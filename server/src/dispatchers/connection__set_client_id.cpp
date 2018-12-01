#include "connection__set_client_id.hpp"

#include "network/message.hpp"
#include "helpers/serialization.hpp"
#include "authentication__ask_username.hpp"

namespace dispatchers {
namespace connection {
namespace set_player_id {

bool dispatch_send(const std::shared_ptr<network::session> &session) {
    std::stringstream ss;
    helpers::serialization::save(network::message{event::set_player_id, true}, ss);
    helpers::serialization::save(session->get_id(), ss);
    session->deliver(network::packet::create_from_stream(ss));

    session->get_context()->set_state(state::authentication);

    return true;
}

bool dispatch_receive(const network::message &message, const std::shared_ptr<network::session> &session, std::stringstream &payload) {
    authentication::ask_username::dispatch_send(session);
    return true;
}

}
}
}
