#include "username.hpp"

namespace operation {
namespace username {

std::unique_ptr<network::packet> handle_send(std::shared_ptr<network::session> session, int id) {
    switch (id) {
        case 0: {
            std::stringstream ss;
            {
                cereal::BinaryOutputArchive archive(ss);
                archive(network::message{OPERATION_USERNAME_ID, 0, true});
            }
            return std::make_unique<network::packet>(network::packet::create_from_stream(ss));
        }
        case 2: {
            std::stringstream ss;
            {
                cereal::BinaryOutputArchive archive(ss);
                archive(network::message{OPERATION_USERNAME_ID, 2, true});
            }
            return std::make_unique<network::packet>(network::packet::create_from_stream(ss));
        }
        default: return nullptr;
    }
}

std::unique_ptr<network::packet> handle_receive(std::shared_ptr<network::session> session,
                                                const network::message &msg,
                                                cereal::BinaryInputArchive &archive) {
    switch (msg.id) {
        case 1: {
            step_client_answer_username step;
            archive(step);
            session->get_context()->set_username(step.username);

            return handle_send(std::move(session), 2);
        }
        default: return nullptr;
    }
}

}
}
