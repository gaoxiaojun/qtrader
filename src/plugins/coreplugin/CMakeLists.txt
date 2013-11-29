set(PLUGIN_NAME Core)

project( ${PLUGIN_NAME} )

cmake_minimum_required( VERSION 2.8.9 )

set(LIB_INCLUDE_DIR
    ${PROJECT_PLUGINS_INCLUDE_DIR}
    ${PLUGINS_INCLUDE_DIR}
    ${SRC_ROOT_DIR}    
    ${BINARY_ROOT_DIR}
)

set( LIB_SRC_FILES
basefilewizard.h
core_global.h
coreconstants.h
coreplugin.h
designmode.h
documentmanager.h
editmode.h
editortoolbar.h
fancyactionbar.h
fancytabwidget.h
featureprovider.h
fileiconprovider.h
fileutils.h
findplaceholder.h
generalsettings.h
generatedfile.h
helpmanager.h
icontext.h
icore.h
icorelistener.h
id.h
idocument.h
idocumentfactory.h
ifilewizardextension.h
imode.h
inavigationwidgetfactory.h
infobar.h
ioutputpane.h
iversioncontrol.h
macfullscreen.h
mainwindow.h
manhattanstyle.h
messagemanager.h
messageoutputwindow.h
mimedatabase.h
mimetypemagicdialog.h
mimetypesettings.h
minisplitter.h
modemanager.h
navigationsubwidget.h
navigationwidget.h
outputpane.h
outputpanemanager.h
outputwindow.h
plugindialog.h
removefiledialog.h
rightpane.h
settingsdatabase.h
sidebar.h
sidebarwidget.h
statusbarmanager.h
statusbarwidget.h
styleanimator.h
tabpositionindicator.h
textdocument.h
variablechooser.h
variablemanager.h
vcsmanager.h
versiondialog.h
basefilewizard.cpp
coreplugin.cpp
designmode.cpp
documentmanager.cpp
editmode.cpp
editortoolbar.cpp
fancyactionbar.cpp
fancytabwidget.cpp
featureprovider.cpp
fileiconprovider.cpp
fileutils.cpp
findplaceholder.cpp
generalsettings.cpp
generatedfile.cpp
helpmanager.cpp
icontext.cpp
icore.cpp
icorelistener.cpp
id.cpp
idocument.cpp
imode.cpp
inavigationwidgetfactory.cpp
infobar.cpp
iversioncontrol.cpp
mainwindow.cpp
manhattanstyle.cpp
messagemanager.cpp
messageoutputwindow.cpp
mimedatabase.cpp
mimetypemagicdialog.cpp
mimetypesettings.cpp
minisplitter.cpp
modemanager.cpp
navigationsubwidget.cpp
navigationwidget.cpp
outputpane.cpp
outputpanemanager.cpp
outputwindow.cpp
plugindialog.cpp
removefiledialog.cpp
rightpane.cpp
settingsdatabase.cpp
sidebar.cpp
sidebarwidget.cpp
statusbarmanager.cpp
statusbarwidget.cpp
styleanimator.cpp
tabpositionindicator.cpp
textdocument.cpp
variablechooser.cpp
variablemanager.cpp
vcsmanager.cpp
versiondialog.cpp
actionmanager/actioncontainer.h
actionmanager/actioncontainer_p.h
actionmanager/actionmanager.h
actionmanager/actionmanager_p.h
actionmanager/command.h
actionmanager/command_p.h
actionmanager/commandbutton.h
actionmanager/commandmappings.h
actionmanager/commandsfile.h
actionmanager/actioncontainer.cpp
actionmanager/actionmanager.cpp
actionmanager/command.cpp
actionmanager/commandbutton.cpp
actionmanager/commandmappings.cpp
actionmanager/commandsfile.cpp
dialogs/addtovcsdialog.h
dialogs/ioptionspage.h
dialogs/iwizard.h
dialogs/newdialog.h
dialogs/openwithdialog.h
dialogs/promptoverwritedialog.h
dialogs/readonlyfilesdialog.h
dialogs/saveitemsdialog.h
dialogs/settingsdialog.h
dialogs/shortcutsettings.h
dialogs/addtovcsdialog.cpp
dialogs/ioptionspage.cpp
dialogs/iwizard.cpp
dialogs/newdialog.cpp
dialogs/openwithdialog.cpp
dialogs/promptoverwritedialog.cpp
dialogs/readonlyfilesdialog.cpp
dialogs/saveitemsdialog.cpp
dialogs/settingsdialog.cpp
dialogs/shortcutsettings.cpp
editormanager/documentmodel.h
editormanager/editormanager.h
editormanager/editorview.h
editormanager/ieditor.h
editormanager/ieditorfactory.h
editormanager/iexternaleditor.h
editormanager/openeditorsview.h
editormanager/openeditorswindow.h
editormanager/systemeditor.h
editormanager/documentmodel.cpp
editormanager/editormanager.cpp
editormanager/editorview.cpp
editormanager/ieditor.cpp
editormanager/ieditorfactory.cpp
editormanager/iexternaleditor.cpp
editormanager/openeditorsview.cpp
editormanager/openeditorswindow.cpp
editormanager/systemeditor.cpp
progressmanager/futureprogress.h
progressmanager/progressbar.h
progressmanager/progressmanager.h
progressmanager/progressmanager_p.h
progressmanager/progressview.h
progressmanager/futureprogress.cpp
progressmanager/progressbar.cpp
progressmanager/progressmanager.cpp
progressmanager/progressview.cpp
)

if(WIN32)
  list(APPEND LIB_SRC_FILES progressmanager/progressmanager_win.cpp)
elseif(APPLE)
  list(APPEND LIB_SRC_FILES progressmanager/progressmanager_mac.mm macfullscreen.mm macfullscreen.h)
else()
  list(APPEND LIB_SRC_FILES progressmanager/progressmanager_x11.cpp)
endif()

file (GLOB_RECURSE LIB_UI_FILES  RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} [^.]*.ui)
file (GLOB_RECURSE LIB_QRC_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} [^.]*.qrc)
file (GLOB LIB_TS_FILES translations/*.ts)

set(LIB_DEPEND_LIBS utils QtCore QtWidgets QtNetwork QtScript QtConcurrent QtSql QtHelp QtXml QtPrintSupport extensionsystem)
#set(LIB_DEPEND_PLUGINS "")
#set(LIB_DEPEND_OPT_PLUGINS "")
#set(LIB_DEPEND_TS_LIBS "")

IF(APPLE)
   FIND_LIBRARY(APPKIT_LIBRARY Appkit)
   SET(EXTRA_LIBS ${APPKIT_LIBRARY})
ENDIF (APPLE)

MacroBuildPlugin(
    NAME ${PLUGIN_NAME}
    SRC_FILES ${LIB_SRC_FILES}
    UI_FILES ${LIB_UI_FILES}
    QRC_FILES ${LIB_QRC_FILES}
    DEPEND_LIBS ${LIB_DEPEND_LIBS}
#   DEPEND_PLUGINS ${LIB_DEPEND_PLUGINS}
#   DEPEND_OPT_PLUGINS ${LIB_DEPEND_OPT_PLUGINS}
    TARGET_LIBRARIES ${EXTRA_LIBS}
    INCLUDE_DIRECTORIES ${LIB_INCLUDE_DIR}
#    DEPEND_PLUGINS ${LIB_DEPEND_PLUGINS}
#    DEPEND_OPT_PLUGINS ${LIB_DEPEND_OPT_PLUGINS}
#    MERGE_TS_LIBS ${LIB_DEPEND_TS_LIBS}
)
