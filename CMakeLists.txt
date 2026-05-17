cmake_minimum_required(VERSION 3.13)

project(ezio)

add_library(ezio)
target_include_directories(ezio PUBLIC include PRIVATE src)

add_executable(client)
target_link_libraries(client PRIVATE ezio)
target_include_directories(client PRIVATE src/Client)

add_subdirectory(src)
add_subdirectory(include)
add_subdirectory(example)

# create resources symlink in build directory
set(RESOURCE_DIR "resources/")
add_custom_command(TARGET client POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E create_symlink
    ${CMAKE_SOURCE_DIR}/${RESOURCE_DIR}
    $<TARGET_FILE_DIR:client>/${RESOURCE_DIR}
)

target_compile_definitions(client PRIVATE
    RESOURCE_PATH=\"${RESOURCE_DIR}\"
)