#include "connection__set_client_id.hpp"

#include "network/message.hpp"
#include "helpers/serialization.hpp"
#include "authentication__ask_username.hpp"

namespace dispatchers {
namespace connection {
namespace set_player_id {

bool dispatch_send(const dispatch_context &context) {
    std::stringstream ss;
    helpers::serialization::save(network::message{event::set_player_id, true}, ss);
    helpers::serialization::save(context.session->get_id(), ss);
    context.session->deliver(network::packet::create_from_stream(ss));

    context.session->get_context()->set_state(state::authentication);

    return true;
}

bool dispatch_receive(const network::message &message, const dispatch_context &context, std::stringstream &payload) {
    authentication::ask_username::dispatch_send(context);
    return true;
}

}
}
}
