#include "authentication__ask_username.hpp"

#include "network/message.hpp"
#include "events/set_username.hpp"
#include "event.hpp"
#include "helpers/serialization.hpp"

namespace dispatchers {
namespace authentication {
namespace set_username {

bool dispatch_receive(network::client &client, std::stringstream &payload) {
    client.get_context().set_state(state::in_menu);
    return true;
}

}
}
}
