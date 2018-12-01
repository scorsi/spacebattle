#pragma once

#include <cstdint>

enum event : std::uint32_t {
    set_player_id = 001,
    ask_username = 101,
    set_username = 102
};
