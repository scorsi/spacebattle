#pragma once

#include <memory>
#include "network/session.hpp"
#include "event.hpp"
#include "state.hpp"

namespace dispatchers {
namespace authentication {
namespace ask_username {

bool dispatch_send(const std::shared_ptr<network::session> &session);

}
}
}
