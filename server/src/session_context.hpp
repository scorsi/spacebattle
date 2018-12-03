#pragma once

#include <memory>
#include <string>
#include "state.hpp"
#include "room.hpp"

class session_context
        : public std::enable_shared_from_this<session_context> {
public:
    session_context();

    ~session_context();

    const state &get_state() const;

    void set_state(const state &new_state);

    const std::string &get_username() const;

    void set_username(const std::string &new_username);

    const std::shared_ptr<room> &get_room() const;

    void set_room(const std::shared_ptr<room> &room_);

private:
    std::string username_;
    state state_;
    std::shared_ptr<room> room_;
};
