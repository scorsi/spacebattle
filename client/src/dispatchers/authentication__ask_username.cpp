#include "authentication__ask_username.hpp"

#include <core/Godot.hpp>
#include "message.hpp"
#include "helpers/serialization.hpp"
#include "events/ask_username.hpp"
#include "events/set_username.hpp"
#include "event.hpp"
#include "client.hpp"

namespace dispatchers {
namespace authentication {
namespace ask_username {

bool dispatch(godot::client &client, std::stringstream &payload) {
    std::stringstream ss;
    helpers::serialization::save(message{event::set_username, true}, ss);
    helpers::serialization::save(events::set_username{"Scorsi"}, ss);
    godot::Godot::print(godot::String((std::to_string(event::set_username) + " to send").c_str()));
    client.write(ss.str());

    return true;
}

}
}
}
