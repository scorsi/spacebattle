cmake_minimum_required(VERSION 3.5)
project(spacebattle_client)
set(CMAKE_CXX_STANDARD 14)

include_directories(godot-cpp/include)

add_executable(spacebattle_client
        src/gdlibrary.cpp

        src/gdexample.cpp
        )
target_link_libraries(spacebattle_client)