set(PLUGIN_NAME TextEdtitor)

project( ${PLUGIN_NAME} )

cmake_minimum_required( VERSION 2.8.9 )

set(LIB_INCLUDE_DIR
    ${PROJECT_PLUGINS_INCLUDE_DIR}
    ${PLUGINS_INCLUDE_DIR}
    ${SRC_ROOT_DIR}    
    ${BINARY_ROOT_DIR}
)

set( LIB_SRC_FILES
autocompleter.h
basefilefind.h
basefilefind_p.h
basehoverhandler.h
basetextdocument.h
basetextdocumentlayout.h
basetexteditor.h
basetexteditor_p.h
basetextmark.h
basetextmarkregistry.h
behaviorsettings.h
behaviorsettingspage.h
behaviorsettingswidget.h
circularclipboard.h
circularclipboardassist.h
codecselector.h
codestyleeditor.h
codestylepool.h
codestyleselectorwidget.h
colorscheme.h
colorschemeedit.h
completionsettings.h
convenience.h
displaysettings.h
displaysettingspage.h
extraencodingsettings.h
findincurrentfile.h
findinfiles.h
findinopenfiles.h
fontsettings.h
fontsettingspage.h
helpitem.h
highlighterutils.h
icodestylepreferences.h
icodestylepreferencesfactory.h
ihighlighterfactory.h
indenter.h
ioutlinewidget.h
itexteditor.h
itextmark.h
linenumberfilter.h
normalindenter.h
outlinefactory.h
plaintexteditor.h
plaintexteditorfactory.h
quickfix.h
refactoringchanges.h
refactoroverlay.h
semantichighlighter.h
simplecodestylepreferences.h
simplecodestylepreferenceswidget.h
storagesettings.h
syntaxhighlighter.h
tabsettings.h
tabsettingswidget.h
texteditor_global.h
texteditoractionhandler.h
texteditorconstants.h
texteditoroptionspage.h
texteditoroverlay.h
texteditorplugin.h
texteditorsettings.h
textfilewizard.h
typingsettings.h
autocompleter.cpp
basefilefind.cpp
basehoverhandler.cpp
basetextdocument.cpp
basetextdocumentlayout.cpp
basetexteditor.cpp
basetextmark.cpp
behaviorsettings.cpp
behaviorsettingspage.cpp
behaviorsettingswidget.cpp
circularclipboard.cpp
circularclipboardassist.cpp
codecselector.cpp
codestyleeditor.cpp
codestylepool.cpp
codestyleselectorwidget.cpp
colorscheme.cpp
colorschemeedit.cpp
completionsettings.cpp
convenience.cpp
displaysettings.cpp
displaysettingspage.cpp
extraencodingsettings.cpp
findincurrentfile.cpp
findinfiles.cpp
findinopenfiles.cpp
fontsettings.cpp
fontsettingspage.cpp
helpitem.cpp
highlighterutils.cpp
icodestylepreferences.cpp
icodestylepreferencesfactory.cpp
indenter.cpp
itexteditor.cpp
itextmark.cpp
linenumberfilter.cpp
normalindenter.cpp
outlinefactory.cpp
plaintexteditor.cpp
plaintexteditorfactory.cpp
quickfix.cpp
refactoringchanges.cpp
refactoroverlay.cpp
semantichighlighter.cpp
simplecodestylepreferences.cpp
simplecodestylepreferenceswidget.cpp
storagesettings.cpp
syntaxhighlighter.cpp
tabsettings.cpp
tabsettingswidget.cpp
texteditoractionhandler.cpp
texteditorconstants.cpp
texteditoroptionspage.cpp
texteditoroverlay.cpp
texteditorplugin.cpp
texteditorsettings.cpp
textfilewizard.cpp
typingsettings.cpp
codeassist/assistenums.h
codeassist/basicproposalitem.h
codeassist/basicproposalitemlistmodel.h
codeassist/codeassistant.h
codeassist/completionassistprovider.h
codeassist/defaultassistinterface.h
codeassist/functionhintproposal.h
codeassist/functionhintproposalwidget.h
codeassist/genericproposal.h
codeassist/genericproposalwidget.h
codeassist/iassistinterface.h
codeassist/iassistprocessor.h
codeassist/iassistproposal.h
codeassist/iassistproposalitem.h
codeassist/iassistproposalmodel.h
codeassist/iassistproposalwidget.h
codeassist/iassistprovider.h
codeassist/ifunctionhintproposalmodel.h
codeassist/igenericproposalmodel.h
codeassist/keywordscompletionassist.h
codeassist/quickfixassistprocessor.h
codeassist/quickfixassistprovider.h
codeassist/runner.h
codeassist/basicproposalitem.cpp
codeassist/basicproposalitemlistmodel.cpp
codeassist/codeassistant.cpp
codeassist/completionassistprovider.cpp
codeassist/defaultassistinterface.cpp
codeassist/functionhintproposal.cpp
codeassist/functionhintproposalwidget.cpp
codeassist/genericproposal.cpp
codeassist/genericproposalwidget.cpp
codeassist/iassistinterface.cpp
codeassist/iassistprocessor.cpp
codeassist/iassistproposal.cpp
codeassist/iassistproposalitem.cpp
codeassist/iassistproposalmodel.cpp
codeassist/iassistproposalwidget.cpp
codeassist/iassistprovider.cpp
codeassist/ifunctionhintproposalmodel.cpp
codeassist/igenericproposalmodel.cpp
codeassist/keywordscompletionassist.cpp
codeassist/quickfixassistprocessor.cpp
codeassist/quickfixassistprovider.cpp
codeassist/runner.cpp
generichighlighter/context.h
generichighlighter/definitiondownloader.h
generichighlighter/dynamicrule.h
generichighlighter/highlightdefinition.h
generichighlighter/highlightdefinitionhandler.h
generichighlighter/highlightdefinitionmetadata.h
generichighlighter/highlighter.h
generichighlighter/highlighterexception.h
generichighlighter/highlightersettings.h
generichighlighter/highlightersettingspage.h
generichighlighter/includerulesinstruction.h
generichighlighter/itemdata.h
generichighlighter/keywordlist.h
generichighlighter/managedefinitionsdialog.h
generichighlighter/manager.h
generichighlighter/progressdata.h
generichighlighter/reuse.h
generichighlighter/rule.h
generichighlighter/specificrules.h
generichighlighter/context.cpp
generichighlighter/definitiondownloader.cpp
generichighlighter/dynamicrule.cpp
generichighlighter/highlightdefinition.cpp
generichighlighter/highlightdefinitionhandler.cpp
generichighlighter/highlighter.cpp
generichighlighter/highlightersettings.cpp
generichighlighter/highlightersettingspage.cpp
generichighlighter/includerulesinstruction.cpp
generichighlighter/itemdata.cpp
generichighlighter/keywordlist.cpp
generichighlighter/managedefinitionsdialog.cpp
generichighlighter/manager.cpp
generichighlighter/progressdata.cpp
generichighlighter/rule.cpp
generichighlighter/specificrules.cpp
snippets/isnippetprovider.h
snippets/plaintextsnippetprovider.h
snippets/reuse.h
snippets/snippet.h
snippets/snippetassistcollector.h
snippets/snippeteditor.h
snippets/snippetscollection.h
snippets/snippetssettings.h
snippets/snippetssettingspage.h
snippets/isnippetprovider.cpp
snippets/plaintextsnippetprovider.cpp
snippets/snippet.cpp
snippets/snippetassistcollector.cpp
snippets/snippeteditor.cpp
snippets/snippetscollection.cpp
snippets/snippetssettings.cpp
snippets/snippetssettingspage.cpp
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
