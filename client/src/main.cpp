//
// chat_client.cpp
// ~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2015 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <cstdlib>
#include <deque>
#include <iostream>
#include <thread>
#include <asio.hpp>
#include <cereal/archives/binary.hpp>
#include "network/packet.hpp"
#include "network/message.hpp"
#include "network/serialize/string.hpp"

using asio::ip::tcp;

typedef std::deque<network::packet> chat_message_queue;

class chat_client {
public:
    chat_client(asio::io_service &io_service,
                tcp::resolver::iterator endpoint_iterator)
            : io_service_(io_service),
              socket_(io_service) {
        do_connect(std::move(endpoint_iterator));
    }

    void write(const network::packet &msg) {
        io_service_.post(
                [this, msg]() {
                    bool write_in_progress = !write_msgs_.empty();
                    write_msgs_.push_back(msg);
                    if (!write_in_progress) {
                        do_write();
                    }
                });
    }

    void close() {
        io_service_.post([this]() { socket_.close(); });
    }

private:
    void do_connect(tcp::resolver::iterator endpoint_iterator) {
        asio::async_connect(
                socket_, endpoint_iterator,
                [this](std::error_code ec, tcp::resolver::iterator) {
                    if (!ec) {
                        do_read_header();
                    }
                });
    }

    void do_read_header() {
        asio::async_read(
                socket_,
                asio::buffer(read_msg_.data(), network::packet::header_length),
                [this](std::error_code ec, std::size_t /*length*/) {
                    if (!ec && read_msg_.decode_header()) {
                        do_read_body();
                    } else {
                        socket_.close();
                    }
                });
    }

    void do_read_body() {
        asio::async_read(
                socket_,
                asio::buffer(read_msg_.body(), read_msg_.body_length()),
                [this](std::error_code ec, std::size_t /*length*/) {
                    if (!ec) {
                        std::istringstream ss(std::string(read_msg_.body(), read_msg_.body_length()));
                        network::message message;
                        {
                            cereal::BinaryInputArchive ar(ss);
                            ar(message);
                        }
                        std::cout << message.type << " " << message.id << " " << static_cast<bool>(message.status)
                                  << std::endl;
                        do_read_header();
                    } else {
                        socket_.close();
                    }
                });
    }

    void do_write() {
        asio::async_write(
                socket_,
                asio::buffer(write_msgs_.front().data(),
                             write_msgs_.front().length()),
                [this](std::error_code ec, std::size_t /*length*/) {
                    if (!ec) {
                        write_msgs_.pop_front();
                        if (!write_msgs_.empty()) {
                            do_write();
                        }
                    } else {
                        socket_.close();
                    }
                });
    }

private:
    asio::io_service &io_service_;
    tcp::socket socket_;
    network::packet read_msg_;
    chat_message_queue write_msgs_;
};

int main(int argc, char *argv[]) {
    try {
        if (argc != 3) {
            std::cerr << "Usage: chat_client <host> <port>\n";
            return 1;
        }

        asio::io_service io_service;

        tcp::resolver resolver(io_service);
        auto endpoint_iterator = resolver.resolve({argv[1], argv[2]});
        chat_client c(io_service, endpoint_iterator);

        std::thread t([&io_service]() { io_service.run(); });

        //////
        network::packet packet;
        std::ostringstream ss;
        {
            cereal::BinaryOutputArchive ar(ss);

            network::message{
                    network::operation_type::username,
                    1,
                    network::operation_status::ok
            }.serialize(ar);

            network::serialize::save_string(ar, std::string("Scorsi"));
        }
        auto s = ss.str();

        packet.body_length(s.length());
        std::memcpy(packet.body(), s.c_str(), packet.body_length());
        packet.encode_header();

        std::cout << "\""
                  << std::string(packet.data(), packet.body_length() + packet.header_length)
                  << "\""
                  << std::endl;
        c.write(packet);
        //////

        char line[1];
        std::cin.getline(line, 1);

        c.close();
        t.join();
    }
    catch (std::exception &e) {
        std::cerr << "Exception: " << e.what() << "\n";
    }

    return 0;
}