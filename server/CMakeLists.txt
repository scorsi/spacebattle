cmake_minimum_required(VERSION 3.5)
project(spacebattle_server)
set(CMAKE_CXX_STANDARD 17)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

include_directories(src)

add_executable(spacebattle_server src/main.cpp src/network/server.cpp src/network/session.cpp src/network/packet.cpp src/network/session_context.cpp src/network/server_context.cpp src/network/protocol/writer.cpp src/network/protocol/writer.hpp src/network/protocol/reader.cpp src/network/protocol/reader.hpp src/network/protocol/model/username.cpp src/network/protocol/model/username.hpp src/network/protocol/base_model.cpp src/network/protocol/base_model.hpp src/network/protocol/operation.hpp src/network/protocol/operation_status.hpp)
target_link_libraries(spacebattle_server ${CONAN_LIBS})