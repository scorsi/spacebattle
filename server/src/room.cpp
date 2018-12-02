#include "room.hpp"

#include <uuid.h>

room::room(const std::string &name)
        : name_(name),
          players_() {
    uuid_t uuid;
    uuid_generate_random(uuid);
    char out[37];
    out[36] = '\0';
    uuid_unparse(uuid, out);
    id_ = std::string(out);
}

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
