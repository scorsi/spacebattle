#pragma once

#include <memory>
#include "network/session.hpp"
#include "event.hpp"
#include "state.hpp"
#include "network/message.hpp"
#include "dispatch_context.hpp"

namespace dispatchers {
namespace in_lobby {
namespace player_joined {

bool dispatch_send(const dispatch_context &context);

}
}
}
