set(PLUGIN_NAME Locator)

project( ${PLUGIN_NAME} )

cmake_minimum_required( VERSION 2.8.9 )

set(LIB_INCLUDE_DIR
    ${PROJECT_PLUGINS_INCLUDE_DIR}
    ${PLUGINS_INCLUDE_DIR}
    ${SRC_ROOT_DIR}    
    ${BINARY_ROOT_DIR}
)

set( LIB_SRC_FILES
basefilefilter.h
commandlocator.h
directoryfilter.h
executefilter.h
filesystemfilter.h
ilocatorfilter.h
locator_global.h
locatorconstants.h
locatorfiltersfilter.h
locatormanager.h
locatorplugin.h
locatorsearchutils.h
locatorwidget.h
opendocumentsfilter.h
settingspage.h
basefilefilter.cpp
commandlocator.cpp
directoryfilter.cpp
executefilter.cpp
filesystemfilter.cpp
ilocatorfilter.cpp
locatorfiltersfilter.cpp
locatormanager.cpp
locatorplugin.cpp
locatorsearchutils.cpp
locatorwidget.cpp
opendocumentsfilter.cpp
settingspage.cpp
)


file (GLOB_RECURSE LIB_UI_FILES  RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} [^.]*.ui)
file (GLOB_RECURSE LIB_QRC_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} [^.]*.qrc)
file (GLOB LIB_TS_FILES translations/*.ts)

set(LIB_EXPORT_DIRECTIVE "LOCATOR_EXPORT")
set(LIB_DEPEND_LIBS utils QtCore QtWidgets QtNetwork QtScript QtConcurrent QtSql QtHelp QtXml QtPrintSupport extensionsystem)
set(LIB_DEPEND_PLUGINS "Core")
#set(LIB_DEPEND_OPT_PLUGINS "")
#set(LIB_DEPEND_TS_LIBS "")


MacroBuildPlugin(
    NAME ${PLUGIN_NAME}
    EXPORT_DIRECTIVE ${LIB_EXPORT_DIRECTIVE}
    SRC_FILES ${LIB_SRC_FILES}
    UI_FILES ${LIB_UI_FILES}
    QRC_FILES ${LIB_QRC_FILES}
    DEPEND_LIBS ${LIB_DEPEND_LIBS}
   DEPEND_PLUGINS ${LIB_DEPEND_PLUGINS}
    INCLUDE_DIRECTORIES ${LIB_INCLUDE_DIR}
)
