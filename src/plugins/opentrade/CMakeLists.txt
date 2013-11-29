set(PLUGIN_NAME OpenTrade)

project( Plugin_${PLUGIN_NAME} )

cmake_minimum_required( VERSION 2.8.9 )

set(LIB_INCLUDE_DIR
    ${PROJECT_PLUGINS_INCLUDE_DIR}
    ${PLUGINS_INCLUDE_DIR}
    ${SRC_ROOT_DIR}    
    ${BINARY_ROOT_DIR}
)

set( LIB_SRC_FILES
  quote.cpp
  bar.cpp
  orderbook.cpp
  instrument.cpp
  order.h
  order.cpp
  opentradeplugin.h
  opentradeplugin.cpp
  iprovider.h
  iorderexecutionprovider.h
  imarketdataprovider.h
  ihistoricalprovider.h
  historicaldatarequest.cpp
  marketdataprovidermanager.h
  marketdataprovidermanager.cpp
  orderexecutionprovidermanager.h
  orderexecutionprovidermanager.cpp
  historicalprovidermanager.cpp
  historicalprovidermanager.h
)
file (GLOB_RECURSE LIB_UI_FILES  RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} [^.]*.ui)
file (GLOB_RECURSE LIB_QRC_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} [^.]*.qrc)
file (GLOB LIB_TS_FILES translations/*.ts)

set(LIB_DEPEND_LIBS QtCore QtWidgets extensionsystem)

MacroBuildPlugin(
    NAME ${PLUGIN_NAME}
    SRC_FILES ${LIB_SRC_FILES}
    UI_FILES ${LIB_UI_FILES}
    QRC_FILES ${LIB_QRC_FILES}
    DEPEND_LIBS ${LIB_DEPEND_LIBS}
    INCLUDE_DIRECTORIES ${LIB_INCLUDE_DIR}
)
