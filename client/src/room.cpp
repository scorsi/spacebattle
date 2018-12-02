#include "room.hpp"

void room::add_player(std::shared_ptr<network::session> player) {
    players_.push_back(std::move(player));
}

const std::string &room::get_id() const {
    return id_;
}

const std::string &room::get_name() const {
    return name_;
}

const std::list<std::shared_ptr<network::session>> &room::get_players() const {
    return players_;
}

std::list<std::shared_ptr<network::session>> &room::get_players() {
    return players_;
}

room::status room::get_status() const {
    return status_;
}

void room::set_status(room::status status_) {
    status_ = status_;
}

room::game_type room::get_game_type() const {
    return game_type_;
}

void room::set_game_type(room::game_type game_type_) {
    game_type_ = game_type_;
}

godot::Dictionary room::to_godot_format() {
    auto d = godot::Dictionary();
    d["id"] = godot::String(id_.c_str());
    d["name"] = godot::String(name_.c_str());
    d["status"] = godot::Variant(int(status_));
    d["game_type"] = godot::Variant(int(game_type_));
    return d;
}
