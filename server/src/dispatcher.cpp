#include "dispatcher.hpp"

#include <map>
#include <functional>
#include <stdexcept>
#include "helpers/serialization.hpp"
#include "network/session.hpp"
#include "network/message.hpp"
#include "dispatchers/authentication__ask_username.hpp"
#include "dispatchers/authentication__set_username.hpp"

namespace dispatcher {

using dispatcher_send_function_type = bool(const std::shared_ptr<network::session> &);

using dispatcher_receive_function_type = bool(const std::shared_ptr<network::session> &, std::stringstream &);

struct dispatcher_struct {
    std::function<dispatcher_send_function_type> dispatch_send;
    std::function<dispatcher_receive_function_type> dispatch_receive;
};

static const std::map<state, std::map<event, dispatcher_struct>> _dispatchers = { // NOLINT(cert-err58-cpp)
        {state::authentication,
                {
                        {event::ask_username,
                                {
                                        dispatchers::authentication::ask_username::dispatch_send,
                                        nullptr
                                }
                        },
                        {event::set_username,
                                {
                                        nullptr,
                                        dispatchers::authentication::set_username::dispatch_receive
                                }
                        }
                }
        }
};

bool find_dispatcher_and_run(const state &state,
                             const event &event,
                             const std::function<bool(const dispatcher_struct &)> &f) {
    try {
        return f(_dispatchers.at(state).at(event));
    } catch (std::out_of_range &) {
        return false;
    }
}

bool dispatch_send(const event &event,
                   const std::shared_ptr<network::session> &session) {
    return find_dispatcher_and_run(
            session->get_context()->get_state(), event,
            [&](const dispatcher_struct &e) {
                if (e.dispatch_send != nullptr) return e.dispatch_send(session);
                else return false;
            });
}

bool dispatch_receive(const network::packet &packet,
                      const std::shared_ptr<network::session> &session) {
    network::message message;
    {
        std::stringstream ss(std::string(packet.get_body(), sizeof(network::message)));
        helpers::serialization::load(message, ss);
    }

    std::stringstream payload;

    if (packet.get_body_length() - sizeof(network::message) > 0) {
        payload.write(packet.get_body() + sizeof(network::message),
                      packet.get_body_length() - sizeof(network::message));
    }

    return find_dispatcher_and_run(
            session->get_context()->get_state(), message.type,
            [&](const dispatcher_struct &e) {
                if (e.dispatch_receive != nullptr) return e.dispatch_receive(session, payload);
                else return false;
            });
}

}
