#include "client.hpp"

#include <sstream>
#include <cereal/archives/binary.hpp>
#include "message.hpp"

namespace godot {

void client::send_fetch_rooms() {
    std::stringstream ss;
    {
        cereal::BinaryOutputArchive ar(ss);
        ar(message{event::fetch_rooms, true});
    }
    write(ss.str());
}

}
