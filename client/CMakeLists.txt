cmake_minimum_required(VERSION 3.5)
project(spacebattle_client)
set(CMAKE_CXX_STANDARD 14)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_executable(spacebattle_client src/main.cpp)
target_link_libraries(spacebattle_client ${CONAN_LIBS})