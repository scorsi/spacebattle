#pragma once

#include <string>
#include <cereal/archives/binary.hpp>

namespace network {
namespace serialize {

template<class Archive>
void save_string(Archive &ar, std::string const &s) {
    auto l = s.length();
    ar(l, cereal::binary_data(s.c_str(), l));
}

template<class Archive>
void load_string(Archive &ar, std::string &s) {
    std::size_t l = 0;
    ar(l);
    char cs[l + 1];
    cs[l] = '\0';
    ar(cereal::binary_data<char *>(cs, l));
    s = cs;
}

}
}
