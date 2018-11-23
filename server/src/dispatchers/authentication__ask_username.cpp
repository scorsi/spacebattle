#include "authentication__ask_username.hpp"

#include <cereal/archives/binary.hpp>
#include "network/message.hpp"
#include "events/ask_username.hpp"
#include "event.hpp"

namespace dispatchers {
namespace authentication {
namespace ask_username {

bool dispatch_send(std::shared_ptr<session_context> session_context,
                   std::stringstream &in,
                   std::stringstream &out) {
    cereal::BinaryOutputArchive archive(out);
    archive(network::message{event::ask_username, true});
    return true;
}

}
}
}
