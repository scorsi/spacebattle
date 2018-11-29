#include "authentication__ask_username.hpp"

#include "message.hpp"
#include "events/set_username.hpp"
#include "event.hpp"
#include "helpers/serialization.hpp"
#include "client.hpp"

namespace dispatchers {
namespace authentication {
namespace set_username {

bool dispatch(godot::client &client, std::stringstream &payload) {
    client.get_context().set_state(state::in_menu);
    return true;
}

}
}
}
