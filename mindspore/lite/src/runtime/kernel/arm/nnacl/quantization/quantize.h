/**
 * Copyright 2020 Huawei Technologies Co., Ltd
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef MINDSPORE_LITE_SRC_RUNTIME_KERNEL_ARM_NNACL_QUANTIZATION_QUANTIZE_H_
#define MINDSPORE_LITE_SRC_RUNTIME_KERNEL_ARM_NNACL_QUANTIZATION_QUANTIZE_H_

#include <stdint.h>
#include <math.h>
#include <stdlib.h>
#include <limits.h>
#include "nnacl/op_base.h"

typedef struct QuantArg {
  double scale_;
  int32_t zp_;
} QuantArg;

typedef struct ConvQuantArg {
  QuantArg **quant_args_;
  double *real_multiplier_;
  int32_t *left_shift_;
  int32_t *right_shift_;
  int32_t *quant_multiplier_;
  int32_t *out_act_min_;
  int32_t *out_act_max_;
} ConvQuantArg;

typedef struct ConcatQuantArg {
  QuantArg *in_args_;
  QuantArg out_args_;
  int output_activation_min_;
  int output_activation_max_;
} ConcatQuantArg;

typedef struct SqueezeQuantArg {
  int *input_sizes_;
  int output_size_;
  int **input_shapes_;
  int *output_shape_;
  float alpha;
  int axis_;
  size_t input_num_;
  size_t output_dim_;
  QuantArg *in_quant_args_;
  QuantArg out_quant_args_;
} SqueezeQuantArg;

typedef struct UnSqueezeQuantArg {
  int *input_sizes_;
  int output_size_;
  int **input_shapes_;
  int *output_shape_;
  float alpha;
  int axis_;
  size_t input_num_;
  size_t output_dim_;
  QuantArg in_quant_args_;
  QuantArg out_quant_args_;
} UnSqueezeQuantArg;

typedef struct PreluQuantArg {
  int *input_sizes_;
  int output_size_;
  int **input_shapes_;
  int *output_shape_;
  size_t input_num_;
  size_t output_dim_;
  float alpha_;
  QuantArg in_args_;
  QuantArg out_args_;
  int output_activation_min_;
  int output_activation_max_;
  QuantArg *in_quant_args_;
  QuantArg out_quant_args_;
} PreluQuantArg;

/*typedef struct SigmoidQuantArg {
    int *input_sizes_;
    int output_size_;
    int **input_shapes_;
    int *output_shape_;
    size_t input_num_;
    size_t output_dim_;
    float alpha_;
    QuantArg in_args_;
    QuantArg out_args_;
    int output_activation_min_;
    int output_activation_max_;
    QuantArg *in_quant_args_;
    QuantArg out_quant_args_;
} SigmoidQuantArg;*/

typedef struct MatmulQuantArg {
  QuantArg input;
  QuantArg weight;
  QuantArg output;
  int32_t out_act_min;
  int32_t out_act_max;
  int32_t left_shift;
  int32_t right_shift;
  int32_t quant_multiplier;
} MatmulQuantArg;

typedef struct PadQuantArg {
  QuantArg *in_quant_args_;
  QuantArg *out_quanr_args_;
  int8_t *constant_value_;
} PadQuantArg;

typedef struct MulQuantArg {
  QuantArg in_quant_args_[2];
  QuantArg out_quant_arg_;
  int output_multiplier_;
  int output_activation_min_;
  int output_activation_max_;
  int shift_left_;
  int shift_right_;
} MulQuantArg;

typedef struct CropQuantArg {
  QuantArg in_args_;
  QuantArg out_args_;
  int output_activation_min_;
  int output_activation_max_;
} CropQuantArg;

typedef struct ArithSelfQuantArg {
  QuantArg in_args_;
  QuantArg out_args_;
  int output_activation_min_;
  int output_activation_max_;
  int output_multiplier_;
  int shift_left_;
  int shift_right_;
} ArithSelfQuantArg;

typedef struct SplitQuantArg {
  QuantArg in_args_;
  QuantArg out_args_[20];
  int output_activation_min_;
  int output_activation_max_;
} SplitQuantArg;

