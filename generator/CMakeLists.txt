cmake_minimum_required(VERSION 3.23)
project(generator C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/.out)

add_executable(generator main.c html-generator.c html-generator.h)
target_link_libraries(generator ${CMAKE_SOURCE_DIR}/css_library.a)

add_custom_command(TARGET ${CMAKE_PROJECT_NAME} PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets $<TARGET_FILE_DIR:${CMAKE_PROJECT_NAME}>/assets)
add_custom_command(TARGET ${CMAKE_PROJECT_NAME} PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/Receptu_tekstai $<TARGET_FILE_DIR:${CMAKE_PROJECT_NAME}>/Receptu_tekstai)

