cmake_minimum_required(VERSION 3.5)
project(spacebattle_server)

set(CMAKE_CXX_STANDARD 14)

add_compile_definitions(spacebattle_server
        OPERATION_SERVER=1
        OPERATION_CLIENT=0)


include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()



include_directories(src)

add_executable(spacebattle_server
        src/main.cpp
        
        src/network/server.cpp
        src/network/server_context.cpp
        src/network/session.cpp
        src/network/session_context.cpp
        src/network/packet_handler.cpp

        src/operation/username.cpp )

target_link_libraries(spacebattle_server ${CONAN_LIBS})