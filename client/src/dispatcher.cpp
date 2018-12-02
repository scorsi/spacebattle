#include "dispatcher.hpp"

#include <map>
#include <functional>
#include <stdexcept>
#include <core/Godot.hpp>
#include "helpers/serialization.hpp"
#include "client.hpp"
#include "message.hpp"
#include "dispatchers/connection__set_client_id.hpp"
#include "dispatchers/authentication__ask_username.hpp"
#include "dispatchers/authentication__set_username.hpp"

namespace dispatcher {

using dispatcher_function= std::function<bool(cereal::BinaryInputArchive &, const message &, godot::client &)>;

static const std::map<state, std::map<event, dispatcher_function>> _dispatchers = { // NOLINT(cert-err58-cpp)
        {state::connection,
                {
                        {event::set_player_id, dispatchers::connection::set_player_id::dispatch}
                }

        },
        {state::authentication,
                {
                        {event::ask_username,  dispatchers::authentication::ask_username::dispatch},
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

bool dispatch_receive(cereal::BinaryInputArchive &ar,
                      const message &message,
                      godot::client &client) {
    return find_dispatcher_and_run(
            client.get_context().get_state(), message.type,
            [&](dispatcher_function f) {
                if (f != nullptr) return f(ar, message, client);
                else return false;
            });
}

}
