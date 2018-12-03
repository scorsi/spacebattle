#include "in_menu__create_room.hpp"

#include "room.hpp"

namespace dispatchers {
namespace in_menu {
namespace create_room {

bool dispatch_receive(const network::message &message, const dispatch_context &context, std::stringstream &payload) {
    std::string lobby_name;
    std::uint16_t game_type;
    {
        cereal::BinaryInputArchive archive(payload);
        serialize::load_string(archive, lobby_name);
        archive(game_type);
    }

    auto room_list = context.server->get_context()->get_room_list();
    auto found = std::find_if(
            std::begin(room_list), std::end(room_list),
            [&lobby_name](const std::shared_ptr<room> &room) {
                return room->get_name() == lobby_name;
            });

    if (found == std::end(room_list)) {
        auto r = std::make_shared<room>(lobby_name);
        r->add_player(context.session);
        context.session->get_context()->set_room(r);
        context.server->get_context()->add_room(r);

        std::stringstream ss;
        {
            cereal::BinaryOutputArchive archive(ss);
            archive(network::message{event::create_room, true});
            serialize::save_string(archive, r->get_id());
        }
        context.session->deliver(network::packet::create_from_stream(ss));
        return true;
    } else {
        std::stringstream ss;
        {
            cereal::BinaryOutputArchive archive(ss);
            archive(network::message{event::create_room, false});
            serialize::save_string(archive, std::string("room_name_already_taken"));
        }
        context.session->deliver(network::packet::create_from_stream(ss));
        return false;
    }
}

}
}
}
