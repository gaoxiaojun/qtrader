set(library_name luajit)

cmake_minimum_required(VERSION 2.8.9)
include(ExternalProject)

project(${library_name})

set(luajit_version 2.0.2)

set_directory_properties(PROPERTIES EP_BASE ${CMAKE_BINARY_DIR}/third_party)

ExternalProject_Add(external_luajit
  URL http://luajit.org/download/LuaJIT-${luajit_version}.tar.gz
  UPDATE_COMMAND ${CMAKE_COMMAND} -E copy
     "${CMAKE_CURRENT_SOURCE_DIR}/${library_name}.cmake" ${CMAKE_BINARY_DIR}/third_party/Source/external_${library_name}/CMakeLists.txt
  INSTALL_COMMAND ""
)
