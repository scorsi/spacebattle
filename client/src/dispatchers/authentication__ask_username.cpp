#include "authentication__ask_username.hpp"

#include "network/message.hpp"
#include "helpers/serialization.hpp"
#include "events/ask_username.hpp"
#include "events/set_username.hpp"
#include "event.hpp"

namespace dispatchers {
namespace authentication {
namespace ask_username {

bool dispatch_receive(network::client &client, std::stringstream &payload) {
    std::stringstream ss;
    helpers::serialization::save(network::message{event::set_username, true}, ss);
    helpers::serialization::save(events::set_username{"Scorsi"}, ss);
    client.deliver(network::packet::create_from_stream(ss));

    return true;
}

}
}
}
