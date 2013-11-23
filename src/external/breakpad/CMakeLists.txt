set(library_name breakpad)

cmake_minimum_required(VERSION 2.8.9)

include(ExternalProject)

project(${library_name})

set(_prefix ${CMAKE_CURRENT_BINARY_DIR}/${library_name}-bin)

ExternalProject_Add(external_${library_name}
      SVN_REPOSITORY http://google-breakpad.googlecode.com/svn/trunk/
      UPDATE_COMMAND ""
      PREFIX ${_prefix}
      CONFIGURE_COMMAND ./configure
		 --prefix=${_prefix}
      BUILD_COMMAND make
      INSTALL_COMMAND make install
      BUILD_IN_SOURCE 1
)

ExternalProject_Get_Property(external_${library_name} install_dir)
message("YYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYinstall dir: ${install_dir}")
install(DIRECTORY ${install_dir}/bin/ DESTINATION bin)
install(DIRECTORY ${install_dir}/lib/ DESTINATION lib)
install(DIRECTORY ${install_dir}/include/ DESTINATION include)


string(TOUPPER ${library_name} project_export)
set(${project_export}_LIBRARIES ${install_dir}/lib/libbreakpad.a CACHE INTERNAL "" FORCE)
set(${project_export}_INCLUDE_DIR "${_prefix}/src/external_breakpad/src" CACHE INTERNAL "" FORCE)

set(BREAKPAD_PATH ${_prefix}/src/external_breakpad)

set (OSMAC_HEADRE_FILES
         ${BREAKPAD_PATH}/src/client/mac/handler/exception_handler.h
         ${BREAKPAD_PATH}/src/client/mac/crash_generation/crash_generation_client.h
#         ${BREAKPAD_PATH}/src/client/mac/crash_generation/crash_generation_server.h
         ${BREAKPAD_PATH}/src/client/mac/crash_generation/client_info.h
         ${BREAKPAD_PATH}/src/client/mac/handler/minidump_generator.h
         ${BREAKPAD_PATH}/src/client/mac/handler/dynamic_images.h
         ${BREAKPAD_PATH}/src/client/mac/handler/breakpad_nlist_64.h
         ${BREAKPAD_PATH}/src/client/mac/handler/mach_vm_compat.h
         ${BREAKPAD_PATH}/src/client/minidump_file_writer.h
         ${BREAKPAD_PATH}/src/client/minidump_file_writer-inl.h
         ${BREAKPAD_PATH}/src/common/mac/macho_utilities.h
         ${BREAKPAD_PATH}/src/common/mac/byteswap.h
         ${BREAKPAD_PATH}/src/common/mac/MachIPC.h
         ${BREAKPAD_PATH}/src/common/mac/scoped_task_suspend-inl.h
         ${BREAKPAD_PATH}/src/common/mac/file_id.h
         ${BREAKPAD_PATH}/src/common/mac/macho_id.h
         ${BREAKPAD_PATH}/src/common/mac/macho_walker.h
         ${BREAKPAD_PATH}/src/common/mac/macho_utilities.h
         ${BREAKPAD_PATH}/src/common/mac/bootstrap_compat.h
         ${BREAKPAD_PATH}/src/common/mac/string_utilities.h
         ${BREAKPAD_PATH}/src/common/linux/linux_libc_support.h
         ${BREAKPAD_PATH}/src/common/string_conversion.h
         ${BREAKPAD_PATH}/src/common/md5.h
         ${BREAKPAD_PATH}/src/common/memory.h
         ${BREAKPAD_PATH}/src/common/using_std_string.h
         ${BREAKPAD_PATH}/src/common/convert_UTF.h
         ${BREAKPAD_PATH}/src/processor/scoped_ptr.h
         ${BREAKPAD_PATH}/src/google_breakpad/common/minidump_exception_mac.h
         ${BREAKPAD_PATH}/src/google_breakpad/common/breakpad_types.h
         ${BREAKPAD_PATH}/src/google_breakpad/common/minidump_format.h
         ${BREAKPAD_PATH}/src/google_breakpad/common/minidump_size.h
         ${BREAKPAD_PATH}/src/third_party/lss/linux_syscall_support.h
)

set (OSMAC_SOURCE_FILES 
        ${BREAKPAD_PATH}/src/client/mac/handler/exception_handler.cc
        ${BREAKPAD_PATH}/src/client/mac/crash_generation/crash_generation_client.cc
#        ${BREAKPAD_PATH}/src/client/mac/crash_generation/crash_generation_server.cc
        ${BREAKPAD_PATH}/src/client/mac/handler/minidump_generator.cc
        ${BREAKPAD_PATH}/src/client/mac/handler/dynamic_images.cc
        ${BREAKPAD_PATH}/src/client/mac/handler/breakpad_nlist_64.cc
        ${BREAKPAD_PATH}/src/client/minidump_file_writer.cc
        ${BREAKPAD_PATH}/src/common/mac/macho_id.cc
        ${BREAKPAD_PATH}/src/common/mac/macho_walker.cc
        ${BREAKPAD_PATH}/src/common/mac/macho_utilities.cc
        ${BREAKPAD_PATH}/src/common/mac/string_utilities.cc
        ${BREAKPAD_PATH}/src/common/mac/file_id.cc
        ${BREAKPAD_PATH}/src/common/mac/MachIPC.mm
        ${BREAKPAD_PATH}/src/common/mac/bootstrap_compat.cc
        ${BREAKPAD_PATH}/src/common/md5.cc
        ${BREAKPAD_PATH}/src/common/string_conversion.cc
        ${BREAKPAD_PATH}/src/common/linux/linux_libc_support.cc
        ${BREAKPAD_PATH}/src/common/convert_UTF.c
)
 
