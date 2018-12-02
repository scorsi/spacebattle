#pragma once

#include <memory>
#include "state.hpp"
#include "event.hpp"
#include "network/packet.hpp"
#include "dispatch_context.hpp"

namespace network {
class session;
}

namespace dispatcher {

bool dispatch_send(const event &event,
                   const dispatch_context &context);

bool dispatch_receive(const network::packet &packet,
                      const dispatch_context &context);

}
