#include <iostream>
#include "include/wss.hpp"

int main(int argc, char* argv[])
{
    if (argc != 4)
    {
        std::cerr <<
            "WSS Version " << wssserver_VERSION_MAJOR << "." << wssserver_VERSION_MINOR << std::endl <<
            "Usage: websocket-server-async <address> <port> <threads>\n" <<
            "Example:\n" <<
            "    websocket-server-async 0.0.0.0 8080 1\n";
        return EXIT_FAILURE;
    }
    const auto address = boost::asio::ip::make_address(argv[1]);
    const auto port = static_cast<unsigned short>(std::atoi(argv[2]));
    const auto threads = std::max<int>(1, std::atoi(argv[3]));
    boost::asio::io_context ioc{threads};

    boost::make_shared<server_wss::listener>(ioc, boost::asio::ip::tcp::endpoint(address, port))->run();

    std::vector<std::thread> v;
    v.reserve(threads);
    for(auto i = threads - 1; i > 0; --i)
        v.emplace_back(
            [&ioc]{
                ioc.run();
            });
    ioc.run();
    return EXIT_SUCCESS;
}
