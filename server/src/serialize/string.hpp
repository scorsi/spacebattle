#pragma once

#include <string>
#include <cereal/archives/binary.hpp>

namespace serialize {

template<class Archive>
void save_string(Archive &ar, const std::string &s) {
    auto l = s.length();
    ar(std::uint32_t(l));
    ar(cereal::binary_data<const char *>(s.c_str(), l));
}

template<class Archive>
void load_string(Archive &ar, std::string &s) {
    std::uint32_t l = 0;
    ar(l);
    char cs[l + 1];
    cs[l] = '\0';
    ar(cereal::binary_data<char *>(cs, std::size_t(l)));
    s = std::string(cs, std::size_t(l));
}

}
