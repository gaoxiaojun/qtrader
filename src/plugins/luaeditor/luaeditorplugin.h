/****************************************************************************
**
** Copyright (C) 2013 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of Qt Creator.
**
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.  For licensing terms and
** conditions see http://qt.digia.com/licensing.  For further information
** use the contact form at http://qt.digia.com/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Digia gives you certain additional
** rights.  These rights are described in the Digia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
****************************************************************************/

#ifndef CPPEDITORPLUGIN_H
#define CPPEDITORPLUGIN_H

#include "luaeditor.h"

#include <coreplugin/editormanager/ieditorfactory.h>

#include <extensionsystem/iplugin.h>

#include <QtPlugin>
#include <QAction>

namespace TextEditor {
class TextEditorActionHandler;
class ITextEditor;
} // namespace TextEditor

namespace LuaEditor {
namespace Internal {

class LuaEditorWidget;

class LuaEditorPlugin : public ExtensionSystem::IPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QtCreatorPlugin")

public:
    LuaEditorPlugin();
    ~LuaEditorPlugin();

    static LuaEditorPlugin *instance();

    bool initialize(const QStringList &arguments, QString *errorMessage = 0);
    void extensionsInitialized();
    ShutdownFlag aboutToShutdown();

    // Connect editor to settings changed signals.
    void initializeEditor(LuaEditorWidget *editor);

    bool sortedOutline() const;

/*signals:
    void outlineSortingChanged(bool sort);
    void typeHierarchyRequested();
    void includeHierarchyRequested();

public slots:
    void openDeclarationDefinitionInNextSplit();
    void openTypeHierarchy();
    void openIncludeHierarchy();
    void findUsages();
    void showPreProcessorDialog();
    void renameSymbolUnderCursor();
    void switchDeclarationDefinition();

    void setSortedOutline(bool sorted);

private slots:
    void onTaskStarted(Core::Id type);
    void onAllTasksFinished(Core::Id type);
    void currentEditorChanged(Core::IEditor *editor);*/

private:
    /*Core::IEditor *createEditor(QWidget *parent);
    void writeSettings();
    void readSettings();

    static LuaEditorPlugin *m_instance;

    TextEditor::TextEditorActionHandler *m_actionHandler;
    bool m_sortedOutline;
    QAction *m_renameSymbolUnderCursorAction;
    QAction *m_findUsagesAction;
    QAction *m_reparseExternallyChangedFiles;
    QAction *m_openTypeHierarchyAction;
    QAction *m_openIncludeHierarchyAction;

    CppQuickFixAssistProvider *m_quickFixProvider;

    QPointer<TextEditor::ITextEditor> m_currentEditor;*/
};

} // namespace Internal
} // namespace LuaEditor

#endif // CPPEDITORPLUGIN_H
