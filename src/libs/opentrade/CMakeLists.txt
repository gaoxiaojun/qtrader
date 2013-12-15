set(library_name opentrade)

project( ${library_name} )

cmake_minimum_required( VERSION 2.8.9 )

set( LIB_SRC_FILES
account.h
account.cpp
accountmanager.h
accountmanager.cpp
quote.h
quote.cpp
trade.h
trade.cpp
bar.h
bar_p.h
barmanager.h
barseries.h
backfillrequest.h
backfillprovidermanager.h
ibackfillprovider.h
imarketdataprovider.h
instrument.h
iexecutionprovider.h
iprovider.h
marketdataprovidermanager.h
opentrade_global.h
order.h
orderbook.h
executionprovidermanager.h
bar.cpp
barmanager.cpp
barseries.cpp
backfillrequest.cpp
backfillprovidermanager.cpp
instrument.cpp
marketdataprovidermanager.cpp
order.cpp
orderbook.cpp
executionprovidermanager.cpp
#instrumentmanager.h
#instrumentmanager.cpp
)

file (GLOB LIB_UI_FILES  RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} [^.]*.ui)
file (GLOB LIB_QRC_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} [^.]*.qrc)

set(LIB_DEPEND_LIBS QtCore QtWidgets extensionsystem)

MacroBuildLib(
    NAME ${library_name}
    SRC_FILES ${LIB_SRC_FILES}
    UI_FILES ${LIB_UI_FILES}
    QRC_FILES ${LIB_QRC_FILES}
    DEPEND_LIBS ${LIB_DEPEND_LIBS}
    INCLUDE_DIRECTORIES ${PROJECT_LIBS_INCLUDE_DIR}
)
