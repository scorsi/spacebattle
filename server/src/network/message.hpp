#pragma once

#include <cstdint>
#include <cereal/archives/binary.hpp>
#include "event.hpp"

namespace network {

struct message {
    event type;
    bool status;

    template<class Archive>
    void serialize(Archive &ar) {
        ar(type, status);
    }
};

}
