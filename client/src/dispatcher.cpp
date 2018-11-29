#include "dispatcher.hpp"

#include <map>
#include <functional>
#include <stdexcept>
#include <core/Godot.hpp>
#include "helpers/serialization.hpp"
#include "message.hpp"
#include "dispatchers/authentication__ask_username.hpp"
#include "dispatchers/authentication__set_username.hpp"
#include "client.hpp"

namespace dispatcher {

using dispatcher_function= std::function<bool(godot::client &, std::stringstream &)>;

static const std::map<state, std::map<event, dispatcher_function>> _dispatchers = { // NOLINT(cert-err58-cpp)
        {state::authentication,
                {
                        {event::ask_username, dispatchers::authentication::ask_username::dispatch},
                        {event::set_username, dispatchers::authentication::set_username::dispatch}
                }
        }
};

bool find_dispatcher_and_run(const state &state,
                             const event &event,
                             const std::function<bool(dispatcher_function)> &f) {
    try {
        return f(_dispatchers.at(state).at(event));
    } catch (std::out_of_range &) {
        return false;
    }
}

bool dispatch(const std::string &packet,
              const message &message,
              godot::client &client) {
    std::stringstream payload;

    if (packet.length() - MESSAGE_LENGTH > 0) {
        payload.write(packet.c_str() + MESSAGE_LENGTH,
                      packet.length() - MESSAGE_LENGTH);
    }

    return find_dispatcher_and_run(
            client.get_context().get_state(), message.type,
            [&](dispatcher_function f) {
                if (f != nullptr) return f(client, payload);
                else return false;
            });
}

}
