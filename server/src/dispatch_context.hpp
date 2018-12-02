#pragma once

#include <memory>
#include "network/server.hpp"
#include "network/session.hpp"

struct dispatch_context {
    std::shared_ptr<network::server> server;
    std::shared_ptr<network::session> session;
};
