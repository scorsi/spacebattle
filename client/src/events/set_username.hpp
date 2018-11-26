#pragma once

#include <cereal/archives/binary.hpp>
#include "serialize/string.hpp"

namespace events {

struct set_username {
    std::string username;

    void save(cereal::BinaryOutputArchive &archive) const {
        serialize::save_string(archive, username);
    }

    void load(cereal::BinaryInputArchive &archive) {
        serialize::load_string(archive, username);
    }
};

}
