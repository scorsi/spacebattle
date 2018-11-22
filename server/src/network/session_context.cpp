#include "session_context.hpp"

namespace network {

session_context::session_context()
        : username_() {
}

const std::string &session_context::get_username() const {
    return username_;
}

void session_context::set_username(const std::string &new_username) {
    username_ = new_username;
}

}
