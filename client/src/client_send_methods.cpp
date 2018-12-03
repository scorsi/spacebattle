#include "client.hpp"

#include <sstream>
#include <cereal/archives/binary.hpp>
#include "message.hpp"
#include "serialize/string.hpp"

namespace godot {

void client::send_fetch_rooms() {
    std::stringstream ss;
    {
        cereal::BinaryOutputArchive ar(ss);
        ar(message{event::fetch_rooms, true});
    }
    write(ss.str());
}

void client::send_join_room(godot::String _id) {
    auto id = std::string(_id.alloc_c_string(), std::size_t(_id.length()));
    std::stringstream ss;
    {
        cereal::BinaryOutputArchive ar(ss);
        ar(message{event::join_room, true});
        serialize::save_string(ar, id);
    }
    write(ss.str());
}

void client::send_create_room(godot::String _name) {
    auto name = std::string(_name.alloc_c_string(), std::size_t(_name.length()));
    std::stringstream ss;
    {
        cereal::BinaryOutputArchive ar(ss);
        ar(message{event::create_room, true});
        serialize::save_string(ar, name);
        ar(std::uint16_t(1)); // CLASSIC GAME TYPE
    }
    write(ss.str());
}

}
