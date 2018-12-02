#include "server.hpp"

#include <iostream>
#include "session.hpp"

namespace network {

server::server(asio::io_service &io_service,
               const asio::ip::tcp::endpoint &endpoint)
        : acceptor_(io_service, endpoint),
          socket_(io_service) {
    context_ = std::make_shared<server_context>();
    do_accept();
}

void server::do_accept() {
    acceptor_.async_accept(
            socket_,
            [this](std::error_code ec) {
                if (!ec) {
                    auto session = std::make_shared<network::session>(std::move(socket_), shared_from_this());
                    session->start();
                }

                do_accept();
            });
}

std::shared_ptr<server_context> server::get_context() const {
    return context_;
}

}
