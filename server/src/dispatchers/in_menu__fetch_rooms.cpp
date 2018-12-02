#include "in_menu__fetch_rooms.hpp"

namespace dispatchers {
namespace in_menu {
namespace fetch_rooms {

bool dispatch_receive(const network::message &, const dispatch_context &context, std::stringstream &) {
    std::stringstream ss;
    {
        cereal::BinaryOutputArchive ar(ss);

        ar(network::message{event::fetch_rooms, true});
        auto s = std::uint32_t(context.server->get_context()->get_room_list().size());
        ar(s);
        if (s != 0) {
            for (auto &r : context.server->get_context()->get_room_list()) {
                ar(*r);
            }
        }
    }
    context.session->deliver(network::packet::create_from_stream(ss));

    return true;
}

}
}
}
