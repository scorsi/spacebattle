#pragma once

#include <cstddef>
#include <cstdlib>
#include <string>
#include <cereal/archives/binary.hpp>

namespace network {

#define PACKET_HEADER_LENGTH (sizeof(std::uint32_t))
#define PACKET_BODY_LENGTH (1024)

class packet {
public:
    packet()
            : body_length_(0),
              header_(""),
              body_("") {
    }

    const char *get_header() const {
        return header_;
    }

    char *get_header() {
        return header_;
    }

    const char *get_body() const {
        return body_;
    }

    char *get_body() {
        return body_;
    }

    std::uint32_t get_body_length() const {
        return body_length_;
    }

    void set_body_length(std::uint32_t new_length) {
        body_length_ = new_length;
    }

    bool decode_header() {
        std::istringstream ss(std::string(header_, PACKET_HEADER_LENGTH));
        cereal::BinaryInputArchive archive(ss);
        std::uint32_t length;
        archive(length);
        body_length_ = length;
        return true;
    }

    void encode_header() {
        std::ostringstream ss;
        {
            cereal::BinaryOutputArchive archive(ss);
            archive(body_length_);
        }
        std::memcpy(header_, ss.str().c_str(), PACKET_HEADER_LENGTH);
    }

    std::vector<char> create_full_packet() {
        auto full_packet = std::vector<char>(get_full_packet_length());
        for (int i = 0; i < PACKET_HEADER_LENGTH; i++) {
            full_packet[i] = header_[i];
        }
        for (int i = 0; i < body_length_; i++) {
            full_packet[PACKET_HEADER_LENGTH + i] = body_[i];
        }

        return full_packet;
    }

    std::uint32_t get_full_packet_length() {
        return PACKET_HEADER_LENGTH + body_length_;
    }

    static packet create_from_stream(const std::stringstream &stream) {
        network::packet p;
        auto s = stream.str();

        p.set_body_length(std::uint32_t(s.length()));
        std::memcpy(p.get_body(), s.c_str(), std::size_t(p.get_body_length()));
        p.encode_header();

        return p;
    }

private:
    char header_[PACKET_HEADER_LENGTH];
    char body_[PACKET_BODY_LENGTH];
    std::uint32_t body_length_;
};

}
