#pragma once

#include <queue>
#include <asio.hpp>
#include "packet.hpp"
#include "session_context.hpp"

class server_context;

namespace network {

class session
        : public std::enable_shared_from_this<session> {
public:
    session(asio::ip::tcp::socket socket, const std::shared_ptr<server_context> &server_context);

    void start();

    void deliver(const network::packet &packet);

    std::shared_ptr<session_context> get_context();

private:
    void do_read();

    void do_write();

    asio::ip::tcp::socket socket_;
    std::shared_ptr<session_context> context_;
    std::shared_ptr<server_context> server_context_;
    network::packet read_packet_;
    std::deque<network::packet> write_packets_;
};

}
