#pragma once

#include <list>
#include "network/session.hpp"

class server_context {
public:
    server_context();

    void broadcast(const network::packet &packet);

    void add_session(std::shared_ptr<network::session> session);

    bool remove_session(const std::shared_ptr<network::session> &session);

    const std::list<std::shared_ptr<network::session>> &get_session_list() const;

private:
    std::list<std::shared_ptr<network::session>> session_list_;
};
