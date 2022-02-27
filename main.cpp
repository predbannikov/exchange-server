#include <iostream>
#include "include/wss.hpp"

int main(int argc, char* argv[])
{
  server_wss::version();
    if (argc != 4)
    {
        std::cerr <<
            "Usage: websocket-server-async <address> <port> <threads>\n" <<
            "Example:\n" <<
            "    websocket-server-async 0.0.0.0 8080 1\n";
        return EXIT_FAILURE;
    }

    auto const address = boost::asio::ip::make_address(argv[1]);
    auto const port = static_cast<unsigned short>(std::atoi(argv[2]));
    auto const threads = std::max<int>(1, std::atoi(argv[3]));

    // The io_context is required for all I/O
    boost::asio::io_context ioc{threads};

    // Create and launch a listening port
    std::make_shared<server_wss::listener>(ioc, boost::asio::ip::tcp::endpoint{address, port})->run();



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
