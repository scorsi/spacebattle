#include "authentication__ask_username.hpp"

#include "message.hpp"
#include "events/set_username.hpp"
#include "event.hpp"
#include "helpers/serialization.hpp"
#include "client.hpp"

namespace dispatchers {
namespace authentication {
namespace set_username {

bool dispatch(cereal::BinaryInputArchive &, const message &message, godot::client &client) {
    if (message.status) {
        client.get_context().set_state(state::in_menu);
        client.owner->emit_signal("connection_ready");
        return true;
    } else {
        // Check for error message
        client.disconnect_from_host();
        return false;
    }
}

}
}
}
