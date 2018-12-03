#include "room.hpp"

#include <uuid.h>
#include "network/session.hpp"

room::room(const std::string &name)
        : name_(name),
          status_(status::WAITING_FOR_PLAYER),
          game_type_(game_type::CLASSIC),
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

void room::remove_player(std::shared_ptr<network::session> player) {
    players_.remove_if([&player](std::shared_ptr<network::session> other_player) {
        return player->get_id() == other_player->get_id();
    });
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

room::status room::get_status() const {
    return status_;
}

void room::set_status(room::status status_) {
    status_ = status_;
}

room::game_type room::get_game_type() const {
    return game_type_;
}

void room::set_game_type(room::game_type game_type_) {
    game_type_ = game_type_;
}
