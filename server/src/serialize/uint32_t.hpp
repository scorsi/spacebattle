#pragma once

#include <string>
#include <cereal/archives/binary.hpp>

namespace serialize {

template<class Archive>
void save_uint32t(Archive &ar, std::uint32_t const &i) {
    char cs[sizeof(std::uint32_t)];
    cs[0] = static_cast<char>((i >> 24) & 0xff);
    cs[1] = static_cast<char>((i >> 16) & 0xff);
    cs[2] = static_cast<char>((i >> 8) & 0xff);
    cs[3] = static_cast<char>((i) & 0xff);
    ar(sizeof(std::uint32_t), cereal::binary_data(cs, sizeof(std::uint32_t)));
}

template<class Archive>
void load_uint32t(Archive &ar, std::uint32_t &i) {
    char cs[sizeof(std::uint32_t)];
    ar(cereal::binary_data<char *>(cs, sizeof(std::uint32_t)));
    auto s = std::string(cs, sizeof(std::uint32_t));
    i = std::uint32_t((s[0] << 24) | (s[1] << 16) | (s[2] << 8) | (s[3]));
}

}
