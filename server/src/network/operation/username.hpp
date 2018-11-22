#pragma once

#include <cereal/archives/binary.hpp>
#include "network/message.hpp"
#include "network/session.hpp"
#include "network/serialize/string.hpp"

namespace network {
namespace operation {
namespace username {
struct step_client_answer_username {
    std::string username;

    template<class Archive>
    void save(Archive &ar) const {
        serialize::save_string(ar, username);
    }

    template<class Archive>
    void load(Archive &ar) {
        serialize::load_string(ar, username);
    }
};

bool is_valid_send(int id);

bool is_valid_receive(const network::message &msg);

bool handle_send(std::shared_ptr<network::session> session, int id);

bool handle_receive(std::shared_ptr<network::session> session,
                    const network::message &msg,
                    cereal::BinaryInputArchive &ar);
}
}
}