###############################################################################
# Open Trading Platform
###############################################################################
set(PROJECT_NAME OpenTrade)

###############################################################################
# project policies
###############################################################################
cmake_minimum_required(VERSION 2.8.9)
set(project_policies
  CMP0001 # NEW: CMAKE_BACKWARDS_COMPATIBILITY should no longer be used.
  CMP0002 # NEW: Logical target names must be globally unique.
  CMP0003 # NEW: Libraries linked via full path no longer produce linker search paths.
  CMP0004 # NEW: Libraries linked may NOT have leading or trailing whitespace.
  CMP0005 # NEW: Preprocessor definition values are now escaped automatically.
  CMP0006 # NEW: Installing MACOSX_BUNDLE targets requires a BUNDLE DESTINATION.
  CMP0007 # NEW: List command no longer ignores empty elements.
  CMP0008 # NEW: Libraries linked by full-path must have a valid library file name.
  CMP0009 # NEW: FILE GLOB_RECURSE calls should not follow symlinks by default.
  CMP0010 # NEW: Bad variable reference syntax is an error.
  CMP0011 # NEW: Included scripts do automatic cmake_policy PUSH and POP.
  CMP0012 # NEW: if() recognizes numbers and boolean constants.
  CMP0013 # NEW: Duplicate binary directories are not allowed.
  CMP0014 # NEW: Input directories must have CMakeLists.txt
  )
foreach(policy ${project_policies})
  if(POLICY ${policy})
    cmake_policy(SET ${policy} NEW)
  endif()
endforeach()

if("${CMAKE_VERSION}" VERSION_GREATER 2.8.11.1)
    cmake_policy(SET CMP0020 NEW)
endif("${CMAKE_VERSION}" VERSION_GREATER 2.8.11.1)

###############################################################################
# project includes
###############################################################################
set(CMAKE_MODULE_PATH
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake"
    ${CMAKE_MODULE_PATH}
)
include(cmake/macroQtCommand.cmake)
include(cmake/macroParseArguments.cmake)
include(cmake/macroBuildLib.cmake)
include(cmake/macroBuildPlugin.cmake)
include(cmake/macroBuildApp.cmake)
include(cmake/macroSetupQt.cmake)
include(cmake/macroGeneratePluginResourcefile.cmake)
###############################################################################
# Project Info
###############################################################################
set(APPLICATION_NAME ${PROJECT_NAME})
string(TOLOWER ${APPLICATION_NAME} APPLICATION_NAME_LOWER)
set(APPLICATION_ORGANIZATION_NAME "dailypips")
set(APPLICATION_COPYRIGHT "2013 Xiaojun Gao <br/>http://www.dailypips.org")
set(APPLICATION_CRASHREPORT_URL "http://www.dailypips.org/${APPLICATION_NAME_LOWER}/crashreport")
set(APPLICATION_UPDATE_CHECK_URL "http://www.dailypips.org/${APPLICATION_NAME_LOWER}/v=")
set(APPLICATION_CORE_PLUGIN_NAME "Core")
# set the OS X Bundle specific CMake variables which will be used to populate the plist for
# the application bundle
set(APPLICATION_BUNDLE_COPYRIGHT "2013 Xiaojun Gao")
set(APPLICATION_BUNDLE_IDENTIFIER "org.dailypips.${APPLICATION_NAME_LOWER}")
file(READ ${CMAKE_SOURCE_DIR}/LICENSE APPLICATION_LICENSE)
set(APPLICATION_LANGUAGES "zh_CN")
set(APPLICATION_LANGUAGES_PACKAGE_IN_BINARY "zh_CN")
###############################################################################
# Version
###############################################################################
if(EXISTS ${CMAKE_SOURCE_DIR}/VERSION)
  file(READ ${CMAKE_SOURCE_DIR}/VERSION APPLICATION_VERSION)
endif()

if(NOT APPLICATION_VERSION)
  set(APPLICATION_VERSION "0.0.1")
  message(STATUS "Warning: Assume version is ${APPLICATION_VERSION}")
endif()

