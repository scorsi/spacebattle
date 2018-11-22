#include "packet.hpp"

#include <cstdlib>
#include <string>

namespace network {
    packet::packet()
            : body_length_(0) {
    }

    const char *packet::data() const {
        return data_;
    }

    char *packet::data() {
        return data_;
    }

    std::size_t packet::length() const {
        return header_length + body_length_;
    }

    const char *packet::body() const {
        return data_ + header_length;
    }

    char *packet::body() {
        return data_ + header_length;
    }

    std::size_t packet::body_length() const {
        return body_length_;
    }

    void packet::body_length(std::size_t new_length) {
        body_length_ = new_length;
    }

    bool packet::decode_header() {
        char header[header_length + 1] = "";
        std::strncat(header, data_, header_length);
        body_length_ = (std::size_t) std::atoi(header);
        if (body_length_ > max_body_length) {
            body_length_ = 0;
            return false;
        }
        return true;
    }

    void packet::encode_header() {
        char header[header_length + 1] = "";
        std::sprintf(header, "%4d", static_cast<int>(body_length_));
        std::memcpy(data_, header, header_length);
    }
}
