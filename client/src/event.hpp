#pragma once

#include <cstdint>

enum event : std::uint32_t {
    ask_username = 101,
    set_username = 102
};
