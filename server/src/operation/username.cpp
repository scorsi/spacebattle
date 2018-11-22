#include "username.hpp"

namespace operation {
namespace username {

std::unique_ptr<network::packet> handle_send(std::shared_ptr<network::session> session, int id) {
    switch (id) {
        case 0: {
            network::packet packet;

            std::ostringstream ss;
            {
                cereal::BinaryOutputArchive oar(ss);
                network::message{OPERATION_USERNAME_ID, 0, true}.serialize(oar);
            }
            auto s = ss.str();

            packet.body_length(s.length());
            std::memcpy(packet.body(), s.c_str(), packet.body_length());
            packet.encode_header();

            return std::make_unique<network::packet>(packet);
        }
        case 2: {
            network::packet packet;

            std::ostringstream ss;
            {
                cereal::BinaryOutputArchive oar(ss);
                network::message{OPERATION_USERNAME_ID, 2, true}.serialize(oar);
            }
            auto s = ss.str();

            packet.body_length(s.length());
            std::memcpy(packet.body(), s.c_str(), packet.body_length());
            packet.encode_header();

            return std::make_unique<network::packet>(packet);
        }
        default: return nullptr;
    }
}

std::unique_ptr<network::packet> handle_receive(std::shared_ptr<network::session> session,
                                                const network::message &msg,
                                                cereal::BinaryInputArchive &iar) {
    switch (msg.id) {
        case 1: {
            step_client_answer_username step;
            iar(step);
            session->get_context()->set_username(step.username);

            return handle_send(std::move(session), 2);
        }
        default:return nullptr;
    }
}

}
}
