#pragma once

#include <asio.hpp>
#include "server_context.hpp"

namespace network {

class server
        : public std::enable_shared_from_this<session> {
    friend network::session;

public:
    server(asio::io_service &io_service, const asio::ip::tcp::endpoint &endpoint);

    std::shared_ptr<server_context> get_context() const;

private:
    void do_accept();

    asio::ip::tcp::acceptor acceptor_;
    asio::ip::tcp::socket socket_;
    std::shared_ptr<server_context> context_;
};

}
