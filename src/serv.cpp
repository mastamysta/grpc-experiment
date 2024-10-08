#include <iostream>

#include <grpcpp/grpcpp.h>
#include <grpcpp/health_check_service_interface.h>
#include <grpcpp/ext/proto_server_reflection_plugin.h>

#include <ss.grpc.pb.h>


class Speedy_impl final : public speedy::Service
{
public:
    grpc::Status SayHello(grpc::ServerContext* context, const str* request, str* response) override
    {
        response->set_msg("Bibblyboo\n");
        return grpc::Status::OK;
    }
};

int main()
{
    std::cout << "Starting server.\n";

    std::string server_address("0.0.0.0:50051");
    Speedy_impl service;

    grpc::ServerBuilder builder;
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    builder.RegisterService(&service);
    std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
    std::cout << "Server listening on " << server_address << std::endl;
    server->Wait();
}