string(REGEX REPLACE "\n" "" APPLICATION_VERSION "${APPLICATION_VERSION}") # get rid of the newline at the end
string(REPLACE "." ";" APPLICATION_VERSION_LIST ${APPLICATION_VERSION})
list(LENGTH APPLICATION_VERSION_LIST APPLICATION_VERSION_SIZE)
list(GET APPLICATION_VERSION_LIST 0 APPLICATION_VERSION_MAJOR)
list(GET APPLICATION_VERSION_LIST 1 APPLICATION_VERSION_MINOR)
if(APPLICATION_VERSION_SIZE EQUAL 3)
    list(GET APPLICATION_VERSION_LIST 2 APPLICATION_VERSION_PATCH)
else(APPLICATION_VERSION_SIZE EQUAL 3)
    set(APPLICATION_VERSION_PATCH 0)
endif(APPLICATION_VERSION_SIZE EQUAL 3)
# Find Git Version Patch
find_program(GIT git)
if(GIT)
  execute_process(
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        COMMAND ${GIT} rev-parse --short HEAD
        OUTPUT_VARIABLE GIT_OUT OUTPUT_STRIP_TRAILING_WHITESPACE
        ERROR_QUIET
  )
  set(APPLICATION_VERSION_REVISOR "${GIT_OUT}")
else(GIT)
    if(GITBUILD)
        set(APPLICATION_VERSION_REVISOR "${GITBUILD}")
   endif()
endif()
if(NOT APPLICATION_VERSION_REVISOR)
  message(STATUS "Warning: Assume revisor is 0123456")
  set(APPLICATION_VERSION_REVISOR 0)
endif()
set(APPLICATION_VERSION "${APPLICATION_VERSION_MAJOR}.${APPLICATION_VERSION_MINOR}.${APPLICATION_VERSION_PATCH}")
###############################################################################
#            Gloabl Compiler Options and Link Options                         #
###############################################################################
# Verbose makefile
set(CMAKE_VERBOSE_MAKEFILE ON)
# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Show all warnings
if(NOT MSVC)
    set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -Wall -Wextra")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -Wextra")
endif(NOT MSVC)

if(MINGW)
# Windows compatibility
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-subsystem,windows")
elseif(MSVC)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -nologo -Zc:wchar_t")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -nologo -Zc:wchar_t -w34100 -w34189")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /NOLOGO /DYNAMICBASE /NXCOMPAT /SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")
endif(MINGW)

# Support 64-bit OS X only
if(APPLE)
    set(CMAKE_OSX_ARCHITECTURES x86_64)
endif()

# Set MingW bin dir, if MingW present
if(MINGW)
    string(REGEX REPLACE "([^ ]+)[/\\].*" "\\1" MINGW_BIN_DIR_TMP "${CMAKE_CXX_COMPILER}")
    string(REGEX REPLACE "\\\\" "/" MINGW_BIN_DIR "${MINGW_BIN_DIR_TMP}") # Replace back slashes to slashes
endif(MINGW)

# -fPIE
if (Qt5_POSITION_INDEPENDENT_CODE)
  set(CMAKE_POSITION_INDEPENDENT_CODE ON)
endif()
###############################################################################
#            Project Compiler Options and Link Options                        #
###############################################################################
# for Luajit in OSX required. see lj_alloc.c for mmap
#if (APPLE)
#  set ( CMAKE_EXE_LINKER_FLAGS "-pagezero_size 10000 -image_base 100000000 ${CMAKE_EXE_LINKER_FLAGS}" )
#  find_library(COCOA_LIBRARY Cocoa)
#endif()

# Assume release build by default
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "RelWithDebInfo" CACHE STRING "" FORCE)
endif()

# Disable debug output for release builds
if(CMAKE_BUILD_TYPE MATCHES "^[Rr]elease$")
    add_definitions(-DQT_NO_DEBUG_OUTPUT)
endif()

###############################################################################
# Find & Setup depended library
###############################################################################

# Find Qt4 or Qt5
MacroSetupQt()

