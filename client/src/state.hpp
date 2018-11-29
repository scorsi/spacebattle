#pragma once

#include <cstddef>

enum state : std::uint16_t {
    connection,
    authentication,
    in_menu
};
