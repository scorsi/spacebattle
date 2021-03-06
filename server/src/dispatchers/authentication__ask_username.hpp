#pragma once

#include <memory>
#include "network/session.hpp"
#include "event.hpp"
#include "state.hpp"
#include "network/message.hpp"
#include "dispatch_context.hpp"

namespace dispatchers {
namespace authentication {
namespace ask_username {

bool dispatch_send(const dispatch_context &context);

}
}
}
