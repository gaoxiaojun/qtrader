#
# Depends on:
#  macroParseArguments.cmake
#

#! \ingroup CMakeUtilities
function(FunctionGetPluginVersion PLUGINAME VERSION )
   string(TOUPPER ${PLUGINAME} _upper_name)
   set(${VERSION} ${${_upper_name}_PLUGIN_VERSION} PARENT_SCOPE)
endfunction()

function(FunctionGeneratePluginXml QRC_SRCS)

  MacroParseArguments(MY
    "NAME;REQUIRE_PLUGINS;OPTIONAL_PLUGINS"
    ""
    ${ARGN}
    )

  if(NOT DEFINED MY_NAME)
    message(FATAL_ERROR "NAME is mandatory")
  endif()

  set(_dependency_context "")
  if(DEFINED MY_REQUIRE_PLUGINS OR DEFINED MY_OPTIONAL_PLUGINS)
    set(_dependency_context "${_dependency_context}\n\t<dependencyList>")
  endif()

  if(DEFINED MY_REQUIRE_PLUGINS)
    foreach(_plugin ${MY_REQUIRE_PLUGINS})
        FunctionGetPluginVersion(${_plugin} _version)
        set(_dependency_context "${_dependency_context}\n\t\t<dependency name=\"${_plugin}\" version=\"${_version}\"/>")
    endforeach()
  endif()

  if(DEFINED MY_OPTIONAL_PLUGINS)
    foreach(_plugin ${MY_REQUIRE_PLUGINS})
        FunctionGetPluginVersion(${_plugin} _version)
        set(_dependency_context "${_dependency_context}\n\t\t<dependency name=\"${_plugin}\" version=\"${_version}\" type=\"optional\"/>")
    endforeach()
  endif()

  if(DEFINED MY_REQUIRE_PLUGINS OR DEFINED MY_OPTIONAL_PLUGINS)
    set(_dependency_context "${_dependency_context}\n\t</dependencyList>")
  endif()

  set(PLUGIN_DEPENDENCYS ${_dependency_context})
  set(_pluginxml_filename "Plugin.xml")
  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/${_pluginxml_filename}.in ${CMAKE_CURRENT_BINARY_DIR}/${_pluginxml_filename})
  set(_pluginxml_qrc_filepath "${CMAKE_CURRENT_BINARY_DIR}/${MY_NAME}_manifest.qrc")

  set(_manifest_qrc_content
"<!DOCTYPE RCC><RCC version=\"1.0\">
<qresource prefix=\"/${MY_NAME}/META-INF\">
 <file>${_pluginxml_filename}</file>
</qresource>
</RCC>
")

  configure_file("${CMAKE_MODULE_PATH}/plugin_xml.qrc.in" "${_pluginxml_qrc_filepath}" @ONLY)

  QT_ADD_RESOURCES(_qrc_src ${_pluginxml_qrc_filepath})

  set(${QRC_SRCS} ${${QRC_SRCS}} ${_qrc_src} PARENT_SCOPE)

endfunction()
