cmake_minimum_required(VERSION 3.23)
project(info_system_dedicated_server)

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${GCC_COVERAGE_LINK_FLAGS} -static -lws2_32")
link_libraries(ws2_32 wsock32)


add_executable(info_system_dedicated_server main.cpp Server.cpp Server.h Database.cpp Database.h Utility.cpp Utility.h)
