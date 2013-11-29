set(library_name breakpad)

cmake_minimum_required(VERSION 2.8.9)

include(ExternalProject)

project(${library_name})

# Set default ExternalProject root directory

set_directory_properties(PROPERTIES EP_BASE ${CMAKE_BINARY_DIR}/third_party)

ExternalProject_Add(external_${library_name}
      SVN_REPOSITORY       http://google-breakpad.googlecode.com/svn/trunk/
      UPDATE_COMMAND ${CMAKE_COMMAND} -E copy
        "${CMAKE_CURRENT_SOURCE_DIR}/${library_name}.cmake" ${CMAKE_BINARY_DIR}/third_party/Source/external_${library_name}/CMakeLists.txt
      INSTALL_COMMAND ""
)

#GCC_VERSION=com.apple.compilers.llvm.clang.1_0  -sdk macosx10.8 -arch x86_64 -project ${CMAKE_CURRENT_BINARY_DIR}/src/client/mac/Breakpad.xcodeproj -target Breakpad

string(TOUPPER ${library_name} project_export)
set(${project_export}_LIBRARIES ${CMAKE_BINARY_DIR}/third_party/Build/external_${library_name}/libbreakpad.a CACHE INTERNAL "" FORCE)
set(${project_export}_INCLUDE_DIR "${CMAKE_BINARY_DIR}/third_party/Source/external_${library_name}/src" CACHE INTERNAL "" FORCE)

