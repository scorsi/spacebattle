#include "dispatcher.hpp"

#include <map>
#include <functional>
#include <stdexcept>
#include "helpers/serialization.hpp"
#include "network/session.hpp"
#include "network/message.hpp"
#include "dispatchers/connection__set_client_id.hpp"
#include "dispatchers/authentication__ask_username.hpp"
#include "dispatchers/authentication__set_username.hpp"
#include "dispatchers/in_menu__fetch_room_info.hpp"
#include "dispatchers/in_menu__fetch_rooms.hpp"
#include "dispatchers/in_menu__create_room.hpp"
#include "dispatchers/in_menu__join_room.hpp"
#include "dispatchers/in_lobby__leave_room.hpp"
#include "dispatchers/in_lobby__player_joined.hpp"
#include "dispatchers/in_lobby__player_leaved.hpp"

namespace dispatcher {

using dispatcher_send_function_type = bool(const dispatch_context &);

using dispatcher_receive_function_type = bool(const network::message &,
                                              const dispatch_context &,
                                              std::stringstream &);

struct dispatcher_struct {
    std::function<dispatcher_send_function_type> dispatch_send;
    std::function<dispatcher_receive_function_type> dispatch_receive;
};

static const std::map<state, std::map<event, dispatcher_struct>> _dispatchers = { // NOLINT(cert-err58-cpp)
        {state::connection,
                {
                        {event::set_player_id,
                                {
                                        dispatchers::connection::set_player_id::dispatch_send,
                                        dispatchers::connection::set_player_id::dispatch_receive
                                }
                        }
                }
        },
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
        },
        {state::in_menu,
                {
                        {event::fetch_room_info,
                                {
                                        nullptr,
                                        dispatchers::in_menu::fetch_room_info::dispatch_receive
                                }
                        },
                        {event::fetch_rooms,
                                {
                                        nullptr,
                                        dispatchers::in_menu::fetch_rooms::dispatch_receive
                                }
                        },
                        {event::create_room,
                                {
                                        nullptr,
                                        dispatchers::in_menu::create_room::dispatch_receive
                                }
                        },
                        {event::join_room,
                                {
                                        nullptr,
                                        dispatchers::in_menu::join_room::dispatch_receive
                                }
                        }
                }
        },
        {state::in_lobby,
                {
                        {event::leave_room,
                                {
                                        nullptr,
                                        dispatchers::in_lobby::leave_room::dispatch_receive
                                }
                        },
                        {event::player_joined,
                                {
                                        dispatchers::in_lobby::player_joined::dispatch_send,
                                        nullptr
                                }
                        },
                        {event::player_leaved,
                                {
                                        dispatchers::in_lobby::player_leaved::dispatch_send,
                                        nullptr
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
                   const dispatch_context &context) {

    std::cout << "Event sent: " << event << ", dispatching status: ";

    auto b = find_dispatcher_and_run(
            context.session->get_context()->get_state(), event,
            [&](const dispatcher_struct &e) {
                if (e.dispatch_send != nullptr) return e.dispatch_send(context);
                else return false;
            });
    std::cout << b << "." << std::endl;
    return b;
}

bool dispatch_receive(const network::packet &packet,
                      const dispatch_context &context) {
    network::message message;
    {
        std::stringstream ss(std::string(packet.get_body(), MESSAGE_LENGTH));
        helpers::serialization::load(message, ss);
    }

    std::cout << "Event received: " << message.type << ", dispatching status: ";

    std::stringstream payload;

    if (packet.get_body_length() - MESSAGE_LENGTH > 0) {
        payload.write(packet.get_body() + MESSAGE_LENGTH,
                      packet.get_body_length() - MESSAGE_LENGTH);
    }

    auto b = find_dispatcher_and_run(
            context.session->get_context()->get_state(), message.type,
            [&](const dispatcher_struct &e) {
                if (e.dispatch_receive != nullptr) return e.dispatch_receive(message, context, payload);
                else return false;
            });
    std::cout << b << "." << std::endl;
    return b;
}

}
