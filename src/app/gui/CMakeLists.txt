set(PROJECT_NAME ${APPLICATION_NAME})

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

# ui & qrc
file (GLOB APP_UI_FILES *.ui)
set (APP_QRC_FILES "application.qrc")

if(APPLE)
    # icon files to copy in the bundle
    file(GLOB ICON_FILES *.icns)
    list(LENGTH ICON_FILES _icon_files_count)
    if(${_icon_files_count} GREATER 0)
        list(GET ICON_FILES 0 APPLICATION_BUNDLE_ICON_FILE)
        if(${_icon_files_count} GREATER 1)
          message(STATUS "Warning:Found too many application icon file, using ${APPLICATION_BUNDLE_ICON_FILE}")
        else()
          message(STATUS "Application Icon: ${APPLICATION_BUNDLE_ICON_FILE}")
        endif()
    else()
        message(FAULT_ERROR "Cann't found application icon file")
    endif()
    get_filename_component(APPLICATION_BUNDLE_ICON_FILE ${APPLICATION_BUNDLE_ICON_FILE} NAME)
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Info.plist.in ${CMAKE_CURRENT_BINARY_DIR}/Info.plist)
    find_library(COREFOUND_LIBRARY CoreFoundation)
    find_library(CORESERVICE_LIBRARY CoreServices)
    set(EXTRA_LIBS ${COREFOUND_LIBRARY} ${CORESERVICE_LIBRARY})

    # set where in the bundle to put the icns files
    set_source_files_properties( ${APPLICATION_BUNDLE_ICON_FILE} PROPERTIES MACOSX_PACKAGE_LOCATION ${APPLICATION_DATA_PATH})
    # include the icns files in the target
    list(APPEND APP_SRC_FILES ${APPLICATION_BUNDLE_ICON_FILE})
endif(APPLE)

set(APP_DEPEND_LIBS QtCore QtNetwork extensionsystem breakpad)

MacroBuildApp(
    NAME ${PROJECT_NAME}
    SRC_FILES ${APP_SRC_FILES}
    UI_FILES ${APP_UI_FILES}
    QRC_FILES ${APP_QRC_FILES}
    DEPEND_LIBS ${APP_DEPEND_LIBS}
    INCLUDE_DIRECTORIES ${APP_INCLUDE_DIR}
    TARGET_LIBRARIES ${EXTRA_LIBS}
)
