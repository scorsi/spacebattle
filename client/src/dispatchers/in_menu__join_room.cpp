#include "in_menu__join_room.hpp"

namespace dispatchers {
namespace in_menu {
namespace join_room {

bool dispatch(cereal::BinaryInputArchive &, const message &message, godot::client &client) {
    if (message.type) {
        client.owner->emit_signal("result_join_room");
    }
    return true;
}

}
}
}
