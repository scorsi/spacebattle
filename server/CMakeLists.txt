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

        src/helpers/serialization.cpp

        src/network/server.cpp
        src/server_context.cpp
        src/network/session.cpp
        src/session_context.cpp
        src/room.cpp

        src/dispatcher.cpp

        src/dispatchers/connection__set_client_id.cpp
        src/dispatchers/authentication__ask_username.cpp
        src/dispatchers/authentication__set_username.cpp
        )

target_link_libraries(spacebattle_server ${CONAN_LIBS})