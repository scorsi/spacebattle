#pragma once

#include <memory>
#include "state.hpp"
#include "event.hpp"
#include "network/packet.hpp"

namespace network {
class session;
}

namespace dispatcher {

bool dispatch_send(const event &event,
                   const std::shared_ptr<network::session> &session);

bool dispatch_receive(const network::packet &packet,
                      const std::shared_ptr<network::session> &session);

}
