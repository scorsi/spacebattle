#pragma once

#include <memory>
#include "network/client.hpp"
#include "event.hpp"
#include "state.hpp"

namespace dispatchers {
namespace authentication {
namespace ask_username {

bool dispatch_receive(const std::shared_ptr<network::client> &client, std::stringstream &payload);

}
}
}
