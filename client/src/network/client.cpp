#include "client.hpp"

#include "dispatcher.hpp"

namespace network {

client::client(asio::io_service &io_service, asio::ip::tcp::resolver::iterator endpoint_iterator)
        : io_service_(io_service),
          socket_(io_service),
          context_() {
    do_connect(endpoint_iterator); // NOLINT(performance-unnecessary-value-param)
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
    std::cout << "Closing socket" << std::endl;
    io_service_.post([this]() { socket_.close(); });
}

void client::do_connect(asio::ip::tcp::resolver::iterator endpoint_iterator) {
    asio::async_connect(
            socket_, endpoint_iterator, // NOLINT(performance-unnecessary-value-param)
            [this](std::error_code ec, asio::ip::tcp::resolver::iterator) {
                if (!ec) {
                    context_.set_state(state::authentication);
                    do_read();
                }
            });
}

void client::do_read() {
    std::cout << "Reading..." << std::endl;
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
                                    std::cout << "Successfully read packet" << std::endl;
                                    dispatcher::dispatch_receive(read_packet_, *this);
                                    do_read();
                                } else if ((asio::error::eof == ec) ||
                                           (asio::error::connection_reset == ec)) {
                                    close();
                                    return;
                                } else {
                                    std::cout << "Got error while reading: " << ec << std::endl;
                                    close();
                                    return;
                                }
                            });
                } else if ((asio::error::eof == ec) ||
                           (asio::error::connection_reset == ec)) {
                    close();
                    return;
                } else {
                    std::cout << "Got error while reading: " << ec << std::endl;
                    close();
                    return;
                }
            });
}

void client::do_write() {
    std::cout << "Writing..." << std::endl;
    asio::async_write(
            socket_,
            asio::buffer(&write_packets_.front().create_full_packet()[0],
                         write_packets_.front().get_full_packet_length()),
            [this](std::error_code ec, std::size_t length) {
                if (!ec) {
                    std::cout << "Successfully write packet" << std::endl;
                    write_packets_.pop_front();
                    if (!write_packets_.empty()) {
                        do_write();
                    }
                } else {
                    std::cout << "Got error while writing: " << ec << std::endl;
                    close();
                }
            });
}

context &client::get_context() {
    return context_;
}

}
