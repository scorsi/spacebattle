#pragma once

#include <memory>
#include "packet.hpp"
#include "message.hpp"

namespace network {

class session;

namespace packet_handler {

std::unique_ptr<network::packet> dispatch(std::shared_ptr<network::session> session,
                                          cereal::BinaryInputArchive &archive,
                                          const network::message &msg);

void do_handle(std::shared_ptr<network::session> session,
               const network::packet &packet);

}

}
