#pragma once

#include <memory>
#include "client.hpp"
#include "event.hpp"
#include "state.hpp"
#include "message.hpp"

namespace dispatchers {
namespace authentication {
namespace set_username {

bool dispatch(cereal::BinaryInputArchive &, const message &message, godot::client &client);

}
}
}
