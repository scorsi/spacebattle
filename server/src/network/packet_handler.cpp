#include "packet_handler.hpp"

#include <cereal/archives/binary.hpp>
#include "network/session.hpp"
#include "operation/username.hpp"
#include "message.hpp"

namespace network {
namespace packet_handler {

std::unique_ptr<network::packet> dispatch(std::shared_ptr<network::session> session,
                                          cereal::BinaryInputArchive &archive,
                                          const network::message &msg) {
    switch (msg.type) {
        case OPERATION_USERNAME_ID: return operation::username::handle_receive(std::move(session), msg, archive);
        default: return nullptr;
    }
}

void do_handle(std::shared_ptr<network::session> session,
               const network::packet &packet) {
    std::istringstream ss(std::string(packet.body(), packet.body_length()));

    cereal::BinaryInputArchive ar(ss);
    network::message msg;

    ar(msg);

    auto packet_to_send = dispatch(session, ar, msg);
    if (packet_to_send.get() != nullptr) {
        session->deliver(*packet_to_send);
    }
}

}
}
