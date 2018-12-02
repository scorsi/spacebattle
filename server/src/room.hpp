#pragma once

#include <string>
#include <list>
#include <cereal/archives/binary.hpp>
#include "serialize/string.hpp"

namespace network {
class session;
}

class room {
public:
    enum status : std::uint16_t {
        WAITING_FOR_PLAYER = 0,
        READY = 1,
        STARTING = 2,
        STARTED = 3,
        FINISHED = 4
    };

    enum game_type : std::uint16_t {
        CLASSIC = 1
    };

    explicit room(const std::string &name);

    void add_player(std::shared_ptr<network::session> player);

    const std::string &get_id() const;

    const std::string &get_name() const;

    const std::list<std::shared_ptr<network::session>> &get_players() const;

    std::list<std::shared_ptr<network::session>> &get_players();

    status get_status() const;

    void set_status(status new_status);

    game_type get_game_type() const;

    void set_game_type(game_type new_game_type);

    template<class Archive>
    void save(Archive &ar) const {
        serialize::save_string(ar, id_);
        serialize::save_string(ar, name_);
        ar(status_, game_type_);
    }

    template<class Archive>
    void load(Archive &ar) {
        serialize::load_string(ar, id_);
        serialize::load_string(ar, name_);
        ar(status_, game_type_);
    }

private:
    std::string id_;
    std::string name_;
    status status_;
    game_type game_type_;
    std::list<std::shared_ptr<network::session>> players_;
    // std::list<std::shared_ptr<network::session>> spectators_;
};
