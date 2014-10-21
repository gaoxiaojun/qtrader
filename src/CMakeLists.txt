cmake_minimum_required(VERSION 2.8.9)

SET(SRC_ROOT_DIR "${CMAKE_CURRENT_SOURCE_DIR}" CACHE INTERNAL "" FORCE)
SET(BINARY_ROOT_DIR "${CMAKE_CURRENT_BINARY_DIR}" CACHE INTERNAL "" FORCE)

add_subdirectory(external)
add_subdirectory(libs)
add_subdirectory(app)
add_subdirectory(plugins)
