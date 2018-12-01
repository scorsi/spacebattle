#pragma once

#include <memory>
#include "network/session.hpp"
#include "event.hpp"
#include "state.hpp"
#include "network/message.hpp"

namespace dispatchers {
namespace connection {
namespace set_player_id {

bool dispatch_send(const std::shared_ptr<network::session> &session);

bool dispatch_receive(const network::message &message, const std::shared_ptr<network::session> &session, std::stringstream &payload);

}
}
}
