#pragma once

#include <memory>
#include <string>
#include "state.hpp"

class session_context {
public:
    session_context();

    const state &get_state() const;

    void set_state(const state &new_state);

    const std::string &get_username() const;

    void set_username(const std::string &new_username);

private:
    std::string username_;
    state state_;
};
