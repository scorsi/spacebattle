#pragma once

#include <memory>
#include "network/session.hpp"
#include "event.hpp"
#include "state.hpp"
#include "network/message.hpp"
#include "dispatch_context.hpp"

namespace dispatchers {
namespace connection {
namespace set_player_id {

bool dispatch_send(const dispatch_context &context);

bool dispatch_receive(const network::message &message, const dispatch_context &context, std::stringstream &payload);

}
}
}
