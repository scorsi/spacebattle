#include "session_context.hpp"

session_context::session_context()
        : username_(),
          state_(state::connection) {
}

session_context::~session_context() {
    // if (room_ != nullptr) room_->remove_player(shared_from_this());
}

const state &session_context::get_state() const {
    return state_;
}

void session_context::set_state(const state &new_state) {
    state_ = new_state;
}

const std::string &session_context::get_username() const {
    return username_;
}

void session_context::set_username(const std::string &new_username) {
    username_ = new_username;
}

const std::shared_ptr<room> &session_context::get_room() const {
    return room_;
}

void session_context::set_room(const std::shared_ptr<room> &new_room) {
    room_ = new_room;
}