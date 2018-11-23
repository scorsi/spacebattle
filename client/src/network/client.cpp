#include "client.hpp"

namespace network {

client::client(asio::io_service &io_service, asio::ip::tcp::resolver::iterator endpoint_iterator)
        : io_service_(io_service),
          socket_(io_service) {
    do_connect(std::move(endpoint_iterator));
}

void client::deliver(const network::packet &msg) {
    io_service_.post(
            [this, msg]() {
                bool write_in_progress = !write_packets_.empty();
                write_packets_.push_back(msg);
                if (!write_in_progress) {
                    do_write();
                }
            });
}

void client::close() {
    io_service_.post([this]() { socket_.close(); });
}

void client::do_connect(asio::ip::tcp::resolver::iterator endpoint_iterator) {
    asio::async_connect(
            socket_, endpoint_iterator,
            [this](std::error_code ec, asio::ip::tcp::resolver::iterator) {
                if (!ec) {
                    do_read();
                }
            });
}

void client::do_read() {
    asio::async_read(
            socket_,
            asio::buffer(read_packet_.get_header(), PACKET_HEADER_LENGTH),
            [this](std::error_code ec, std::size_t /* length */) {
                if (!ec && read_packet_.decode_header()) {
                    asio::async_read(
                            socket_,
                            asio::buffer(read_packet_.get_body(), read_packet_.get_body_length()),
                            [this](std::error_code ec, std::size_t /* length */) {
                                if (!ec) {
                                    // dispatcher::dispatch_receive(read_packet_);
                                    do_read();
                                } else if ((asio::error::eof == ec) ||
                                           (asio::error::connection_reset == ec)) {
                                    close();
                                    return;
                                } else {
                                    close();
                                    return;
                                }
                            });
                } else if ((asio::error::eof == ec) ||
                           (asio::error::connection_reset == ec)) {
                    close();
                    return;
                } else {
                    close();
                    return;
                }
            });
}

void client::do_write() {
    asio::async_write(
            socket_,
            asio::buffer(write_packets_.front().create_full_packet(),
                         write_packets_.front().get_full_packet_length()),
            [this](std::error_code ec, std::size_t length) {
                if (!ec) {
                    write_packets_.pop_front();
                    if (!write_packets_.empty()) {
                        do_write();
                    }
                } else {
                    close();
                }
            });
}

}
