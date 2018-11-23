#pragma once

#include <memory>
#include "network/session.hpp"
#include "event.hpp"
#include "state.hpp"

namespace dispatchers {
namespace authentication {
namespace set_username {

bool dispatch_receive(const std::shared_ptr<network::session> &, std::stringstream &);

}
}
}
