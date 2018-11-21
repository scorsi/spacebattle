#pragma once

#include <asio.hpp>
#include "server_context.hpp"

namespace network {
    class server {
    public:
        server(asio::io_service &io_service, const asio::ip::tcp::endpoint &endpoint);

    private:
        void do_accept();

        asio::ip::tcp::acceptor acceptor_;
        asio::ip::tcp::socket socket_;
        std::shared_ptr<network::server_context> context_;
    };
}
