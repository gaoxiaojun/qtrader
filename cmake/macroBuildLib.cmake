#
# Depends on:
#  macroParseArguments.cmake
#
#! \brief Build a Library.
#!
#! This macro takes the usual arguments for building
#! a shared library using Qt.
#
#! \ingroup CMakeAPI

macro(MacroBuildLib)
  MacroParseArguments(MY
    "NAME;SRC_FILES;UI_FILES;QRC_FILES;DEPEND_LIBS;INCLUDE_DIRECTORIES;TARGET_LIBRARIES;CACHED_RESOURCEFILES;LIBRARY_TYPE;MOC_OPTIONS"
    ""
    ${ARGN}
    )

  # Sanity checks
  if(NOT DEFINED MY_NAME)
    message(FATAL_ERROR "NAME is mandatory")
  endif()

  if(NOT DEFINED MY_LIBRARY_TYPE)
    set(MY_LIBRARY_TYPE "SHARED")
  endif()

  # Define library name
  set(lib_name ${MY_NAME})
  
  # --------------------------------------------------------------------------
  # Depends library
  set(MY_QT_MODULES )
  set(MY_LIB_MODULES )
  foreach(_name ${MY_DEPEND_LIBS})
    if(${_name} MATCHES "Qt.*")
      string(REPLACE "Qt" "" q_name ${_name})
      list(APPEND MY_QT_MODULES ${q_name})
    else()
      string(TOUPPER ${_name} upper_name)
      list(APPEND MY_LIB_MODULES ${upper_name})
    endif()
  endforeach()
  if(MY_LIB_MODULES)
     list(REMOVE_DUPLICATES MY_LIB_MODULES)
  endif()
  if(MY_QT_MODULES)
    set(CMAKE_AUTOMOC ON)
  endif()
  # --------------------------------------------------------------------------
  # Include dirs
  set(my_includes
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}
    ${MY_INCLUDE_DIRECTORIES}
    )
  foreach(_lib_name ${MY_LIB_MODULES})
    list(APPEND my_includes  ${${_lib_name}_INCLUDE_DIR})
  endforeach()

  include_directories(
    ${my_includes}
    )
  # --------------------------------------------------------------------------
  # Library definition
  string(TOUPPER ${MY_NAME} MY_EXPORT_LIBNAME) 
  set(MY_LIBRARY_EXPORT_DIRECTIVE ${MY_EXPORT_DIRECTIVE})
  add_definitions(-D${MY_EXPORT_LIBNAME}_LIBRARY)

  # --------------------------------------------------------------------------
  # UI and Resource
  # Make sure variable are cleared
  set(MY_UI_CPP)
  set(MY_QRC_SRCS)

  if(DEFINED MY_UI_FILES)
    QT_WRAP_UI(MY_UI_CPP ${MY_UI_FILES})
  endif()

  if(DEFINED MY_QRC_FILES)
      QT_ADD_RESOURCES(MY_QRC_SRCS ${MY_QRC_FILES})
  endif()

  # --------------------------------------------------------------------------
  # Translation
  # Create translation files (.ts and .qm)
  set(_plugin_qm_files )
  set(_plugin_cached_resources_in_binary_tree )
  set(_translations_dir "${CMAKE_CURRENT_BINARY_DIR}/translations")
  # Create translation files if not exist
  foreach(_language ${APPLICATION_LANGUAGES})
    set(_ts_file "${CMAKE_CURRENT_SOURCE_DIR}/translations/${_language}.ts")
    QT_CREATE_OR_UPDATE_TRANSLATION(${_ts_file} ${MY_SRC_FILES} ${MY_UI_FILES})
  endforeach()

  set(MY_TS_FILES)
  foreach(_language ${APPLICATION_LANGUAGES})
    list(APPEND MY_TS_FILES "${CMAKE_CURRENT_BINARY_DIR}/translations/${_language}.ts")
  endforeach()

  set_source_files_properties(${MY_TS_FILES} PROPERTIES OUTPUT_LOCATION ${_translations_dir})
  QT_ADD_TRANSLATION(_plugin_qm_files ${MY_TS_FILES})

  # --------------------------------------------------------------------------
  # Resource add
  set(_plugin_cached_resources_in_source_tree )
  if(MY_CACHED_RESOURCEFILES)
    foreach(_cached_resource ${MY_CACHED_RESOURCEFILES})
      if(IS_ABSOLUTE "${_cached_resource}")
        # create a path relative to the current binary dir
        file(RELATIVE_PATH _relative_cached_resource ${CMAKE_CURRENT_BINARY_DIR} ${_cached_resource})
        list(APPEND _plugin_cached_resources_in_binary_tree ${_relative_cached_resource})
      else()
        list(APPEND _plugin_cached_resources_in_source_tree ${_cached_resource})
      endif()
    endforeach()
  endif()

  # Add any other additional resource files
  if(_plugin_cached_resources_in_source_tree OR _plugin_cached_resources_in_binary_tree)
    MacroGenerateResourceFile(MY_QRC_SRCS
      NAME ${lib_name}_cached.qrc
      PREFIX ${lib_name}
      RESOURCES ${_plugin_cached_resources_in_source_tree}
      BINARY_RESOURCES ${_plugin_cached_resources_in_binary_tree})
  endif()

  # --------------------------------------------------------------------------
  # Build library
  add_library(Lib_${lib_name} ${MY_LIBRARY_TYPE}
    ${MY_SRC_FILES}
    ${MY_UI_CPP}
    ${MY_QRC_SRCS}
    ${MY_QM_SRCS}
    )
  set_target_properties(Lib_${lib_name} PROPERTIES OUTPUT_NAME ${lib_name})

  # Library properties specific to STATIC build
  if(MY_LIBRARY_TYPE STREQUAL "STATIC")
    if(CMAKE_SYSTEM_PROCESSOR STREQUAL "x86_64")
      set_target_properties(${lib_name} PROPERTIES COMPILE_FLAGS "-fPIC")
    endif()
  endif()

  set(my_libs
    ${MY_TARGET_LIBRARIES}
    )

  foreach(_lib_name ${MY_LIB_MODULES})
    list(APPEND my_libs ${${_lib_name}_LIBRARIES})
  endforeach()

  if(MINGW)
    list(APPEND my_libs ssp) # add stack smash protection lib
  endif()
  target_link_libraries(Lib_${lib_name} ${my_libs})

  if(MY_QT_MODULES)
      qt_use_modules(Lib_${lib_name} ${MY_QT_MODULES})
  endif()

  # --------------------------------------------------------------------------
  # Export
  string(TOUPPER ${lib_name} project_export)
  set(${project_export}_LIBRARIES Lib_${lib_name} CACHE INTERNAL "" FORCE)
  set(${project_export}_INCLUDE_DIR ${my_includes} CACHE INTERNAL "" FORCE)
  set(${project_export}_TRANSLATION_DIR "${CMAKE_CURRENT_SOURCE_DIR}/translations" CACHE INTERNAL "" FORCE)
endmacro()


