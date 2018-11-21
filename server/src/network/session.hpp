#pragma once

#include <queue>
#include <asio.hpp>
#include "packet.hpp"
#include "session_context.hpp"

namespace network {
    class server_context;

    class session
            : public std::enable_shared_from_this<session> {
    public:
        std::shared_ptr<network::session_context> context;

        session(asio::ip::tcp::socket socket, std::shared_ptr<network::server_context> server_context);

        void start();

        void deliver(const network::packet &packet);

    private:
        void do_read();

        void do_write();

        asio::ip::tcp::socket socket_;
        network::packet read_msg_;
        std::deque<network::packet> write_msgs_;
        std::shared_ptr<network::server_context> server_context_;
    };
}
