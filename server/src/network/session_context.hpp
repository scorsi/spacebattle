#pragma once

#include <memory>
#include <string>

namespace network {

class session_context : public std::enable_shared_from_this<session_context> {
public:
    session_context();

    const std::string &get_username() const;

    void set_username(const std::string &new_username);

private:
    std::string username_;
};

}
