#pragma once

#include <memory>
#include <cereal/archives/binary.hpp>
#include "network/message.hpp"
#include "network/session.hpp"
#include "serialize/string.hpp"

#define OPERATION_USERNAME_ID (100)

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

std::unique_ptr<network::packet> handle_send(std::shared_ptr<network::session> session, int id);

std::unique_ptr<network::packet> handle_receive(std::shared_ptr<network::session> session,
                                                const network::message &msg,
                                                cereal::BinaryInputArchive &archive);

}
}
