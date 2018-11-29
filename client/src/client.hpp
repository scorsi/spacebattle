#include <climits>

#pragma once

#include <deque>
#include <core/Godot.hpp>
#include <Node.hpp>
#include <StreamPeerTCP.hpp>
#include <PacketPeerStream.hpp>
#include "context.hpp"

namespace godot {

class client : public godot::GodotScript<Node> { // NOLINT(cppcoreguidelines-pro-type-member-init)

GODOT_CLASS(client)

public:
    client() = default;

    ~client();

    static void  __unused _register_methods();

    void ready();

    void process();

    void write(const std::string &message);

    void start_client(const godot::Variant &ip_address, const godot::Variant &port);

    void stop_client();

    godot::String get_server_ip() const;

    void set_server_ip(godot::String new_server_ip);

    int64_t get_server_port() const;

    void set_server_port(int64_t new_server_ip);

    bool is_connected() const;

    context &get_context();

private:
    void connect();

    bool check_connection();

    void do_read();

    void do_write();

    godot::String server_ip_ = "";
    int64_t server_port_ = 0;
    bool connected_ = false;
    godot::StreamPeerTCP *connection_ = nullptr;
    godot::PacketPeerStream *peerstream_ = nullptr;
    context context_;
    std::deque<std::string> packets_;
};

}