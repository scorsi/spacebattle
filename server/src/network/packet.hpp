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

    const char *get_data() const {
        return data_;
    }

    char *get_data() {
        return data_;
    }

    std::size_t get_length() const {
        return PACKET_HEADER_LENGTH + body_length_;
    }

    const char *get_body() const {
        return data_ + PACKET_HEADER_LENGTH;
    }

    char *get_body() {
        return data_ + PACKET_HEADER_LENGTH;
    }

    std::size_t get_body_length() const {
        return body_length_;
    }

    void set_body_length(std::size_t new_length) {
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

    static packet create_from_stream(const std::stringstream &stream) {
        network::packet p;
        auto s = stream.str();

        p.set_body_length(s.length());
        std::memcpy(p.get_body(), s.c_str(), p.get_body_length());
        p.encode_header();

        return p;
    }

private:
    char data_[PACKET_HEADER_LENGTH + PACKET_BODY_LENGTH];
    std::size_t body_length_;
};

}
