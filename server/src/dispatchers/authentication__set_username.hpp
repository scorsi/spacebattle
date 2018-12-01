#pragma once

#include <memory>
#include "network/session.hpp"
#include "event.hpp"
#include "state.hpp"
#include "network/message.hpp"

namespace dispatchers {
namespace authentication {
namespace set_username {

bool dispatch_receive(const network::message &message, const std::shared_ptr<network::session> &, std::stringstream &);

}
}
}
