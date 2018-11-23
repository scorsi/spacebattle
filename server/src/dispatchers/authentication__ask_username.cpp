#include "authentication__ask_username.hpp"

#include "network/message.hpp"
#include "helpers/serialization.hpp"
#include "events/ask_username.hpp"
#include "event.hpp"

namespace dispatchers {
namespace authentication {
namespace ask_username {

bool dispatch_send(const std::shared_ptr<network::session> &session) {
    std::stringstream ss;
    helpers::serialization::save(network::message{event::ask_username, true}, ss);
    session->deliver(network::packet::create_from_stream(ss));
    return true;
}

}
}
}
