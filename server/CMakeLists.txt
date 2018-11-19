cmake_minimum_required(VERSION 3.5)
project(spacebattle_server)
set(CMAKE_CXX_STANDARD 14)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

include_directories(src)

add_executable(spacebattle_server src/main.cpp)
target_link_libraries(spacebattle_server ${CONAN_LIBS})