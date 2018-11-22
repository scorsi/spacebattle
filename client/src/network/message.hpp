#pragma once

#include <cstdint>
#include <cereal/archives/binary.hpp>

namespace network {
    enum operation_type : int {
        username = 100,
        room_fetch = 200,
        room_connect = 201,
        room_disconnect = 202,
        room_ready = 203,
        client_fetch = 300,
        client_connect = 301,
        client_disconnect = 302,
        client_ready = 303,
        game_launch = 304,
        game_start = 304
    };

    enum operation_status : bool {
        ok = true,
        error = false
    };

    struct message {
        network::operation_type type;
        int id;
        network::operation_status status;

        template<class Archive>
        void serialize(Archive &ar) {
            ar(type, id, status);
        }
    };
}
