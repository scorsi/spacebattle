#include <cstdlib>
#include <iostream>
#include <thread>
#include <asio.hpp>
#include "network/client.hpp"

int main(int argc, char *argv[]) {
    try {
        if (argc != 3) {
            std::cerr << "Usage: chat_client <host> <port>\n";
            return 1;
        }

        asio::io_service io_service;

        asio::ip::tcp::resolver resolver(io_service);
        auto endpoint_iterator = resolver.resolve({argv[1], argv[2]});
        network::client c(io_service, endpoint_iterator);

        std::thread t([&io_service]() { io_service.run(); });

        ////
        char line[1];
        std::cin.getline(line, 1);
        ////

        c.close();
        t.join();
    }
    catch (std::exception &e) {
        std::cerr << "Exception: " << e.what() << "\n";
    }

    return 0;
}