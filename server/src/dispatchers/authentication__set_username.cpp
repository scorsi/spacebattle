#include "authentication__ask_username.hpp"

#include <cereal/archives/binary.hpp>
#include "network/message.hpp"
#include "events/ask_username.hpp"
#include "event.hpp"

namespace dispatchers {
namespace authentication {
namespace set_username {

bool dispatch_receive(const std::shared_ptr<network::session> &session, std::stringstream &payload) {
    std::stringstream ss;
    {
        cereal::BinaryOutputArchive archive(ss);
        archive(network::message{event::set_username, true});
    }
    session->deliver(network::packet::create_from_stream(ss));
    return true;
}

}
}
}
