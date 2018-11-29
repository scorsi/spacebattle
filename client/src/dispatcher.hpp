#pragma once

#include <memory>
#include "state.hpp"
#include "event.hpp"
#include "message.hpp"

namespace godot {
class client;
}

namespace dispatcher {

bool dispatch(const std::string &packet,
              const message &message,
              godot::client &client);

}
