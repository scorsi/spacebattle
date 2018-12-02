#include "client.hpp"

#include <StreamPeerTCP.hpp>
#include <PacketPeerStream.hpp>
#include "dispatcher.hpp"
#include "message.hpp"

namespace godot {

client::~client() {
    disconnect_from_host();
}

void __unused client::_register_methods() {
    register_method("_ready", &client::ready);
    register_method("_process", &client::process);
    register_method("connect_to_host", &client::connect_to_host);
    register_method("disconnect_from_host", &client::disconnect_from_host);
    register_method("is_connected", &client::is_connected);
    // Send methods:
    register_method("send_fetch_rooms", &client::send_fetch_rooms);

    register_property("server_ip", &client::set_server_ip, &client::get_server_ip, godot::String(""));
    register_property("server_port", &client::set_server_port, &client::get_server_port, int64_t(0));
    register_property("username", &client::set_username, &client::get_username, godot::String(""));
    register_property("player_id", &client::set_id, &client::get_id, godot::String(""));

    register_signal<client>("connection_success");
    register_signal<client>("connection_failure");
    register_signal<client>("connection_ready");
    register_signal<client>("disconnected");
    // Receive signals:
    register_signal<client>("result_fetch_rooms", "rooms", GODOT_VARIANT_TYPE_ARRAY);
}

void client::ready() {
    owner->set_process(false);
}

void client::process() {
    if (disconnection_) return;
    if (!check_connection()) return;
    do_write();
    do_read();
}

void client::connect_to_host() {
    connected_ = false;
    disconnection_ = false;

    context_ = context();
    context_.set_username(username_.alloc_c_string());
    connection_ = new godot::StreamPeerTCP();
    auto err = connection_->connect_to_host(server_ip_, server_port_);
    if (err == Error::OK) {
        peerstream_ = new godot::PacketPeerStream();
        peerstream_->set_stream_peer(connection_);
        switch (connection_->get_status()) {
            case StreamPeerTCP::Status::STATUS_CONNECTED:
                owner->set_process(true);
                connected_ = true;
                owner->emit_signal("connection_success");
                return;
            case StreamPeerTCP::Status::STATUS_CONNECTING:
                owner->set_process(true);
                return;
            default:
                // case StreamPeerTCP::Status::STATUS_NONE
                // case StreamPeerTCP::Status::STATUS_ERROR
                owner->emit_signal("connection_failure");
                return;
        }
    }
}

void client::disconnect_from_host() {
    disconnection_ = true;
    connected_ = false;
    if (connection_) connection_->disconnect_from_host();
    owner->emit_signal("disconnected");
    /// Godot has a garbage collector:
    // delete connection_;
    // delete peerstream_;
}

bool client::check_connection() {
    if (!connected_) {
        if (connection_->get_status() == StreamPeerTCP::Status::STATUS_CONNECTED) {
            connected_ = true;
            owner->emit_signal("connection_success");
        } else if (connection_->get_status() == StreamPeerTCP::Status::STATUS_NONE ||
                   connection_->get_status() == StreamPeerTCP::Status::STATUS_ERROR) {
            owner->emit_signal("connection_failure");
            owner->set_process(false);
        }
        return false;
    } else if (connection_->get_status() == StreamPeerTCP::Status::STATUS_NONE ||
               connection_->get_status() == StreamPeerTCP::Status::STATUS_ERROR) {
        owner->emit_signal("disconnected");
        owner->set_process(false);
        return false;
    }
    return true;
}

void client::do_read() {
    if (peerstream_->get_available_packet_count() > 0) {
        auto p = peerstream_->get_packet();
        Godot::print(godot::String((std::string("Got packet of size: ") + std::to_string(p.size())).c_str()));
        auto s = std::string(reinterpret_cast<const char *>(p.read().ptr()), std::size_t(p.size()));
        std::stringstream ss(s);
        message m{};
        cereal::BinaryInputArchive ar(ss);
        ar(m);
        Godot::print(godot::String((std::to_string(m.type) + " to read").c_str()));
        if (dispatcher::dispatch_receive(ar, m, *this)) Godot::print("Success");
        else Godot::print("Failure");
        Godot::print("Read");
    }
}

void client::write(const std::string &packet) {
    packets_.push_back(packet);
}

void client::do_write() {
    if (!packets_.empty()) {
        auto p = packets_.front();
        int l = static_cast<int>(p.length());
        auto b = godot::PoolByteArray();
        for (int i = 0; i < l; i++) {
            b.append(static_cast<std::uint8_t>(p[i]));
        }
        peerstream_->put_packet(b);
        Godot::print("Sent");

        packets_.pop_front();
    }
}

godot::String client::get_server_ip() const {
    return server_ip_;
}

void client::set_server_ip(godot::String new_server_ip) {
    server_ip_ = new_server_ip;
}

int64_t client::get_server_port() const {
    return server_port_;
}

void client::set_server_port(int64_t new_server_port) {
    server_port_ = new_server_port;
}

godot::String client::get_username() const {
    return username_;
}

void client::set_username(godot::String new_username) {
    username_ = new_username;
}

bool client::is_connected() const {
    return connected_;
}

context &client::get_context() {
    return context_;
}

godot::String client::get_id() const {
    return id_;
}

void client::set_id(godot::String new_id) {
    id_ = new_id;
}


}
