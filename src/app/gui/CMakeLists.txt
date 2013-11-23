set(PROJECT_NAME QTrader)

project(${PROJECT_NAME} )

cmake_minimum_required( VERSION 2.8.9 )

set(CMAKE_AUTOMOC ON)

set(APP_INCLUDE_DIR
    ${CMAKE_CURRENT_SOURCE_DIR}/../utils/breakpad
    ${CMAKE_CURRENT_SOURCE_DIR}/../utils/qtsingleapplication
    ${PROJECT_LIBS_INCLUDE_DIR}
    ${BINARY_ROOT_DIR}
    ${BREAKPAD_INCLUDE_DIR}
)

if(APPLE)
  CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/Info.plist.in ${CMAKE_CURRENT_BINARY_DIR}/Info.plist)
  find_library(COREFOUND_LIBRARY CoreFoundation)
  find_library(CORESERVICE_LIBRARY CoreServices)
  SET(EXTRA_LIBS ${COREFOUND_LIBRARY} ${CORESERVICE_LIBRARY})
endif()

set( APP_SRC_FILES
main.cpp
../utils/qtsingleapplication/qtlocalpeer.h
../utils/qtsingleapplication/qtlockedfile.h
../utils/qtsingleapplication/qtsingleapplication.h
../utils/qtsingleapplication/qtlocalpeer.cpp
../utils/qtsingleapplication/qtlockedfile.cpp
../utils/qtsingleapplication/qtsingleapplication.cpp
../utils/breakpad/breakpad.cpp
../utils/breakpad/crashreportdialog.cpp
)
if(WIN32)
  list(APPEND APP_SRC_FILES ../utils/qtsingleapplication/qtlockedfile_win.cpp)
else()
  list(APPEND APP_SRC_FILES ../utils/qtsingleapplication/qtlockedfile_unix.cpp)
endif()

# breakpad
list(APPEND APP_SRC_FILES ${BREAKPAD_SOURCE_FILES})

# ui & qrc
file (GLOB APP_UI_FILES *.ui)
set (APP_QRC_FILES "application.qrc")

if(APPLE)
    # icon files to copy in the bundle
    set (OSX_ICON_FILES application.icns)
    # set where in the bundle to put the icns files
    set_source_files_properties( ${OSX_ICON_FILES} PROPERTIES MACOSX_PACKAGE_LOCATION ${APPLICATION_DATA_PATH})
    # include the icns files in the target
    list(APPEND APP_SRC_FILES ${OSX_ICON_FILES})
endif(APPLE)

set(APP_DEPEND_LIBS QtCore QtWidgets QtNetwork extensionsystem)

MacroBuildApp(
    NAME ${PROJECT_NAME}
    SRC_FILES ${APP_SRC_FILES}
    UI_FILES ${APP_UI_FILES}
    QRC_FILES ${APP_QRC_FILES}
    DEPEND_LIBS ${APP_DEPEND_LIBS}
    INCLUDE_DIRECTORIES ${APP_INCLUDE_DIR}
    TARGET_LIBRARIES ${EXTRA_LIBS}
)
