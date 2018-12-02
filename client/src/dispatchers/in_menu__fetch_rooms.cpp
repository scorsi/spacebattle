#include "in_menu__fetch_rooms.hpp"

#include <list>
#include "room.hpp"

namespace dispatchers {
namespace in_menu {
namespace fetch_rooms {

bool dispatch(cereal::BinaryInputArchive &archive, const message &message, godot::client &client) {
    if (message.status) {
        std::uint32_t size;
        archive(size);
        godot::Array rooms;
        for (std::uint32_t i = 0; i < size; i++) {
            room r;
            archive(r);
            rooms.append(r.to_godot_format());
        }
        godot::Array args;
        args.append(rooms);
        client.owner->emit_signal("result_fetch_rooms", args);
    }
    return true;
}

}
}
}
