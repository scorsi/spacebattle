#include "in_menu__join_room.hpp"

#include "room.hpp"

namespace dispatchers {
namespace in_menu {
namespace join_room {

bool dispatch_receive(const network::message &message, const dispatch_context &context, std::stringstream &payload) {
    std::string lobby_id;
    {
        cereal::BinaryInputArchive archive(payload);
        serialize::load_string(archive, lobby_id);
    }

    auto room_list = context.server->get_context()->get_room_list();
    auto r = std::find_if(
            std::begin(room_list), std::end(room_list),
            [&lobby_id](const std::shared_ptr<room> &room) {
                return room->get_id() == lobby_id;
            });

    if (r == std::end(room_list)) {
        std::stringstream ss;
        {
            cereal::BinaryOutputArchive archive(ss);
            archive(network::message{event::join_room, false});
            serialize::save_string(archive, std::string("room_do_not_exists"));
        }
        context.session->deliver(network::packet::create_from_stream(ss));
        return false;
    } else if ((*r)->get_players().size() >= 2) {
        std::stringstream ss;
        {
            cereal::BinaryOutputArchive archive(ss);
            archive(network::message{event::join_room, false});
            serialize::save_string(archive, std::string("room_is_full"));
        }
        context.session->deliver(network::packet::create_from_stream(ss));
        return false;
    } else {
        (*r)->add_player(context.session);
        context.session->get_context()->set_room(*r);
        std::stringstream ss;
        {
            cereal::BinaryOutputArchive archive(ss);
            archive(network::message{event::join_room, true});
        }
        context.session->deliver(network::packet::create_from_stream(ss));
        return true;
    }
}

}
}
}
