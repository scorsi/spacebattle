#include "session.hpp"

#include <string>
#include "server_context.hpp"
#include "message.hpp"
#include "dispatcher.hpp"

namespace network {

session::session(asio::ip::tcp::socket socket, const std::shared_ptr<server_context> &server_context)
        : socket_(std::move(socket)),
          server_context_(server_context),
          write_packets_() {
    context_ = std::make_shared<session_context>();
}

void session::start() {
    server_context_->add_session(shared_from_this());
    do_read();
}

void session::deliver(const network::packet &packet) {
    bool write_in_progress = !write_packets_.empty();
    write_packets_.push_back(packet);
    if (!write_in_progress) {
        do_write();
    }
}

void session::do_read() {
    std::cout << "Reading..." << std::endl;
    auto self(shared_from_this());
    asio::async_read(
            socket_,
            asio::buffer(read_packet_.get_header(), PACKET_HEADER_LENGTH),
            [this, self](std::error_code ec, std::size_t /* length */) {
                if (!ec && read_packet_.decode_header()) {
                    asio::async_read(
                            socket_,
                            asio::buffer(read_packet_.get_body(), read_packet_.get_body_length()),
                            [this, self](std::error_code ec, std::size_t /* length */) {
                                if (!ec) {
                                    std::cout << "Successfully read packet" << std::endl;
                                    dispatcher::dispatch_receive(read_packet_, self);
                                    do_read();
                                } else if ((asio::error::eof == ec) ||
                                           (asio::error::connection_reset == ec)) {
                                    server_context_->remove_session(shared_from_this());
                                    return;
                                } else {
                                    std::cout << "Got error while reading: " << ec << std::endl;
                                    return;
                                }
                            });
                } else if ((asio::error::eof == ec) ||
                           (asio::error::connection_reset == ec)) {
                    server_context_->remove_session(shared_from_this());
                    return;
                } else {
                    std::cout << "Got error while reading: " << ec << std::endl;
                    return;
                }
            });
}

void session::do_write() {
    std::cout << "Writing..." << std::endl;
    auto self(shared_from_this());
    asio::async_write(
            socket_,
            asio::buffer(&write_packets_.front().create_full_packet()[0],
                         write_packets_.front().get_full_packet_length()),
            [this, self](std::error_code ec, std::size_t length) {
                if (!ec) {
                    std::cout << "Successfully write packet" << std::endl;
                    write_packets_.pop_front();
                    if (!write_packets_.empty()) {
                        do_write();
                    }
                } else {
                    std::cout << "Got error while writing: " << ec << std::endl;
                }
            });
}

std::shared_ptr<session_context> session::get_context() {
    return context_;
}

}
