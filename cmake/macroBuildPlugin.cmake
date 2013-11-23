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
    "NAME;EXPORT_DIRECTIVE;SRC_FILES;MOC_FILES;UI_FILES;QRC_FILES;DEPEND_LIBS;DEPEND_PLUGINS;DEPEND_OPT_PLUGINS;MERGE_TS_LIBS;INCLUDE_DIRECTORIES;TARGET_LIBRARIES;CACHED_RESOURCEFILES;OUTPUT_DIR;MOC_OPTIONS;"
    "TEST_PLUGIN"
    ${ARGN}
    )

  # Sanity checks
  if(NOT DEFINED MY_NAME)
    message(FATAL_ERROR "NAME is mandatory")
  endif()
  if(NOT DEFINED MY_EXPORT_DIRECTIVE)
    message(FATAL_ERROR "EXPORT_DIRECTIVE is mandatory")
  endif()
  
  # Plugin are expected to be shared library
  set(MY_LIBRARY_TYPE "SHARED")

  # Define library name
  set(lib_name ${MY_NAME})

  # Plug-in target names must contain at leas one _
  if(lib_name MATCHES _)
    message(FATAL_ERROR "The plug-in project name ${lib_name} must not contain a '_' character")
  endif()
  
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


  # Add the generated manifest qrc file
  set(manifest_qrc_src )
  FunctionGeneratePluginXml(manifest_qrc_src
    NAME ${lib_name}
    REQUIRE_PLUGINS ${MY_DEPEND_PLUGINS}
    OPTIONAL_PLUGINS ${MY_DEPEND_OPT_PLUGINS}
    )

   #set_property(SOURCE ${manifest_qrc_src} APPEND
   #                PROPERTY OBJECT_DEPENDS "Plugin.xml.in")

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

  string(TOUPPER ${MY_NAME} MY_EXPORT_LIBNAME)
  string(TOLOWER ${MY_NAME} MY_EXPORT_HEADERNAME)
  set(MY_LIBRARY_EXPORT_DIRECTIVE ${MY_EXPORT_DIRECTIVE})
  add_definitions(-D${MY_EXPORT_LIBNAME}_LIBRARY)
  configure_file(
    ${CMAKE_MODULE_PATH}/Export.h.in
    ${CMAKE_CURRENT_BINARY_DIR}/${MY_EXPORT_HEADERNAME}_global.h
    )
  set(dynamicHeaders
    "${dynamicHeaders};${CMAKE_CURRENT_BINARY_DIR}/${MY_EXPORT_HEADERNAME}_global.h")

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

  list(APPEND MY_QRC_SRCS ${manifest_qrc_src})

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
    MacroGeneratePluginResourcefile(MY_QRC_SRCS
      NAME ${lib_name}_cached.qrc
      PREFIX ${lib_name}
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

  list(LENGTH MY_QT_MODULES qcount)
  list(LENGTH MY_MOC_FILES mcount)
  if(${qcount} GREATER 0 AND ${mcount} EQUAL 0)
    set(CMAKE_AUTOMOC ON)
  endif()

  add_library(${lib_name} ${MY_LIBRARY_TYPE}
    ${MY_SRC_FILES}
    ${MY_MOC_CPP}
    ${MY_UI_CPP}
    ${MY_QRC_SRCS}
    ${_plugin_qm_files}
    )

  # Set the output directory for the plugin
  #if(MY_OUTPUT_DIR)
  #  set(output_dir_suffix "/${MY_OUTPUT_DIR}")
  #else()
  #  set(output_dir_suffix "")
  #endif()

  #foreach(type RUNTIME LIBRARY ARCHIVE)
    #if(NOT DEFINED CTK_PLUGIN_${type}_OUTPUT_DIRECTORY AND CMAKE_${type}_OUTPUT_DIRECTORY)
      # Put plug-ins by default into a "plugins" subdirectory
      #set(CTK_PLUGIN_${type}_OUTPUT_DIRECTORY "${CMAKE_${type}_OUTPUT_DIRECTORY}/plugins")
    #endif()
    
    #if(IS_ABSOLUTE "${CTK_PLUGIN_${type}_OUTPUT_DIRECTORY}")
      #set(plugin_${type}_output_dir "${CTK_PLUGIN_${type}_OUTPUT_DIRECTORY}${output_dir_suffix}")
    #elseif(CMAKE_${type}_OUTPUT_DIRECTORY)
      #set(plugin_${type}_output_dir "${CMAKE_${type}_OUTPUT_DIRECTORY}/${CTK_PLUGIN_${type}_OUTPUT_DIRECTORY}${output_dir_suffix}")
    #else()
      #set(plugin_${type}_output_dir "${CMAKE_CURRENT_BINARY_DIR}/${CTK_PLUGIN_${type}_OUTPUT_DIRECTORY}${output_dir_suffix}")
    #endif()

    #if(MY_TEST_PLUGIN)
      # Test plug-ins will always be put in a separate directory
      #if(CMAKE_${type}_OUTPUT_DIRECTORY)
        #set(plugin_${type}_output_dir "${CMAKE_${type}_OUTPUT_DIRECTORY}/test_plugins")
      #else()
        #set(plugin_${type}_output_dir "${PROJECT_BINARY_DIR}/test_plugins")
      #endif()
    #endif()
  #endforeach()

  #set(plugin_compile_flags "-DQT_PLUGIN")
  #ctkFunctionGetCompilerVisibilityFlags(plugin_compile_flags)

  # Apply properties to the library target.
  #set_target_properties(${lib_name} PROPERTIES
    #COMPILE_FLAGS "${plugin_compile_flags}"
    #RUNTIME_OUTPUT_DIRECTORY ${plugin_RUNTIME_output_dir}
    #LIBRARY_OUTPUT_DIRECTORY ${plugin_LIBRARY_output_dir}
    #ARCHIVE_OUTPUT_DIRECTORY ${plugin_ARCHIVE_output_dir}
    #PREFIX "lib"
    #)

  #if(NOT MY_TEST_PLUGIN)
    # Install rules
    #install(TARGETS ${lib_name} EXPORT CTKExports
      #RUNTIME DESTINATION ${CTK_INSTALL_PLUGIN_DIR} COMPONENT RuntimePlugins
      #LIBRARY DESTINATION ${CTK_INSTALL_PLUGIN_DIR} COMPONENT RuntimePlugins
      #ARCHIVE DESTINATION ${CTK_INSTALL_PLUGIN_DIR} COMPONENT Development)
  #endif()

  # Set labels associated with the target.
  set_target_properties(${lib_name} PROPERTIES LABELS ${lib_name})

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

  target_link_libraries(${lib_name} ${my_libs})

  if(${qcount} GREATER 0)
      qt_use_modules(${lib_name} ${MY_QT_MODULES})
  endif()

  string(TOUPPER ${lib_name} project_export)
  set(${project_export}_PLUGIN_LIBRARIES ${lib_name} CACHE INTERNAL "" FORCE)
  set(${project_export}_INCLUDE_DIR ${my_includes} CACHE INTERNAL "" FORCE)
  if(NOT DEFINED MY_PLUGIN_VERSION)
    set(MY_PLUGIN_VERSION ${PLUGINS_DEFAULT_VERSION})
  endif()
  set(${project_export}_PLUGIN_VERSION ${MY_PLUGIN_VERSION} CACHE INTERNAL "Plugin Version" FORCE)

  #if(NOT MY_TEST_PLUGIN)
    # Install headers
  #  file(GLOB headers "${CMAKE_CURRENT_SOURCE_DIR}/*.h" "${CMAKE_CURRENT_SOURCE_DIR}/*.tpp")
  #  install(FILES
  #    ${headers}
  #    ${dynamicHeaders}
  #    DESTINATION ${CTK_INSTALL_PLUGIN_INCLUDE_DIR}/${Plugin-SymbolicName} COMPONENT Development
  #    )
  #endif()

endmacro()


