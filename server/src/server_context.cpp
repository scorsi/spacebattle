#include "server_context.hpp"

#include <iostream>
#include "network/session.hpp"
#include "dispatcher.hpp"

server_context::server_context() {
    room_list_.push_back(std::make_shared<room>("Official room #1"));
    room_list_.push_back(std::make_shared<room>("Official room #2"));
    room_list_.push_back(std::make_shared<room>("Official room #3"));
    room_list_.push_back(std::make_shared<room>("Official room #4"));
    room_list_.push_back(std::make_shared<room>("Official room #5"));
}

void server_context::add_session(std::shared_ptr<network::session> session) {
    std::cout << "Adding session...";
    session_list_.push_back(session);
    std::cout << " done." << std::endl;
}

void server_context::add_room(std::shared_ptr<room> room) {
    room_list_.push_back(room);
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

const std::list<std::shared_ptr<network::session>> &server_context::get_session_list() const {
    return session_list_;
}

const std::list<std::shared_ptr<room>> &server_context::get_room_list() const {
    return room_list_;
}
