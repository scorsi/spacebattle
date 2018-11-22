#include "server_context.hpp"

#include <iostream>

namespace network {

server_context::server_context() {
}

void server_context::add_session(std::shared_ptr<network::session> session) {
    std::cout << "Adding session...";
    session_list_.push_back(session);
    std::cout << " done." << std::endl;
}

bool server_context::remove_session(const std::shared_ptr<network::session> &session) {
    std::cout << "Removing session...";
    auto e = std::end(session_list_);
    auto i = std::find(std::begin(session_list_), e, session);
    if (i != e) {
        session_list_.erase(i);
        std::cout << " done." << std::endl;
        return true;
    } else {
        std::cout << " fail." << std::endl;
        return false;
    }
}

void server_context::broadcast(const network::packet &packet) {
    std::for_each(std::begin(session_list_),
                  std::end(session_list_),
                  [&packet](std::shared_ptr<network::session> &session) {
                      session->deliver(packet);
                  });
}

}
