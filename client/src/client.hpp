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

    static void __unused _register_methods();

    void ready();

    void process();

    void write(const std::string &message);

    void connect_to_host();

    void disconnect_from_host();

    //

    void send_fetch_rooms();

    //

    godot::String get_server_ip() const;

    void set_server_ip(godot::String new_server_ip);

    int64_t get_server_port() const;

    void set_server_port(int64_t new_server_ip);

    godot::String get_username() const;

    void set_username(godot::String new_username);

    bool is_connected() const;

    context &get_context();

    godot::String get_id() const;

    void set_id(godot::String new_id);

private:
    bool check_connection();

    void do_read();

    void do_write();

    godot::String server_ip_ = "";
    int64_t server_port_ = 0;
    godot::String username_ = "";
    godot::String id_ = "";

    bool connected_ = false;
    bool disconnection_ = false;
    godot::StreamPeerTCP *connection_ = nullptr;
    godot::PacketPeerStream *peerstream_ = nullptr;
    context context_;
    std::deque<std::string> packets_;
};

}