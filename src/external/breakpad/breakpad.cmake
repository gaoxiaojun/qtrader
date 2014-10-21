set(library_name breakpad)

cmake_minimum_required(VERSION 2.8.9)

include_directories (${CMAKE_CURRENT_SOURCE_DIR}/src)

if(APPLE)
    set (BREAKPAD_SOURCE_FILES
        src/client/mac/handler/exception_handler.cc
        src/client/mac/crash_generation/crash_generation_client.cc
#        src/client/mac/crash_generation/crash_generation_server.cc
        src/client/mac/handler/minidump_generator.cc
        src/client/mac/handler/dynamic_images.cc
        src/client/mac/handler/breakpad_nlist_64.cc
        src/client/minidump_file_writer.cc
        src/common/mac/macho_id.cc
        src/common/mac/macho_walker.cc
        src/common/mac/macho_utilities.cc
        src/common/mac/string_utilities.cc
        src/common/mac/file_id.cc
        src/common/mac/MachIPC.mm
        src/common/mac/bootstrap_compat.cc
        src/common/md5.cc
        src/common/string_conversion.cc
        src/common/linux/linux_libc_support.cc
        src/common/convert_UTF.c
    )
elseif(WIN32)
    set(BREAKPAD_SOURCE_FILES
        src/client/windows/handler/exception_handler.cc
        src/common/windows/string_utils.cc
        src/common/windows/guid_string.cc
        src/client/windows/crash_generation/crash_generation_client.cc
    )
else()
    set(BREAKPAD_SOURCE_FILES
        src/client/linux/crash_generation/crash_generation_client.cc
        src/client/linux/handler/exception_handler.cc
        src/client/linux/handler/minidump_descriptor.cc
        src/client/linux/minidump_writer/minidump_writer.cc
        src/client/linux/minidump_writer/linux_dumper.cc
        src/client/linux/minidump_writer/linux_ptrace_dumper.cc
        src/client/linux/log/log.cc
        src/client/minidump_file_writer.cc
        src/common/linux/linux_libc_support.cc
        src/common/linux/file_id.cc
        src/common/linux/memory_mapped_file.cc
        src/common/linux/safe_readlink.cc
        src/common/linux/guid_creator.cc
        src/common/linux/elfutils.cc
        src/common/string_conversion.cc
        src/common/convert_UTF.c
    )
endif()

add_library(${library_name} STATIC ${BREAKPAD_SOURCE_FILES})

string(TOUPPER ${library_name} project_export)
set(${project_export}_LIBRARIES ${library_name} CACHE INTERNAL "" FORCE)
set(${project_export}_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src" CACHE INTERNAL "" FORCE)
