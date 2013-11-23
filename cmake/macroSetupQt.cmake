#! \ingroup CMakeUtilities
macro(MacroSetupQt)

  set(minimum_required_qt_version "5.2.0")

  # workround qt5 Qt5CoreConfig.cmake symbol link path bug
  find_program(QT_QMAKE_EXECUTABLE_FINDQT NAMES qmake qmake5 qmake-qt5 qmake4 qmake-qt4
               PATHS "${QT_SEARCH_PATH}/bin" "$ENV{QTDIR}/bin")
  set(QT_QMAKE_EXECUTABLE ${QT_QMAKE_EXECUTABLE_FINDQT} CACHE PATH "Qt qmake program.")

  exec_program(${QT_QMAKE_EXECUTABLE} ARGS "-query QT_VERSION" OUTPUT_VARIABLE QTVERSION)

  if(QTVERSION MATCHES "5.*")
      set(_qt_found 5)
  elseif(QTVERSION MATCHES "4.*")
      set(_qt_found 4)
  else()
      set(_qt_found 0)
  endif()

  exec_program(${QT_QMAKE_EXECUTABLE} ARGS "-query QT_INSTALL_PREFIX" OUTPUT_VARIABLE QT_INSTALL_PREFIX)
  set(CMAKE_PREFIX_PATH ${QT_INSTALL_PREFIX} ${CMAKE_PREFIX_PATH})

  if(${QTVERSION} VERSION_LESS ${minimum_required_qt_version})
    message(FATAL_ERROR "error: requires Qt >= ${minimum_required_qt_version} -- you cannot use Qt ${QT_VERSION_MAJOR}.${QT_VERSION_MINOR}.${QT_VERSION_PATCH}.")
  endif()

  message(STATUS "Found Qt ${QTVERSION}")

  if (_qt_found EQUAL 4)
    find_package(Qt4)
    set(QT_USE_QTNETWORK ON)
    set(QT_USE_QTOPENGL ON)
    set(QT_USE_QTSQL ON)
    set(QT_USE_QTXML ON)
    #set(QT_USE_QTSVG ON)
    #set(QT_USE_QTDBUS ON)
    #set(QT_USE_QTSCRIPT ON)
    set(QT_USE_QTWEBKIT ON)
    set(QT_USE_QTXMLPATTERNS ON)
    set(QT_USE_PHONON ON)
    set(QT_USE_QTTEST ${BUILD_TESTING})
    include(${QT_USE_FILE})

    # Set variable QT_INSTALLED_LIBRARY_DIR that will contains
    # Qt shared library
    set(QT_INSTALLED_LIBRARY_DIR ${QT_LIBRARY_DIR})
    if(WIN32)
      get_filename_component(QT_INSTALLED_LIBRARY_DIR ${QT_QMAKE_EXECUTABLE} PATH)
    endif()
  elseif(_qt_found EQUAL 5)
    find_package(Qt5Core QUIET)
    find_package(Qt5Gui REQUIRED)
    find_package(Qt5Widgets REQUIRED)
    find_package(Qt5Network REQUIRED)
    find_package(Qt5XmlPatterns REQUIRED)
    find_package(Qt5Concurrent REQUIRED)
    find_package(Qt5PrintSupport REQUIRED)
    find_package(Qt5Xml REQUIRED)
    find_package(Qt5Script REQUIRED)
    find_package(Qt5Sql REQUIRED)
    find_package(Qt5LinguistTools REQUIRED)
  else()
    message(FATAL_ERROR "Found unsuitable Qt ${QTVERSION}")
  endif()

  find_program(QT_LUPDATE_EXECUTABLE lupdate lupdate5 lupdate-qt5 lupdate4 lupdate-qt4
               PATHS "${QT_SEARCH_PATH}/bin" "$ENV{QTDIR}/bin")
  if(NOT QT_LUPDATE_EXECUTABLE)
    message(FATAL_ERROR "Could NOT find Qt lupdate")
  endif()

  find_program(QT_LCONVERT_EXECUTABLE lconvert lconvert5 lconver-qt5 lconvert4 lconvert-qt4
               PATHS "${QT_SEARCH_PATH}/bin" "$ENV{QTDIR}/bin")
  if(NOT QT_LCONVERT_EXECUTABLE)
    message(FATAL_ERROR "Could NOT find Qt lconvert")
  endif()

  set(CMAKE_AUTOMOC ON)

endmacro()

