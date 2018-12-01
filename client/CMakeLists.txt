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

        src/context.cpp
        src/dispatcher.cpp

        src/dispatchers/connection__set_client_id.cpp
        src/dispatchers/authentication__ask_username.cpp
        src/dispatchers/authentication__set_username.cpp
        )
target_link_libraries(spacebattle_client ${CONAN_LIBS})