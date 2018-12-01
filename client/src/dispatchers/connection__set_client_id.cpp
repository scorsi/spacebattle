#include "connection__set_client_id.hpp"

#include "helpers/serialization.hpp"
#include "message.hpp"

namespace dispatchers {
namespace connection {
namespace set_player_id {

bool dispatch(const message &, godot::client &client, std::stringstream &payload) {
    std::string id;
    helpers::serialization::load(id, payload);
    client.set_id(id.c_str());
    godot::Godot::print(godot::String(std::string("Got id: " + id).c_str()));
    client.get_context().set_state(state::authentication);

    std::stringstream ss;
    helpers::serialization::save(message{event::set_player_id, true}, ss);
    godot::Godot::print(godot::String((std::to_string(event::set_player_id) + " to send").c_str()));
    client.write(ss.str());

    return true;
};

}
}
}
