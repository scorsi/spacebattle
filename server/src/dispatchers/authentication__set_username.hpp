#pragma once

#include <memory>
#include "network/session.hpp"
#include "event.hpp"
#include "state.hpp"
#include "network/message.hpp"
#include "dispatch_context.hpp"

namespace dispatchers {
namespace authentication {
namespace set_username {

bool dispatch_receive(const network::message &message, const dispatch_context &context, std::stringstream &);

}
}
}
