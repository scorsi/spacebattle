cmake_minimum_required(VERSION 3.5)
project(spacebattle_client)
set(CMAKE_CXX_STANDARD 14)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

include_directories(
        src
        godot-cpp/include
        godot_headers
)

add_executable(spacebattle_client
        src/gdlibrary.cpp
        src/client.cpp
        src/client_send_methods.cpp
        src/room.cpp

        src/context.cpp
        src/dispatcher.cpp

        src/dispatchers/connection__set_client_id.cpp
        src/dispatchers/authentication__ask_username.cpp
        src/dispatchers/authentication__set_username.cpp
        src/dispatchers/in_menu__fetch_rooms.cpp
        src/dispatchers/in_menu__create_room.cpp
        src/dispatchers/in_menu__join_room.cpp
        )
target_link_libraries(spacebattle_client ${CONAN_LIBS})