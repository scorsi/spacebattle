#include "authentication__ask_username.hpp"

#include <cereal/archives/binary.hpp>
#include "network/message.hpp"
#include "events/ask_username.hpp"
#include "event.hpp"

namespace dispatchers {
namespace authentication {
namespace set_username {

bool dispatch_receive(std::shared_ptr<session_context> session_context,
                      std::stringstream &in,
                      std::stringstream &out) {
    cereal::BinaryOutputArchive archive(out);
    archive(network::message{event::set_username, true});
    return true;
}

}
}
}
