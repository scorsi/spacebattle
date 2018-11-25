#pragma once

#include <cstdint>
#include <cereal/archives/binary.hpp>
#include "event.hpp"

namespace network {

#define MESSAGE_LENGTH (sizeof(std::int32_t) + sizeof(bool))

struct message {
    event type;
    bool status;

    template<class Archive>
    void serialize(Archive &ar) {
        ar(type, status);
    }
};

}
