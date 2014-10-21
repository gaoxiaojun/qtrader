#
# Depends on:
#  macroParseArguments.cmake
#
#! \brief Build a plug-in.
#!
#! This macro takes the usual arguments for building
#! a shared library using Qt. Additionally, it generates
#! plugin meta-data by creating a Plugin.xml file
#! which is embedded in the share library as a Qt resource.
#!
#! \ingroup CMakeAPI
macro(MacroBuildPlugin)
  MacroParseArguments(MY
    "NAME;SRC_FILES;MOC_FILES;UI_FILES;QRC_FILES;DEPEND_LIBS;DEPEND_PLUGINS;DEPEND_OPT_PLUGINS;MERGE_TS_LIBS;INCLUDE_DIRECTORIES;TARGET_LIBRARIES;CACHED_RESOURCEFILES;"
    ""
    ${ARGN}
    )

  # Sanity checks
  if(NOT DEFINED MY_NAME)
    message(FATAL_ERROR "NAME is mandatory")
  endif()
  
  # Define library name
  set(plugin_name ${MY_NAME})

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

  foreach(_lib_name ${MY_DEPEND_PLUGINS})
    string(TOUPPER ${_lib_name} _upper_lib_name)
    list(APPEND my_includes  ${${_upper_lib_name}_INCLUDE_DIR})
  endforeach()

  foreach(_lib_name ${MY_DEPEND_OPT_PLUGINS})
    string(TOUPPER ${_lib_name} _upper_lib_name)
    list(APPEND my_includes  ${${_upper_lib_name}_INCLUDE_DIR})
  endforeach()

  include_directories(
    ${my_includes}
    )

  # --------------------------------------------------------------------------
  # Library definition
  string(TOUPPER ${MY_NAME} MY_EXPORT_LIBNAME)
  add_definitions(-D${MY_EXPORT_LIBNAME}_LIBRARY)

  # --------------------------------------------------------------------------
  # Generator json
  #set_property(SOURCE ${CMAKE_CURRENT_BINARY_DIR}/${MY_NAME}.json APPEND PROPERTY OBJECT_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/OpenTrade.json.in")

  configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/${MY_NAME}.json.in
    ${CMAKE_CURRENT_BINARY_DIR}/${MY_NAME}.json
    @ONLY)

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
  # Create translation files (.ts and .qm)
  set(_plugin_qm_files )
  set(_plugin_cached_resources_in_binary_tree )
  set(_translations_dir "${CMAKE_CURRENT_BINARY_DIR}/translations")
  # Create translation files if not exist
  foreach(_language ${APPLICATION_LANGUAGES})
    set(_ts_file ${CMAKE_CURRENT_SOURCE_DIR}/translations/${_language}.ts)
    QT_CREATE_OR_UPDATE_TRANSLATION(${_ts_file} ${MY_SRC_FILES} ${MY_UI_FILES})
  endforeach()

  # Merge plugin ts file with depend librarys ts file
  foreach(_language ${APPLICATION_LANGUAGES})
    set(_plugin_dep_ts_files)
    foreach(_dep_libname ${MY_MERGE_TS_LIBS})
      string(TOUPPER ${_dep_libname} _dep_libname)
      set(_dep_ts_file ${${_dep_libname}_TRANSLATION_DIR}/${_language}.ts)
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

  # --------------------------------------------------------------------------
  # Resource
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
      NAME ${plugin_name}_cached.qrc
      PREFIX ${plugin_name}
      RESOURCES ${_plugin_cached_resources_in_source_tree}
      BINARY_RESOURCES ${_plugin_cached_resources_in_binary_tree})
  endif()

  # --------------------------------------------------------------------------
  # Build plugin
  add_library(Plugin_${plugin_name} SHARED
    ${MY_SRC_FILES}
    ${MY_MOC_CPP}
    ${MY_UI_CPP}
    ${MY_QRC_SRCS}
    ${_plugin_qm_files}
    )

  # Set labels associated with the target.
  set_target_properties(Plugin_${plugin_name} PROPERTIES OUTPUT_NAME ${plugin_name})

  set(my_libs
    ${MY_TARGET_LIBRARIES}
    )

  foreach(_lib_name ${MY_LIB_MODULES})
    list(APPEND my_libs ${${_lib_name}_LIBRARIES})
  endforeach()

  foreach(_lib_name ${MY_DEPEND_PLUGINS})
    string(TOUPPER ${_lib_name} _upper_lib_name)
    list(APPEND my_libs ${${_upper_lib_name}_PLUGIN_LIBRARIES})
  endforeach()

  foreach(_lib_name ${MY_DEPEND_OPT_PLUGINS})
    string(TOUPPER ${_lib_name} _upper_lib_name)
    list(APPEND my_libs ${${_upper_lib_name}_PLUGIN_LIBRARIES})
  endforeach()

  if(MINGW)
    list(APPEND my_libs ssp) # add stack smash protection lib
  endif()

  target_link_libraries(Plugin_${plugin_name} ${my_libs})

  if(MY_QT_MODULES)
      qt_use_modules(Plugin_${plugin_name} ${MY_QT_MODULES})
  endif()

  string(TOUPPER ${plugin_name} project_export)
  set(${project_export}_PLUGIN_LIBRARIES Plugin_${plugin_name} CACHE INTERNAL "" FORCE)
  set(${project_export}_INCLUDE_DIR ${my_includes} CACHE INTERNAL "" FORCE)
  if(NOT DEFINED MY_PLUGIN_VERSION)
    set(MY_PLUGIN_VERSION ${PLUGINS_DEFAULT_VERSION})
  endif()
  set(${project_export}_PLUGIN_VERSION ${MY_PLUGIN_VERSION} CACHE INTERNAL "" FORCE)

endmacro()


