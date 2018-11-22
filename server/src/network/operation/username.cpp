#include "username.hpp"

namespace network {
namespace operation {
namespace username {

#define SERVER_VALID_SEND(id) (id == 0 || id == 2)
#define SERVER_VALID_RECEIVE(id) (id == 1)

#if OPERATION_SERVER == 1

bool is_valid_send(int id) {
    return SERVER_VALID_SEND(id);
}

bool is_valid_receive(const network::message &msg) {
    return SERVER_VALID_RECEIVE(msg.id);
}

bool handle_send(std::shared_ptr<network::session> session, int id) {
    if (is_valid_send(id)) {
        switch (id) {
            case 0: {
                network::packet packet;

                std::ostringstream ss;
                {
                    cereal::BinaryOutputArchive oar(ss);

                    network::message{
                            network::operation_type::username,
                            0,
                            network::operation_status::ok
                    }.serialize(oar);
                }
                auto s = ss.str();

                packet.body_length(s.length());
                std::memcpy(packet.body(), s.c_str(), packet.body_length());
                packet.encode_header();

                session->deliver(packet);
                break;
            }
            case 2: {
                network::packet packet;

                std::ostringstream ss;
                {
                    cereal::BinaryOutputArchive oar(ss);

                    network::message{
                            network::operation_type::username,
                            2,
                            network::operation_status::ok
                    }.serialize(oar);
                }
                auto s = ss.str();

                packet.body_length(s.length());
                std::memcpy(packet.body(), s.c_str(), packet.body_length());
                packet.encode_header();

                session->deliver(packet);
                break;
            }
        }
        return true;
    } else {
        return false;
    }
}

bool handle_receive(std::shared_ptr<network::session> session,
                    const network::message &msg,
                    cereal::BinaryInputArchive &iar) {
    if (is_valid_receive(msg)) {
        step_client_answer_username step;
        iar(step);
        session->get_context()->set_username(step.username);

        handle_send(std::move(session), 2);
        return true;
    } else {
        return false;
    }
}

#elif OPERATION_CLIENT == 1

bool is_valid_send(int id) {
    return SERVER_VALID_RECEIVE(id);
}

bool is_valid_receive(const network::message &msg) {
    return SERVER_VALID_SEND(msg.id);
}

#endif

#undef SERVER_VALID_SEND
#undef SERVER_VALID_RECEIVE

}
}
}
