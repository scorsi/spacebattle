#pragma once

#include <memory>
#include "event.hpp"
#include "state.hpp"
#include "session_context.hpp"

namespace dispatchers {
namespace authentication {
namespace set_username {

bool dispatch_receive(std::shared_ptr<session_context> session_context,
                      std::stringstream &in,
                      std::stringstream &out);

}
}
}
