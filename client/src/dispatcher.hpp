#pragma once

#include <memory>
#include "network/packet.hpp"
#include "state.hpp"
#include "event.hpp"

namespace network {
class client;
}

namespace dispatcher {

bool dispatch_send(const event &event,
                   const std::shared_ptr<network::client> &client);

bool dispatch_receive(const network::packet &packet,
                      const std::shared_ptr<network::client> &client);

}