typedef struct SoftmaxQuantArg {
  QuantArg in_quant_args_;
  QuantArg out_quant_arg_;
} SoftmaxQuantArg;

typedef struct ReshapeQuantArg {
  QuantArg in_args_;
  QuantArg out_args_;
  int output_activation_min_;
  int output_activation_max_;
} ReshapeQuantArg;

typedef struct QuantMulArg {
  int32_t multiplier_;
  int left_shift_;
  int right_shift_;
} QuantMulArg;

typedef struct SubQuantArg {
  QuantArg in0_args_;
  QuantArg in1_args_;
  QuantArg out_args_;
  int output_activation_min_;
  int output_activation_max_;
  int input0_multiplier_;
  int input1_multiplier_;
  int output_multiplier_;
  int input0_shift_;
  int input1_shift_;
  int output_shift_;
  int left_shift_result0_;
  int left_shift_result1_;
  int right_shift0_;
  int right_shift1_;
  int left_shift_out_;
  int right_shift_out_;
} SubQuantArg;

typedef struct ArithmeticQuantArg {
  QuantArg in0_args_;
  QuantArg in1_args_;
  QuantArg out_args_;
} ArithmeticQuantArg;
#ifdef __cplusplus
extern "C" {
#endif

void QuantizeMultiplier(double double_multiplier, int32_t *quantized_multiplier, int *shift);

inline void QuantizeMultiplierSmallerThanOne(double double_multiplier, int32_t *quantized_multiplier,
                                             int *right_shift) {
  if (quantized_multiplier == NULL || right_shift == NULL) {
    return;
  }
  int shift;
  QuantizeMultiplier(double_multiplier, quantized_multiplier, &shift);
  *right_shift = -shift;
}

inline void QuantizeRoundParameter(double double_multiplier, int32_t *quantized_multiplier, int *left_shift,
                                   int *right_shift) {
  int shift;
  QuantizeMultiplierSmallerThanOne(double_multiplier, quantized_multiplier, &shift);
  shift = -shift;
  if (shift < 0) {
    *left_shift = 0;
    *right_shift = shift;
  } else {
    *left_shift = shift;
    *right_shift = 0;
  }
}

inline uint8_t QuantizeToUint8(float real_value, float scale, int32_t zp) { return round(real_value / scale + zp); }

inline int32_t QuantizeToInt8(float real_value, float scale, int32_t zp) { return round(real_value / scale + zp); }

inline void CalculateActivationRangeQuantized(bool is_relu, bool is_relu6, int32_t zp, float scale, int *mini,
                                              int *maxi) {
  int32_t min = CHAR_MIN;
  int32_t max = CHAR_MAX;
  int32_t quantized_zero = QuantizeToInt8(0, scale, zp);
  int32_t quantized_six = QuantizeToInt8(6, scale, zp);
  if (is_relu) {
    min = min > quantized_zero ? min : quantized_zero;
  } else if (is_relu6) {
    min = min > quantized_zero ? min : quantized_zero;
    max = max < quantized_six ? max : quantized_six;
  } else {
    // do nothing
  }
  *mini = min;
  *maxi = max;
}

// quantize from float to int8
inline void Quantize(float *input_data, int length, float scale, int zero_point, int8_t *output_data) {
  for (int i = 0; i < length; ++i) {
    int q = (int)round(input_data[i] / scale + zero_point);
    q = q > CHAR_MAX ? CHAR_MAX : q;
    q = q < CHAR_MIN ? CHAR_MIN : q;
    output_data[i] = (int8_t)q;
  }
}

// dequantize from int8 to float
inline void Dequantize(int8_t *input_data, int length, float scale, int zero_point, float *output_data) {
  for (int i = 0; i < length; ++i) {
    output_data[i] = scale * (input_data[i] - zero_point);
  }
}

#ifdef __cplusplus
}
#endif

#endif  // MINDSPORE_LITE_SRC_RUNTIME_KERNEL_ARM_NNACL_QUANTIZATION_QUANTIZE_H_
