#include "context.hpp"

#include <core/Godot.hpp>

context::context()
        : username_(),
          state_(state::connection) {
}

const state &context::get_state() const {
    return state_;
}

void context::set_state(const state &new_state) {
    godot::Godot::print((std::string("Changing state from ") + std::to_string(state_) + " to " +
                         std::to_string(new_state)).c_str());
    state_ = new_state;
}

const std::string &context::get_username() const {
    return username_;
}

void context::set_username(const std::string &new_username) {
    username_ = new_username;
}
