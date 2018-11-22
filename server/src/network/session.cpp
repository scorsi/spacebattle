#include "session.hpp"

#include "server_context.hpp"

namespace network {

session::session(asio::ip::tcp::socket socket, const std::shared_ptr<network::server_context> &server_context)
        : socket_(std::move(socket)),
          server_context_(server_context) {
    context_ = std::make_shared<network::session_context>();
}

void session::start() {
    server_context_->add_session(shared_from_this());
    do_read();
}

void session::deliver(const network::packet &packet) {
    bool write_in_progress = !write_msgs_.empty();
    write_msgs_.push_back(packet);
    if (!write_in_progress) {
        do_write();
    }
}

void session::do_read() {
    auto self(shared_from_this());
    asio::async_read(
            socket_,
            asio::buffer(read_msg_.data(), network::packet::header_length),
            [this, self](std::error_code ec, std::size_t /* length */) {
                if (!ec && read_msg_.decode_header()) {
                    asio::async_read(
                            socket_,
                            asio::buffer(read_msg_.body(), read_msg_.body_length()),
                            [this, self](std::error_code ec, std::size_t /* length */) {
                                if (!ec) {
                                    packet_handler::do_handle(shared_from_this(), read_msg_);
                                    do_read();
                                } else if ((asio::error::eof == ec) ||
                                           (asio::error::connection_reset == ec)) {
                                    server_context_->remove_session(shared_from_this());
                                    return;
                                } else {
                                    // DO SOMETHING
                                    return;
                                }
                            });
                } else if ((asio::error::eof == ec) ||
                           (asio::error::connection_reset == ec)) {
                    server_context_->remove_session(shared_from_this());
                    return;
                } else {
                    // DO SOMETHING
                    return;
                }
            });
}

void session::do_write() {
    auto self(shared_from_this());
    asio::async_write(
            socket_,
            asio::buffer(write_msgs_.front().data(),
                         write_msgs_.front().length()),
            [this, self](std::error_code ec, std::size_t length) {
                if (!ec) {
                    write_msgs_.pop_front();
                    if (!write_msgs_.empty()) {
                        do_write();
                    }
                } else {
                    // DO SOMETHING
                }
            });
}

std::shared_ptr<network::session_context> session::get_context() {
    return context_;
}

}
