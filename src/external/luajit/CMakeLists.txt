set(library_name luajit)

cmake_minimum_required(VERSION 2.8.9)
include(ExternalProject)

project(${library_name})

set(luajit_version 2.0.2)

ExternalProject_Add(external_luajit
  URL http://luajit.org/download/LuaJIT-${luajit_version}.tar.gz
  PREFIX ${CMAKE_CURRENT_BINARY_DIR}/luajit-${luajit_version}
  CONFIGURE_COMMAND ""
  BUILD_COMMAND make
  INSTALL_COMMAND make install PREFIX=${CMAKE_CURRENT_BINARY_DIR}/luajit-${luajit_version}
  BUILD_IN_SOURCE 1
)

ExternalProject_Get_Property(external_luajit install_dir)

install(DIRECTORY ${install_dir}/bin/ DESTINATION bin)
install(DIRECTORY ${install_dir}/lib/ DESTINATION lib)
install(DIRECTORY ${install_dir}/include/ DESTINATION include)


string(TOUPPER ${library_name} project_export)
SET(${project_export}_LIBRARIES ${target_name} CACHE INTERNAL "" FORCE)
SET(${project_export}_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}" CACHE INTERNAL "" FORCE)
