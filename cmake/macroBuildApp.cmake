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

macro(MacroBuildApp)
  MacroParseArguments(MY
    "NAME;SRC_FILES;MOC_FILES;UI_FILES;QRC_FILES;DEPEND_LIBS;INCLUDE_DIRECTORIES;TARGET_LIBRARIES;CACHED_RESOURCEFILES;MOC_OPTIONS"
    ""
    ${ARGN}
    )

  # Sanity checks
  if(NOT DEFINED MY_NAME)
    message(FATAL_ERROR "NAME is mandatory")
  endif()

  # Define library name
  set(app_name ${MY_NAME})

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

  # Make sure variable are cleared
  set(MY_MOC_CPP)
  set(MY_UI_CPP)
  set(MY_QRC_SRCS)

  # Wrap
  if(MY_MOC_FILES)
    # this is a workaround for Visual Studio. The relative include paths in the generated
    # moc files can get very long and can't be resolved by the MSVC compiler.
    foreach(moc_src ${MY_MOC_FILES})
      QT_WRAP_CPP(MY_MOC_CPP ${moc_src} OPTIONS -f${moc_src} ${MY_MOC_OPTIONS})
    endforeach()
  endif()
  QT_WRAP_UI(MY_UI_CPP ${MY_UI_FILES})
  if(DEFINED MY_QRC_FILES)
      QT_ADD_RESOURCES(MY_QRC_SRCS ${MY_QRC_FILES})
  endif()

  # Create translation files (.ts and .qm)
  set(_plugin_qm_files )
  set(_plugin_cached_resources_in_binary_tree )
  set(_translations_dir "${CMAKE_CURRENT_BINARY_DIR}/translations")
  # Create translation files if not exist
  foreach(_language ${APPLICATION_LANGUAGES})
    set(_ts_file "${CMAKE_CURRENT_SOURCE_DIR}/translations/${_language}.ts")
    QT_CREATE_OR_UPDATE_TRANSLATION(${_ts_file} ${MY_SRC_FILES} ${MY_UI_FILES})
  endforeach()
  # Merge plugin ts file with depend librarys ts file
  foreach(_language ${APPLICATION_LANGUAGES})
    set(_plugin_dep_ts_files)
    foreach(_dep_libname ${MY_LIB_MODULES})
      string(TOUPPER ${_dep_libname} _dep_libname)
      set(_dep_ts_file "${${_dep_libname}_TRANSLATION_DIR}/${_language}.ts")
      #message("lib:${_dep_libname} ts:${_dep_ts_file}")
      if(EXISTS ${_dep_ts_file})
        list(APPEND _plugin_dep_ts_files ${_dep_ts_file})
      endif()
    endforeach()
    list(APPEND _plugin_dep_ts_files "${CMAKE_CURRENT_SOURCE_DIR}/translations/${_language}.ts")
    QT_MERGE_TRANSLATION("${CMAKE_CURRENT_BINARY_DIR}/translations/${_language}.ts" ${_plugin_dep_ts_files})
  endforeach()
  set(MY_TS_FILES)
  foreach(_language ${APPLICATION_LANGUAGES})
    list(APPEND MY_TS_FILES "${CMAKE_CURRENT_BINARY_DIR}/translations/${_language}.ts")
  endforeach()

  set_source_files_properties(${MY_TS_FILES} PROPERTIES OUTPUT_LOCATION ${_translations_dir})
  QT_ADD_TRANSLATION(_plugin_qm_files ${MY_TS_FILES})

  if(_plugin_qm_files)
    foreach(_qm_file ${_plugin_qm_files})
      file(RELATIVE_PATH _relative_qm_file ${CMAKE_CURRENT_BINARY_DIR} ${_qm_file})
      list(APPEND _plugin_cached_resources_in_binary_tree ${_relative_qm_file})
    endforeach()
  endif()

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
      NAME ${app_name}_cached.qrc
      PREFIX ${app_name}
      RESOURCES ${_plugin_cached_resources_in_source_tree}
      BINARY_RESOURCES ${_plugin_cached_resources_in_binary_tree})
  endif()

  source_group("Resources" FILES
    ${MY_QRC_FILES}
    ${MY_UI_FILES}
    ${MY_TS_FILES}
    )

  source_group("Generated" FILES
    ${MY_QRC_SRCS}
    ${MY_MOC_CPP}
    ${MY_UI_CPP}
    ${_plugin_qm_files}
    )

  add_executable(${app_name} WIN32 MACOSX_BUNDLE
    ${MY_SRC_FILES}
    ${MY_MOC_CPP}
    ${MY_UI_CPP}
    ${MY_QRC_SRCS}
    ${MY_QM_SRCS}
    )

  # Set labels associated with the target.
  set_target_properties(${app_name} PROPERTIES LABELS ${app_name})

  # Library properties specific to STATIC build
  if(MY_LIBRARY_TYPE STREQUAL "STATIC")
    if(CMAKE_SYSTEM_PROCESSOR STREQUAL "x86_64")
      set_target_properties(${app_name} PROPERTIES COMPILE_FLAGS "-fPIC")
    endif()
  endif()

  set(my_libs
    ${MY_TARGET_LIBRARIES}
    )

  foreach(_app_name ${MY_LIB_MODULES})
    list(APPEND my_libs ${${_app_name}_LIBRARIES})
  endforeach()

  if(MINGW)
    list(APPEND my_libs ssp) # add stack smash protection lib
  endif()
  target_link_libraries(${app_name} ${my_libs})

  if(MY_QT_MODULES)
      qt_use_modules(${app_name} ${MY_QT_MODULES})
  endif()

  if(APPLE)
  # configure CMake to use a custom Info.plist
    set_target_properties(${app_name} PROPERTIES MACOSX_BUNDLE_INFO_PLIST ${CMAKE_CURRENT_BINARY_DIR}/Info.plist )
  endif(APPLE)

  # Install headers
  # file(GLOB headers "${CMAKE_CURRENT_SOURCE_DIR}/*.h" "${CMAKE_CURRENT_SOURCE_DIR}/*.tpp")
  # install(FILES
  #  ${headers}
  #  ${dynamicHeaders}
  #  DESTINATION ${INSTALL_INCLUDE_DIR} COMPONENT Development
  #  )

endmacro()


