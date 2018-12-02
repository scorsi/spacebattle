#pragma once

#include <queue>
#include <asio.hpp>
#include <uuid.h>
#include "packet.hpp"
#include "session_context.hpp"

class server_context;

namespace network {

class server;

class session
        : public std::enable_shared_from_this<session> {
    friend network::server;

public:
    session(asio::ip::tcp::socket socket, std::shared_ptr<network::server> server);

    void deliver(const network::packet &packet);

    std::shared_ptr<session_context> get_context() const;

    const std::string &get_id() const;

private:
    void start();

    void do_read();

    void do_write();

    asio::ip::tcp::socket socket_;
    std::shared_ptr<session_context> context_;
    std::shared_ptr<network::server> server_;
    network::packet read_packet_;
    std::deque<network::packet> write_packets_;
    std::string id_;
};

}