set(OSLIN_HEADER_FILES
         ${BREAKPAD_PATH}/src/client/linux/handler/exception_handler.h
         ${BREAKPAD_PATH}/src/client/linux/crash_generation/crash_generation_client.h
         ${BREAKPAD_PATH}/src/client/linux/handler/minidump_descriptor.h
         ${BREAKPAD_PATH}/src/client/linux/minidump_writer/minidump_writer.h
         ${BREAKPAD_PATH}/src/client/linux/minidump_writer/line_reader.h
         ${BREAKPAD_PATH}/src/client/linux/minidump_writer/linux_dumper.h
         ${BREAKPAD_PATH}/src/client/linux/minidump_writer/linux_ptrace_dumper.h
         ${BREAKPAD_PATH}/src/client/linux/minidump_writer/directory_reader.h
         ${BREAKPAD_PATH}/src/client/linux/log/log.h
         ${BREAKPAD_PATH}/src/client/minidump_file_writer-inl.h
         ${BREAKPAD_PATH}/src/client/minidump_file_writer.h
         ${BREAKPAD_PATH}/src/common/linux/linux_libc_support.h
         ${BREAKPAD_PATH}/src/common/linux/eintr_wrapper.h
         ${BREAKPAD_PATH}/src/common/linux/ignore_ret.h
         ${BREAKPAD_PATH}/src/common/linux/file_id.h
         ${BREAKPAD_PATH}/src/common/linux/memory_mapped_file.h
         ${BREAKPAD_PATH}/src/common/linux/safe_readlink.h
         ${BREAKPAD_PATH}/src/common/linux/guid_creator.h
         ${BREAKPAD_PATH}/src/common/linux/elfutils.h
         ${BREAKPAD_PATH}/src/common/linux/elfutils-inl.h
         ${BREAKPAD_PATH}/src/common/using_std_string.h
         ${BREAKPAD_PATH}/src/common/memory.h
         ${BREAKPAD_PATH}/src/common/basictypes.h
         ${BREAKPAD_PATH}/src/common/memory_range.h
         ${BREAKPAD_PATH}/src/common/string_conversion.h
         ${BREAKPAD_PATH}/src/common/convert_UTF.h
         ${BREAKPAD_PATH}/src/google_breakpad/common/minidump_format.h
         ${BREAKPAD_PATH}/src/google_breakpad/common/minidump_size.h
         ${BREAKPAD_PATH}/src/google_breakpad/common/breakpad_types.h
         ${BREAKPAD_PATH}/src/processor/scoped_ptr.h
         ${BREAKPAD_PATH}/src/third_party/lss/linux_syscall_support.h
)
set(OSLIN_SOURCE_FILES
        ${BREAKPAD_PATH}/src/client/linux/crash_generation/crash_generation_client.cc
        ${BREAKPAD_PATH}/src/client/linux/handler/exception_handler.cc
        ${BREAKPAD_PATH}/src/client/linux/handler/minidump_descriptor.cc
        ${BREAKPAD_PATH}/src/client/linux/minidump_writer/minidump_writer.cc
        ${BREAKPAD_PATH}/src/client/linux/minidump_writer/linux_dumper.cc
        ${BREAKPAD_PATH}/src/client/linux/minidump_writer/linux_ptrace_dumper.cc
        ${BREAKPAD_PATH}/src/client/linux/log/log.cc
        ${BREAKPAD_PATH}/src/client/minidump_file_writer.cc
        ${BREAKPAD_PATH}/src/common/linux/linux_libc_support.cc
        ${BREAKPAD_PATH}/src/common/linux/file_id.cc
        ${BREAKPAD_PATH}/src/common/linux/memory_mapped_file.cc
        ${BREAKPAD_PATH}/src/common/linux/safe_readlink.cc
        ${BREAKPAD_PATH}/src/common/linux/guid_creator.cc
        ${BREAKPAD_PATH}/src/common/linux/elfutils.cc
        ${BREAKPAD_PATH}/src/common/string_conversion.cc
        ${BREAKPAD_PATH}/src/common/convert_UTF.c
)
 
set(OSWIN_HEADER_FILES
         ${BREAKPAD_PATH}/src/common/windows/string_utils-inl.h
         ${BREAKPAD_PATH}/src/common/windows/guid_string.h
         ${BREAKPAD_PATH}/src/client/windows/handler/exception_handler.h
         ${BREAKPAD_PATH}/src/client/windows/common/ipc_protocol.h
         ${BREAKPAD_PATH}/src/google_breakpad/common/minidump_format.h 
         ${BREAKPAD_PATH}/src/google_breakpad/common/breakpad_types.h 
         ${BREAKPAD_PATH}/src/client/windows/crash_generation/crash_generation_client.h 
         ${BREAKPAD_PATH}/src/processor/scoped_ptr.h 
)

set(OSWIN_SOURCE_FILES 
        ${BREAKPAD_PATH}/src/client/windows/handler/exception_handler.cc
        ${BREAKPAD_PATH}/src/common/windows/string_utils.cc
        ${BREAKPAD_PATH}/src/common/windows/guid_string.cc
        ${BREAKPAD_PATH}/src/client/windows/crash_generation/crash_generation_client.cc 
)


if(WIN32)
  set(BREAKPAD_SOURCE_FILES ${OSWIN_SOURCE_FILES} CACHE INTERNAL "" FORCE)
elseif(APPLE)
  set(BREAKPAD_SOURCE_FILES ${OSMAC_SOURCE_FILES} CACHE INTERNAL "" FORCE)
else()
  set(BREAKPAD_SOURCE_FILES ${OSLIN_SOURCE_FILES} CACHE INTERNAL "" FORCE)
endif()
