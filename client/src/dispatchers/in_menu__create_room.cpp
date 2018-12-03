#include "in_menu__create_room.hpp"

#include "serialize/string.hpp"

namespace dispatchers {
namespace in_menu {
namespace create_room {

bool dispatch(cereal::BinaryInputArchive &archive, const message &message, godot::client &client) {
    if (message.type) {
        std::string id;
        serialize::load_string(archive, id);
        client.owner->emit_signal("result_create_room", godot::String(id.c_str()));
    }
    return true;
}

}
}
}
