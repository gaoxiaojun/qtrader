cmake_minimum_required(VERSION 2.8.9)

CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/app_config.h.in ${CMAKE_CURRENT_BINARY_DIR}/app_config.h)

add_subdirectory(gui)
#add_subdirectory(cli)
