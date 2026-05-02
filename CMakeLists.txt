cmake_minimum_required(VERSION 3.13)

project(ezio)

add_library(ezio)

add_executable(client)
target_link_libraries(client PRIVATE ezio)

add_subdirectory(EzIO)
add_subdirectory(Client)
target_include_directories(ezio PUBLIC EzIO/src)
target_include_directories(client PRIVATE Client/src)