#include "session_context.hpp"

session_context::session_context()
        : username_(),
          state_(state::connection) {
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
