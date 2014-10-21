set(library_name utils)

project( ${library_name} )

cmake_minimum_required( VERSION 2.8.9 )

include_directories(
    ${PROJECT_LIBS_INCLUDE_DIR}
)

set( LIB_SRC_FILES
annotateditemdelegate.h
ansiescapecodehandler.h
appmainwindow.h
basetreeview.h
basevalidatinglineedit.h
bracematcher.h
buildablehelperlibrary.h
changeset.h
checkablemessagebox.h
classnamevalidatinglineedit.h
codegeneration.h
completingtextedit.h
consoleprocess.h
consoleprocess_p.h
crumblepath.h
detailsbutton.h
detailswidget.h
elfreader.h
elidinglabel.h
environment.h
environmentmodel.h
faketooltip.h
fancylineedit.h
fancymainwindow.h
fileinprojectfinder.h
filenamevalidatinglineedit.h
filesearch.h
filesystemwatcher.h
fileutils.h
filewizarddialog.h
filewizardpage.h
filterlineedit.h
flowlayout.h
function.h
headerviewstretcher.h
historycompleter.h
hostosinfo.h
htmldocextractor.h
ipaddresslineedit.h
iwelcomepage.h
json.h
linecolumnlabel.h
listutils.h
multitask.h
navigationtreeview.h
networkaccessmanager.h
newclasswidget.h
osspecificaspects.h
outputformat.h
outputformatter.h
parameteraction.h
pathchooser.h
pathlisteditor.h
persistentsettings.h
portlist.h
projectintropage.h
projectnamevalidatinglineedit.h
proxyaction.h
qtcassert.h
qtcolorbutton.h
qtcoverride.h
qtcprocess.h
reloadpromptutils.h
runextensions.h
savedaction.h
savefile.h
settingsselector.h
settingsutils.h
sleep.h
statuslabel.h
stringutils.h
styledbar.h
stylehelper.h
synchronousprocess.h
tcpportsgatherer.h
textfileformat.h
uncommentselection.h
unixutils.h
utils_global.h
winutils.h
wizard.h
annotateditemdelegate.cpp
ansiescapecodehandler.cpp
appmainwindow.cpp
basetreeview.cpp
basevalidatinglineedit.cpp
bracematcher.cpp
buildablehelperlibrary.cpp
changeset.cpp
checkablemessagebox.cpp
classnamevalidatinglineedit.cpp
codegeneration.cpp
completingtextedit.cpp
consoleprocess.cpp
crumblepath.cpp
detailsbutton.cpp
detailswidget.cpp
elfreader.cpp
elidinglabel.cpp
environment.cpp
environmentmodel.cpp
faketooltip.cpp
fancylineedit.cpp
fancymainwindow.cpp
fileinprojectfinder.cpp
filenamevalidatinglineedit.cpp
filesearch.cpp
filesystemwatcher.cpp
fileutils.cpp
filewizarddialog.cpp
filewizardpage.cpp
filterlineedit.cpp
flowlayout.cpp
function.cpp
headerviewstretcher.cpp
historycompleter.cpp
hostosinfo.cpp
htmldocextractor.cpp
ipaddresslineedit.cpp
iwelcomepage.cpp
json.cpp
linecolumnlabel.cpp
navigationtreeview.cpp
networkaccessmanager.cpp
newclasswidget.cpp
outputformatter.cpp
parameteraction.cpp
pathchooser.cpp
pathlisteditor.cpp
persistentsettings.cpp
portlist.cpp
projectintropage.cpp
projectnamevalidatinglineedit.cpp
proxyaction.cpp
qtcassert.cpp
qtcolorbutton.cpp
qtcprocess.cpp
reloadpromptutils.cpp
savedaction.cpp
savefile.cpp
settingsselector.cpp
sleep.cpp
statuslabel.cpp
stringutils.cpp
styledbar.cpp
stylehelper.cpp
synchronousprocess.cpp
tcpportsgatherer.cpp
textfileformat.cpp
uncommentselection.cpp
wizard.cpp
tooltip/effects.h
tooltip/reuse.h
tooltip/tipcontents.h
tooltip/tips.h
tooltip/tooltip.h
tooltip/tipcontents.cpp
tooltip/tips.cpp
tooltip/tooltip.cpp
)

if(WIN32)
  list(APPEND LIB_SRC_FILES consoleprocess_win.cpp process_ctrlc_stub.cpp winutils.cpp)
else()
  list(APPEND LIB_SRC_FILES consoleprocess_unix.cpp unixutils.cpp)
endif()

file (GLOB LIB_UI_FILES  RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} [^.]*.ui)
file (GLOB LIB_QRC_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} [^.]*.qrc)

set(LIB_DEPEND_LIBS QtCore QtWidgets QtNetwork QtScript QtConcurrent extensionsystem)

MacroBuildLib(
    NAME ${library_name}
    SRC_FILES ${LIB_SRC_FILES}
    UI_FILES ${LIB_UI_FILES}
    QRC_FILES ${LIB_QRC_FILES}
    DEPEND_LIBS ${LIB_DEPEND_LIBS}
)
