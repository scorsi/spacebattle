#pragma once

#include <string>
#include <list>

namespace network {
class session;
}

class room {
public:
    explicit room(const std::string &name);

    void add_player(std::shared_ptr<network::session> player);

    const std::string &get_id() const;

    const std::string &get_name() const;

    const std::list<std::shared_ptr<network::session>> &get_players() const;

    std::list<std::shared_ptr<network::session>> &get_players();

private:
    std::string id_;
    std::string name_;
    std::list<std::shared_ptr<network::session>> players_;
    // std::list<std::shared_ptr<network::session>> spectators_;
};
