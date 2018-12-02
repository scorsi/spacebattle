#include "in_lobby__leave_room.hpp"

namespace dispatchers {
namespace in_lobby {
namespace leave_room {

bool dispatch_receive(const network::message &message, const dispatch_context &context, std::stringstream &payload) {
    return true;
}

}
}
}
