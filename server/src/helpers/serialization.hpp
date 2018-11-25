#pragma once

#include <sstream>
#include <cereal/archives/binary.hpp>
#include "serialize/string.hpp"

namespace helpers {
namespace serialization {

template<typename T>
void load(T &data, std::stringstream &payload) {
    cereal::BinaryInputArchive archive(payload);
    archive(data);
}

template<>
void load(std::string &data, std::stringstream &payload) {
    cereal::BinaryInputArchive archive(payload);
    serialize::load_string(archive, data);
}

template<typename T>
void save(const T &data, std::stringstream &payload) {
    cereal::BinaryOutputArchive archive(payload);
    archive(data);
}

template<>
void save(const std::string &data, std::stringstream &payload) {
    cereal::BinaryInputArchive archive(payload);
    serialize::save_string(archive, data);
}

}
}
