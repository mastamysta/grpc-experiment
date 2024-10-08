#include <iostream>
#include <memory>
#include <string>

#include <grpcpp/grpcpp.h>
#include <grpcpp/health_check_service_interface.h>
#include <grpcpp/ext/proto_server_reflection_plugin.h>

#include <ss.grpc.pb.h>

class Speedy_client
{
public:
    Speedy_client(std::shared_ptr<grpc::ChannelInterface> channel) : stub_(speedy::NewStub(channel))
    {
    }

    auto SayHello() const -> std::string
    {
        grpc::ClientContext ctx;
        str req, res;
        
        req.set_msg("Hi.\n");

        grpc::Status stat = stub_->SayHello(&ctx, req, &res);

        if (!stat.ok())
            std::cout << "Something went wrong client-side.\n";

        return res.msg();
    }

private:
    std::unique_ptr<speedy::StubInterface> stub_;
};

int main()
{
    std::cout << "Starting client.\n";

    auto chan = grpc::CreateChannel("localhost:50051", grpc::InsecureChannelCredentials());

    auto client = Speedy_client(chan);

    std::cout << client.SayHello() << "\n";

}
