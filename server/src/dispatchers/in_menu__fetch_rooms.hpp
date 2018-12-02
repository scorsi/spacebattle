#pragma once

#include <memory>
#include "network/session.hpp"
#include "event.hpp"
#include "state.hpp"
#include "network/message.hpp"
#include "dispatch_context.hpp"

namespace dispatchers {
namespace in_menu {
namespace fetch_rooms {

bool dispatch_receive(const network::message &message, const dispatch_context &context, std::stringstream &payload);

}
}
}
