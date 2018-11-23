#pragma once

#include <sstream>
#include <cereal/archives/binary.hpp>

namespace helpers {
namespace serialization {

template<typename T>
void load(T &data, std::stringstream &payload) {
    cereal::BinaryInputArchive archive(payload);
    archive(data);
}

template<typename T>
void save(const T &data, std::stringstream &payload) {
    cereal::BinaryOutputArchive archive(payload);
    archive(data);
}

}
}
