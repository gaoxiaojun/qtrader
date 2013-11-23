set(PLUGIN_NAME LUAEdtitor)

project( ${PLUGIN_NAME} )

cmake_minimum_required( VERSION 2.8.9 )

set(LIB_INCLUDE_DIR
    ${PROJECT_PLUGINS_INCLUDE_DIR}
    ${PLUGINS_INCLUDE_DIR}
    ${SRC_ROOT_DIR}    
    ${BINARY_ROOT_DIR}
)

set( LIB_SRC_FILES
luacompleter.h
luaconstants.h
luaeditor.h
luaindenter.h
luamanager.h
luatocpp.h
luacompleter.cpp
luaeditor.cpp
luaindenter.cpp
luamanager.cpp
luatocpp.cpp
)


file (GLOB_RECURSE LIB_UI_FILES  RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} [^.]*.ui)
file (GLOB_RECURSE LIB_QRC_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} [^.]*.qrc)
file (GLOB LIB_TS_FILES translations/*.ts)

set(LIB_EXPORT_DIRECTIVE "TEXTEDITOR_EXPORT")
set(LIB_DEPEND_LIBS QtCore QtWidgets QtNetwork QtScript QtConcurrent QtSql QtHelp QtXml QtPrintSupport extensionsystem utils)
set(LIB_DEPEND_PLUGINS Core Find Locator)
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
