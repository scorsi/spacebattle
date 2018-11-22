#include "packet_handler.hpp"

#include <cereal/archives/binary.hpp>
#include "network/session.hpp"
#include "network/operation/username.hpp"
#include "message.hpp"

namespace network {

void packet_handler::do_handle(std::shared_ptr<network::session> session,
                               const network::packet &packet) {
    std::istringstream ss(std::string(packet.body(), packet.body_length()));

    cereal::BinaryInputArchive ar(ss);
    network::message msg;

    ar(msg);

    switch (msg.type) {
        case username: {
            network::operation::username::handle_receive(std::move(session), msg, ar);
            break;
        }
        default: {

        }
    }
}

}
