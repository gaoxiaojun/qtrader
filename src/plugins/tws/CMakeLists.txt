set(PLUGIN_NAME Tws)

project( ${PLUGIN_NAME} )

cmake_minimum_required( VERSION 2.8.9 )

set(LIB_INCLUDE_DIR
    ${PROJECT_PLUGINS_INCLUDE_DIR}
    ${PLUGINS_INCLUDE_DIR}
    ${SRC_ROOT_DIR}    
    ${BINARY_ROOT_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/IBJts/source/posixclient/shared
)

add_definitions (-DIB_USE_STD_STRING)

set( LIB_SRC_FILES
    twsclient.h
    twsclient.cpp
    IBJts/source/posixclient/src/EClientSocketBase.cpp
    IBJts/source/posixclient/src/EPosixClientSocket.cpp
    twswrapper.h
    twswrapper.cpp
    twsplugin.h
    twsplugin.cpp
)


file (GLOB_RECURSE LIB_UI_FILES  RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} [^.]*.ui)
file (GLOB_RECURSE LIB_QRC_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} [^.]*.qrc)
file (GLOB LIB_TS_FILES translations/*.ts)

set(LIB_EXPORT_DIRECTIVE "TWS_EXPORT")
set(LIB_DEPEND_LIBS utils QtCore QtWidgets QtNetwork QtScript QtConcurrent QtSql QtHelp QtXml QtPrintSupport extensionsystem)
set(LIB_DEPEND_PLUGINS "OpenTrade" "Core" )
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
