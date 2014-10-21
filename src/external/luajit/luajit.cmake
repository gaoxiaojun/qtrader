set(library_name luajit)

cmake_minimum_required(VERSION 2.8.9)

project(${library_name})

###############################################################################
#                 Global Sources Directories                                  #
###############################################################################
SET(LUA_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR})
###############################################################################
#                            External Include                                 #
###############################################################################
INCLUDE (CheckIncludeFiles)
INCLUDE(CheckLibraryExists)
INCLUDE(CheckFunctionExists)
INCLUDE(CheckCSourceCompiles)
INCLUDE(CheckTypeSize)
INCLUDE(CheckSymbolExists)
INCLUDE(MacroAddFileDependencies)

###############################################################################
#            Gloabl Compiler Options and Link Options                         #
###############################################################################
# for Luajit in OSX required. see lj_alloc.c for mmap
if (APPLE)
  set ( CMAKE_EXE_LINKER_FLAGS "-pagezero_size 10000 -image_base 100000000 ${CMAKE_EXE_LINKER_FLAGS}" )
  find_library(COCOA_LIBRARY Cocoa)
endif()

#if (NOT WIN32 OR NOT MINGW)
#  set (CMAKE_C_FLAGS_INIT "-Wall -Wunused -O2 -fomit-frame-pointer")
#endif()

###############################################################################
#                           Luajit                                            #
###############################################################################
enable_language(C)
enable_language(ASM)

# LuaJIT specific options
option ( LUAJIT_DISABLE_FFI "Disable FFI." OFF )
option ( LUAJIT_ENABLE_LUA52COMPAT "Enable Lua 5.2 compatibility." ON )
option ( LUAJIT_DISABLE_JIT "Disable JIT." OFF )
option ( LUAJIT_CPU_SSE2 "Use SSE2 instead of x87 instructions." ON )
option ( LUAJIT_CPU_NOCMOV "Disable NOCMOV." OFF )
option ( LUAJIT_USE_GDBJIT "USING GDBJIT." OFF)
MARK_AS_ADVANCED(LUAJIT_DISABLE_FFI LUAJIT_ENABLE_LUA52COMPAT LUAJIT_DISABLE_JIT
  LUAJIT_CPU_SSE2 LUAJIT_CPU_NOCMOV LUAJIT_RUN_DYNASM LUAJIT_USE_GDBJIT)

CHECK_TYPE_SIZE("void*" SIZEOF_VOID_P)
IF(SIZEOF_VOID_P EQUAL 8)
  ADD_DEFINITIONS(-D_FILE_OFFSET_BITS=64 -D_LARGEFILE_SOURCE)
ENDIF()

if ( WIN32 AND NOT CYGWIN )
  add_definitions ( -DLUA_BUILD_AS_DLL -DLUAJIT_OS=LUAJIT_OS_WINDOWS)
  set ( LJVM_MODE coffasm )
elseif ( APPLE )
  set ( LJVM_MODE machasm )
else ()
  set ( LJVM_MODE elfasm )
endif ()

