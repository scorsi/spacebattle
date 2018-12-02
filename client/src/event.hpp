#pragma once

#include <cstdint>

enum event : std::uint32_t {
    set_player_id = 001,
    ask_username = 101,
    set_username = 102,
    fetch_rooms = 201,
    fetch_room_info = 202,
    create_room = 203,
    join_room = 204,
    leave_room = 301,
    player_joined = 302,
    player_leaved = 303
};
