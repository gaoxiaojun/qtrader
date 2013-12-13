cmake_minimum_required(VERSION 2.8.9)

if(APPLE)
    SET(LIBRARY_OUTPUT_PATH ${EXECUTABLE_OUTPUT_PATH}/${APPLICATION_NAME}.app/Contents/${APPLICATION_LIBS_PATH})
else()
    SET(LIBRARY_OUTPUT_PATH ${EXECUTABLE_OUTPUT_PATH}/${APPLICATION_LIBS_PATH})
endif()

SET(PROJECT_LIBS_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}" "${CMAKE_CURRENT_BINARY_DIR}"  CACHE INTERNAL "" FORCE)

add_subdirectory(extensionsystem)
add_subdirectory(opentrade)
#add_subdirectory(utils)
#add_subdirectory(luajit)