IF(NOT WIN32)
  FIND_LIBRARY(DL_LIBRARY "dl")
  IF(DL_LIBRARY)
    SET(CMAKE_REQUIRED_LIBRARIES ${DL_LIBRARY})
    LIST(APPEND LIBS ${DL_LIBRARY})
  ENDIF(DL_LIBRARY)
  CHECK_FUNCTION_EXISTS(dlopen LUA_USE_DLOPEN)
  IF(NOT LUA_USE_DLOPEN)
    MESSAGE(FATAL_ERROR "Cannot compile a useful lua.
Function dlopen() seems not to be supported on your platform.
Apparently you are not on a Windows platform as well.
So lua has no way to deal with shared libraries!")
  ENDIF(NOT LUA_USE_DLOPEN)
ENDIF(NOT WIN32)

if (UNIX AND NOT APPLE)
  CHECK_LIBRARY_EXISTS(m sin "" LUA_USE_LIBM)
  if ( LUA_USE_LIBM )
    list ( APPEND LIBS m )
  endif ()
endif ()

## SOURCES
# Generate luaconf.h
#configure_file ( src/luaconf.h.in ${CMAKE_CURRENT_BINARY_DIR}/luaconf.h )
#INSTALL(FILES ${CMAKE_CURRENT_BINARY_DIR}/luaconf.h src/lua.h src/lauxlib.h src/lualib.h
#  DESTINATION "${LUA_INSTALL_INCLUDE_SUBDIR}")

MACRO(LJ_TEST_ARCH stuff)
  CHECK_C_SOURCE_COMPILES("
#undef ${stuff}
#include \"lj_arch.h\"
#if ${stuff}
int main() { return 0; }
#else
#error \"not defined\"
#endif
" ${stuff})
ENDMACRO()

MACRO(LJ_TEST_ARCH_VALUE stuff value)
  CHECK_C_SOURCE_COMPILES("
#undef ${stuff}
#include \"lj_arch.h\"
#if ${stuff} == ${value}
int main() { return 0; }
#else
#error \"not defined\"
#endif
" ${stuff}_${value})
ENDMACRO()

SET(CMAKE_REQUIRED_INCLUDES ${CMAKE_CURRENT_BINARY_DIR} ${LUA_ROOT_DIR}/src)

FOREACH(arch X64 X86 ARM) # PPC PPCSPE MIPS not supported
  LJ_TEST_ARCH(LJ_TARGET_${arch})
  if(LJ_TARGET_${arch})
    STRING(TOLOWER ${arch} TARGET_LJARCH)
    BREAK()
  ENDIF()
ENDFOREACH()

IF(NOT TARGET_LJARCH)
  MESSAGE(FATAL_ERROR "architecture not supported")
ENDIF()

SET(DASM_ARCH ${TARGET_LJARCH})
SET(DASM_FLAGS)
SET(TARGET_ARCH)
LIST(APPEND TARGET_ARCH "LUAJIT_TARGET=LUAJIT_ARCH_${TARGET_LJARCH}")
LJ_TEST_ARCH_VALUE(LJ_ARCH_BITS 64)
IF(LJ_ARCH_BITS_64)
  SET(DASM_FLAGS ${DASM_FLAGS} -D P64)
ENDIF()
LJ_TEST_ARCH_VALUE(LJ_HASJIT 1)
IF(LJ_HASJIT_1)
  SET(DASM_FLAGS ${DASM_FLAGS} -D JIT)
ENDIF()
LJ_TEST_ARCH_VALUE(LJ_HASFFI 1)
IF(LJ_HASFFI_1)
  SET(DASM_FLAGS ${DASM_FLAGS} -D FFI)
ENDIF()
LJ_TEST_ARCH_VALUE(LJ_DUALNUM 1)
IF(LJ_DUALNUM_1)
  SET(DASM_FLAGS ${DASM_FLAGS} -D DUALNUM)
ENDIF()
LJ_TEST_ARCH_VALUE(LJ_ARCH_HASFPU 1)
IF(LJ_ARCH_HASFPU_1)
  SET(DASM_FLAGS ${DASM_FLAGS} -D HASFPU)
  LIST(APPEND TARGET_ARCH "LJ_ARCH_HASFPU=1")
ELSE()
  LIST(APPEND TARGET_ARCH "LJ_ARCH_HASFPU=0")
ENDIF()
IF(NOT LJ_ARCH_HASFPU_1)
  LJ_TEST_ARCH_VALUE(LJ_ABI_SOFTFP 1)
  IF(NOT LJ_ABI_SOFTFP_1)
    SET(DASM_FLAGS ${DASM_FLAGS} -D HFABI)
    LIST(APPEND TARGET_ARCH "LJ_ABI_SOFTFP=0")
  ELSE()
    LIST(APPEND TARGET_ARCH "LJ_ABI_SOFTFP=1")
  ENDIF()
ENDIF()

IF(WIN32)
  SET(DASM_FLAGS ${DASM_FLAGS} -D WIN)
ENDIF()
IF(TARGET_LJARCH STREQUAL "x86")
  LJ_TEST_ARCH_VALUE(__SSE2__ 1)
  IF(__SSE2__1)
    SET(DASM_FLAGS ${DASM_FLAGS} -D SSE)
  ENDIF()
ENDIF()
IF(TARGET_LJARCH STREQUAL "x64")
  SET(DASM_ARCH "x86")
ENDIF()

# don't support ppc
#IF(TARGET_LJARCH STREQUAL "ppc")
#  LJ_TEST_ARCH_VALUE(LJ_ARCH_SQRT 1)
#  IF(NOT LJ_ARCH_SQRT_1)
#    SET(DASM_FLAGS ${DASM_FLAGS} -D SQRT)
#  ENDIF()
#  LJ_TEST_ARCH_VALUE(LJ_ARCH_PPC64 1)
#  IF(NOT LJ_ARCH_PPC64_1)
#    SET(DASM_FLAGS ${DASM_FLAGS} -D GPR64)
#  ENDIF()
#ENDIF()

add_executable(minilua ${LUA_ROOT_DIR}/src/host/minilua.c)
SET_TARGET_PROPERTIES(minilua PROPERTIES COMPILE_DEFINITIONS "${TARGET_ARCH}")
CHECK_LIBRARY_EXISTS(m sin "" MINILUA_USE_LIBM)
if(MINILUA_USE_LIBM)
  TARGET_LINK_LIBRARIES(minilua m)
endif()
MESSAGE("Configure: luajit - done.")

add_custom_command(OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/buildvm_arch.h
  COMMAND minilua ${LUA_ROOT_DIR}/dynasm/dynasm.lua ${DASM_FLAGS} -o ${CMAKE_CURRENT_BINARY_DIR}/buildvm_arch.h ${LUA_ROOT_DIR}/src/vm_${DASM_ARCH}.dasc
  DEPENDS ${LUA_ROOT_DIR}/dynasm/dynasm.lua minilua
)

SET(SRC_LJLIB ${LUA_ROOT_DIR}/src/lib_base.c ${LUA_ROOT_DIR}/src/lib_math.c ${LUA_ROOT_DIR}/src/lib_bit.c
  ${LUA_ROOT_DIR}/src/lib_string.c ${LUA_ROOT_DIR}/src/lib_table.c ${LUA_ROOT_DIR}/src/lib_io.c
  ${LUA_ROOT_DIR}/src/lib_os.c ${LUA_ROOT_DIR}/src/lib_package.c ${LUA_ROOT_DIR}/src/lib_debug.c
  ${LUA_ROOT_DIR}/src/lib_jit.c ${LUA_ROOT_DIR}/src/lib_ffi.c)

SET(SRC_LJCORE ${LUA_ROOT_DIR}/src/lj_gc.c ${LUA_ROOT_DIR}/src/lj_err.c
  ${LUA_ROOT_DIR}/src/lj_char.c ${LUA_ROOT_DIR}/src/lj_bc.c ${LUA_ROOT_DIR}/src/lj_obj.c
  ${LUA_ROOT_DIR}/src/lj_str.c ${LUA_ROOT_DIR}/src/lj_tab.c
  ${LUA_ROOT_DIR}/src/lj_func.c ${LUA_ROOT_DIR}/src/lj_udata.c ${LUA_ROOT_DIR}/src/lj_meta.c
  ${LUA_ROOT_DIR}/src/lj_debug.c ${LUA_ROOT_DIR}/src/lj_state.c ${LUA_ROOT_DIR}/src/lj_dispatch.c
  ${LUA_ROOT_DIR}/src/lj_vmevent.c ${LUA_ROOT_DIR}/src/lj_vmmath.c ${LUA_ROOT_DIR}/src/lj_strscan.c
  ${LUA_ROOT_DIR}/src/lj_api.c ${LUA_ROOT_DIR}/src/lj_lex.c ${LUA_ROOT_DIR}/src/lj_parse.c
  ${LUA_ROOT_DIR}/src/lj_bcread.c ${LUA_ROOT_DIR}/src/lj_bcwrite.c ${LUA_ROOT_DIR}/src/lj_load.c
  ${LUA_ROOT_DIR}/src/lj_ir.c ${LUA_ROOT_DIR}/src/lj_opt_mem.c ${LUA_ROOT_DIR}/src/lj_opt_fold.c
  ${LUA_ROOT_DIR}/src/lj_opt_narrow.c ${LUA_ROOT_DIR}/src/lj_opt_dce.c ${LUA_ROOT_DIR}/src/lj_opt_loop.c
  ${LUA_ROOT_DIR}/src/lj_opt_sink.c ${LUA_ROOT_DIR}/src/lj_mcode.c ${LUA_ROOT_DIR}/src/lj_snap.c
  ${LUA_ROOT_DIR}/src/lj_record.c ${LUA_ROOT_DIR}/src/lj_crecord.c ${LUA_ROOT_DIR}/src/lj_ffrecord.c
  ${LUA_ROOT_DIR}/src/lj_asm.c ${LUA_ROOT_DIR}/src/lj_trace.c
  ${LUA_ROOT_DIR}/src/lj_ctype.c ${LUA_ROOT_DIR}/src/lj_cdata.c ${LUA_ROOT_DIR}/src/lj_cconv.c
  ${LUA_ROOT_DIR}/src/lj_ccall.c ${LUA_ROOT_DIR}/src/lj_ccallback.c
  ${LUA_ROOT_DIR}/src/lj_carith.c ${LUA_ROOT_DIR}/src/lj_clib.c ${LUA_ROOT_DIR}/src/lj_cparse.c
  ${LUA_ROOT_DIR}/src/lj_lib.c ${LUA_ROOT_DIR}/src/lj_alloc.c ${LUA_ROOT_DIR}/src/lib_aux.c
  ${SRC_LJLIB} ${LUA_ROOT_DIR}/src/lib_init.c)

IF(LJ_HASJIT_1 AND ((NOT LJ_ARCH_HASFPU_1) OR ((NOT LJ_ARCH_BITS_64) AND LJ_HASFFI_1)))
  SET(SRC_LJCORE ${LUA_ROOT_DIR}/src/lj_opt_split.c ${SRC_LJCORE})
ENDIF()

IF(LUAJIT_USE_GDBJIT)
  SET(SRC_LJCORE ${LUA_ROOT_DIR}/src/lj_gdbjit.c ${SRC_LJCORE})
ENDIF()

SET(SRC_BUILDVM ${LUA_ROOT_DIR}/src/host/buildvm.c ${LUA_ROOT_DIR}/src/host/buildvm_asm.c
  ${LUA_ROOT_DIR}/src/host/buildvm_peobj.c ${LUA_ROOT_DIR}/src/host/buildvm_lib.c ${LUA_ROOT_DIR}/src/host/buildvm_fold.c
  ${CMAKE_CURRENT_BINARY_DIR}/buildvm_arch.h)

## GENERATE
ADD_EXECUTABLE(buildvm ${SRC_BUILDVM})
SET_TARGET_PROPERTIES(buildvm PROPERTIES COMPILE_DEFINITIONS "${TARGET_ARCH}")

macro(add_buildvm_target _target _mode)
  add_custom_command(OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/${_target}
    COMMAND buildvm ARGS -m ${_mode} -o ${CMAKE_CURRENT_BINARY_DIR}/${_target} ${ARGN}
    WORKING_DIRECTORY ${LUA_ROOT_DIR}
    DEPENDS buildvm ${ARGN}
  )
endmacro(add_buildvm_target)

if (MSVC)
  add_buildvm_target ( lj_vm.obj peobj )
  set (LJ_VM_SRC ${CMAKE_CURRENT_BINARY_DIR}/lj_vm.obj)
else ()
  add_buildvm_target ( lj_vm.s ${LJVM_MODE} )
  set (LJ_VM_SRC ${CMAKE_CURRENT_BINARY_DIR}/lj_vm.s)
endif ()
add_buildvm_target ( lj_ffdef.h   ffdef   ${SRC_LJLIB} )
add_buildvm_target ( lj_bcdef.h  bcdef  ${SRC_LJLIB} )
add_buildvm_target ( lj_folddef.h folddef ${LUA_ROOT_DIR}/src/lj_opt_fold.c )
add_buildvm_target ( lj_recdef.h  recdef  ${SRC_LJLIB} )
add_buildvm_target ( lj_libdef.h  libdef  ${SRC_LJLIB} )
add_buildvm_target ( vmdef.lua  vmdef  ${SRC_LJLIB} )

SET(DEPS
  ${LJ_VM_SRC}
  ${CMAKE_CURRENT_BINARY_DIR}/lj_ffdef.h
  ${CMAKE_CURRENT_BINARY_DIR}/lj_bcdef.h
  ${CMAKE_CURRENT_BINARY_DIR}/lj_libdef.h
  ${CMAKE_CURRENT_BINARY_DIR}/lj_recdef.h
  ${CMAKE_CURRENT_BINARY_DIR}/lj_folddef.h
  ${CMAKE_CURRENT_BINARY_DIR}/vmdef.lua
  )

## COMPILE
include_directories (BEFORE ${CMAKE_CURRENT_BINARY_DIR} ${LUA_ROOT_DIR}/dynasm ${LUA_ROOT_DIR}/src )

###############################################################################
#                       LIBRARY: liblua                                       #
###############################################################################
add_library (${library_name} STATIC ${SRC_LJCORE} ${DEPS} )
target_link_libraries (${library_name} ${LIBS} )

string(TOUPPER ${library_name} project_export)
SET(${project_export}_LIBRARIES ${library_name} CACHE INTERNAL ""  FORCE)
SET(${project_export}_INCLUDE_DIR ${LUA_ROOT_DIR}/src CACHE INTERNAL "" FORCE)

###############################################################################
#                       TARGET: luajit                                        #
###############################################################################
add_executable (${library_name}_bin ${LUA_ROOT_DIR}/src/luajit.c)
target_link_libraries (${library_name}_bin ${library_name} )
SET_TARGET_PROPERTIES(${library_name}_bin PROPERTIES OUTPUT_NAME "luajit")

SET(${project_export}_BINARY ${library_name}_bin CACHE INTERNAL "" FORCE)
