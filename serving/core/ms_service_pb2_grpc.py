# Generated by the gRPC Python protocol compiler plugin. DO NOT EDIT!
import grpc

import ms_service_pb2 as ms__service__pb2


class MSServiceStub(object):
    """Missing associated documentation comment in .proto file"""

    def __init__(self, channel):
        """Constructor.

        Args:
            channel: A grpc.Channel.
        """
        self.Predict = channel.unary_unary(
                '/ms_serving.MSService/Predict',
                request_serializer=ms__service__pb2.PredictRequest.SerializeToString,
                response_deserializer=ms__service__pb2.PredictReply.FromString,
                )
        self.Test = channel.unary_unary(
                '/ms_serving.MSService/Test',
                request_serializer=ms__service__pb2.PredictRequest.SerializeToString,
                response_deserializer=ms__service__pb2.PredictReply.FromString,
                )


class MSServiceServicer(object):
    """Missing associated documentation comment in .proto file"""

    def Predict(self, request, context):
        """Missing associated documentation comment in .proto file"""
        context.set_code(grpc.StatusCode.UNIMPLEMENTED)
        context.set_details('Method not implemented!')
        raise NotImplementedError('Method not implemented!')

    def Test(self, request, context):
        """Missing associated documentation comment in .proto file"""
        context.set_code(grpc.StatusCode.UNIMPLEMENTED)
        context.set_details('Method not implemented!')
        raise NotImplementedError('Method not implemented!')


def add_MSServiceServicer_to_server(servicer, server):
    rpc_method_handlers = {
            'Predict': grpc.unary_unary_rpc_method_handler(
                    servicer.Predict,
                    request_deserializer=ms__service__pb2.PredictRequest.FromString,
                    response_serializer=ms__service__pb2.PredictReply.SerializeToString,
            ),
            'Test': grpc.unary_unary_rpc_method_handler(
                    servicer.Test,
                    request_deserializer=ms__service__pb2.PredictRequest.FromString,
                    response_serializer=ms__service__pb2.PredictReply.SerializeToString,
            ),
    }
    generic_handler = grpc.method_handlers_generic_handler(
            'ms_serving.MSService', rpc_method_handlers)
    server.add_generic_rpc_handlers((generic_handler,))


 # This class is part of an EXPERIMENTAL API.
class MSService(object):
    """Missing associated documentation comment in .proto file"""

    @staticmethod
    def Predict(request,
            target,
            options=(),
            channel_credentials=None,
            call_credentials=None,
            compression=None,
            wait_for_ready=None,
            timeout=None,
            metadata=None):
        return grpc.experimental.unary_unary(request, target, '/ms_serving.MSService/Predict',
            ms__service__pb2.PredictRequest.SerializeToString,
            ms__service__pb2.PredictReply.FromString,
            options, channel_credentials,
            call_credentials, compression, wait_for_ready, timeout, metadata)

    @staticmethod
    def Test(request,
            target,
            options=(),
            channel_credentials=None,
            call_credentials=None,
            compression=None,
            wait_for_ready=None,
            timeout=None,
            metadata=None):
        return grpc.experimental.unary_unary(request, target, '/ms_serving.MSService/Test',
            ms__service__pb2.PredictRequest.SerializeToString,
            ms__service__pb2.PredictReply.FromString,
            options, channel_credentials,
            call_credentials, compression, wait_for_ready, timeout, metadata)