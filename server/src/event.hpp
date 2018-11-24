#pragma once

#include <cstdint>

enum event : std::int32_t {
    ask_username = 101,
    set_username = 102
};
