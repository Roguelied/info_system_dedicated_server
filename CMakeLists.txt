cmake_minimum_required(VERSION 3.23)
project(info_system_dedicated_server)

set(CMAKE_CXX_STANDARD 23)

add_executable(info_system_dedicated_server main.cpp Server.cpp Server.h Database.cpp Database.h Utility.cpp Utility.h)
