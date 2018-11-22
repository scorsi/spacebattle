#pragma once

#include <cstdint>
#include <cereal/archives/binary.hpp>

namespace network {

struct message {
    int type;
    int id;
    bool status;

    template<class Archive>
    void serialize(Archive &ar) {
        ar(type, id, status);
    }
};

}
