#pragma once

#include <cstddef>
#include <cstdlib>
#include <string>
#include <cereal/archives/binary.hpp>

namespace network {

#define PACKET_HEADER_LENGTH (sizeof(std::size_t))
#define PACKET_BODY_LENGTH (1024)

class packet {
public:
    packet()
            : body_length_(0),
              data_("") {
    }

    const char *data() const {
        return data_;
    }

    char *data() {
        return data_;
    }

    std::size_t length() const {
        return PACKET_HEADER_LENGTH + body_length_;
    }

    const char *body() const {
        return data_ + PACKET_HEADER_LENGTH;
    }

    char *body() {
        return data_ + PACKET_HEADER_LENGTH;
    }

    std::size_t body_length() const {
        return body_length_;
    }

    void body_length(std::size_t new_length) {
        body_length_ = new_length;
    }

    bool decode_header() {
        char header[PACKET_HEADER_LENGTH + 1] = "";
        std::istringstream ss(std::string(data_, PACKET_HEADER_LENGTH));
        cereal::BinaryInputArchive archive(ss);
        std::size_t length;
        archive(length);
        body_length_ = length;
        return true;
    }

    void encode_header() {
        char header[PACKET_HEADER_LENGTH + 1] = "";
        std::ostringstream ss;
        {
            cereal::BinaryOutputArchive archive(ss);
            archive(body_length_);
        }
        std::memcpy(data_, ss.str().c_str(), PACKET_HEADER_LENGTH);
    }

private:
    char data_[PACKET_HEADER_LENGTH + PACKET_BODY_LENGTH];
    std::size_t body_length_;
};

}
