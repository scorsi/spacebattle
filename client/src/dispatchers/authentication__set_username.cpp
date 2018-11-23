#include "authentication__ask_username.hpp"

#include "network/message.hpp"
#include "events/set_username.hpp"
#include "event.hpp"
#include "helpers/serialization.hpp"

namespace dispatchers {
namespace authentication {
namespace set_username {

bool dispatch_receive(const std::shared_ptr<network::client> &client, std::stringstream &payload) {
    events::set_username event;
    helpers::serialization::load(event, payload);

    //session->get_context()->set_username(event.username);

    std::stringstream ss;
    helpers::serialization::save(network::message{event::set_username, true}, ss);
    client->deliver(network::packet::create_from_stream(ss));

    return true;
}

}
}
}
