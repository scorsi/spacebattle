#pragma once

#include <memory>
#include "packet.hpp"

namespace network {

class session;

class packet_handler {
public:
    static void do_handle(std::shared_ptr<network::session> session, const network::packet &packet);
};

}
