#include "authentication__ask_username.hpp"

#include "network/message.hpp"
#include "helpers/serialization.hpp"
#include "events/ask_username.hpp"
#include "event.hpp"

namespace dispatchers {
namespace authentication {
namespace ask_username {

bool dispatch_send(const dispatch_context &context) {
    std::stringstream ss;
    helpers::serialization::save(network::message{event::ask_username, true}, ss);
    context.session->deliver(network::packet::create_from_stream(ss));
    return true;
}

}
}
}
