#pragma once

#include <memory>
#include "session_context.hpp"
#include "state.hpp"
#include "event.hpp"

namespace dispatcher {

bool dispatch_send(const event &event,
                   std::shared_ptr<session_context> session_context,
                   std::stringstream &in_stream,
                   std::stringstream &out_stream);

bool dispatch_receive(const event &event,
                      std::shared_ptr<session_context> session_context,
                      std::stringstream &in_stream,
                      std::stringstream &out_stream);

}
