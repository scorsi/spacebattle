#pragma once

#include <memory>
#include "client.hpp"
#include "event.hpp"
#include "state.hpp"
#include "message.hpp"

namespace dispatchers {
namespace authentication {
namespace ask_username {

bool dispatch(cereal::BinaryInputArchive &archive, const message &message, godot::client &client);

}
}
}