###############################################################################
#           Global Default Install Paths                                      #
###############################################################################
if(APPLE)
   set(APPLICATION_DATA_PATH "Resources")
   set(APPLICATION_DOC_PATH  "Resources/doc")
   set(APPLICATION_LIBS_PATH "lib")
   set(APPLICATION_PLUGINS_PATH "PlugIns/${APPLICATION_NAME}")
elseif(WIN32)
    set(APPLICATION_DATA_PATH "resources")
    set(APPLICATION_DOC_PATH  "resources/doc")
    set(APPLICATION_LIBS_PATH "lib")
    set(APPLICATION_PLUGINS_PATH "../plugins/${APPLICATION_NAME_LOWER}")
else() # unix
    set(APPLICATION_DATA_PATH "share/${APPLICATION_NAME_LOWER}")
    set(APPLICATION_DOC_PATH  "share/doc/${APPLICATION_NAME_LOWER}")
    set(APPLICATION_LIBS_PATH "lib")
    set(APPLICATION_PLUGINS_PATH "../plugins/${APPLICATION_NAME_LOWER}")
endif()
set(APPLICATION_TRANSLATIONS_PATH "${APPLICATION_DATA_PATH}/translations")

# Set default install path:
# In *nix environments this is /usr/local
# Under M$ Windows this is C:\Program files\
# Under OSX this is /Application
# WARNING: Leading slash should be added
if(WIN32)
    if(NOT CMAKE_INSTALL_PREFIX)
        set(CMAKE_INSTALL_PREFIX "C:/Program files/${APPLICATION_NAME}")
    endif(NOT CMAKE_INSTALL_PREFIX)
    set(PROJECT_INSTALL_DATA_DIR ${APPLICATION_DATA_PATH})
    set(PROJECT_INSTALL_BIN_DIR "")
    set(PROJECT_INSTALL_LIB_DIR ${APPLICATION_LIBS_PATH})
elseif(APPLE)
    if(NOT CMAKE_INSTALL_PREFIX)
        set(CMAKE_INSTALL_PREFIX "/Applications")
    endif(NOT CMAKE_INSTALL_PREFIX)
    set(PROJECT_INSTALL_DATA_DIR "${APPLICATION_NAME}.app/Contents/${APPLICATION_DATA_PATH}")
    set(PROJECT_INSTALL_BIN_DIR "${APPLICATION_NAME}.app/Contents/MacOS")
    set(PROJECT_INSTALL_LIB_DIR "${APPLICATION_NAME}.app/Contents/${APPLICATION_LIBS_PATH}")

    SET(APPLICATION_DATA_DIR "${CMAKE_INSTALL_PREFIX}/${PROJECT_INSTALL_DATA_DIR}")
else()
    if(NOT CMAKE_INSTALL_PREFIX)
        set(CMAKE_INSTALL_PREFIX "/usr/local")
    endif(NOT CMAKE_INSTALL_PREFIX)
    set(PROJECT_INSTALL_DATA_DIR ${APPLICATION_DATA_PATH})
    set(PROJECT_INSTALL_BIN_DIR "bin")
    set(PROJECT_INSTALL_LIB_DIR ${APPLICATION_LIBS_PATH})

    set(APPLICATION_DATA_DIR "${CMAKE_INSTALL_PREFIX}/${PROJECT_INSTALL_DATA_DIR}")
endif()

# default execution & lib & plugins path
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/dist)

###############################################################################
# Installation                                                                #
###############################################################################
# Install data
# INSTALL(DIRECTORY ${APPLICATION_ICONS} DESTINATION "${CMAKE_INSTALL_PREFIX}/${APPLICATION_INSTALL_DATA_DIR}/icons")

###############################################################################
# Uninstall
###############################################################################
configure_file(
    "${CMAKE_SOURCE_DIR}/cmake/cmake_uninstall.cmake.in"
    "${CMAKE_BINARY_DIR}/cmake_uninstall.cmake"
    IMMEDIATE @ONLY)

add_custom_target(uninstall
    "${CMAKE_COMMAND}" -P "${CMAKE_BINARY_DIR}/cmake_uninstall.cmake")

###############################################################################
# Source Code
###############################################################################
add_subdirectory(src)
