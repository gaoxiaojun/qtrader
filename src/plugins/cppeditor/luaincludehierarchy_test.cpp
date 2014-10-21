/****************************************************************************
**
** Copyright (C) 2013 Przemyslaw Gorszkowski <pgorszkowski@gmail.com>
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

#include "luaeditorplugin.h"
#include "luaincludehierarchymodel.h"

#include <cpptools/cppmodelmanagerinterface.h>
#include <utils/fileutils.h>

#include <QByteArray>
#include <QList>
#include <QtTest>

using namespace CPlusPlus;
using namespace LuaEditor::Internal;
using namespace CppTools;

namespace {
class TestCase
{
public:
    TestCase(const QList<QByteArray> &sourceList)
        : m_cmm(CppModelManagerInterface::instance())
    {
        QStringList filePaths;
        const int sourceListSize = sourceList.size();
        for (int i = 0; i < sourceListSize; ++i) {
            const QByteArray &source = sourceList.at(i);

            // Write source to file
            const QString fileName = QString::fromLatin1("%1/file%2.h").arg(QDir::tempPath())
                    .arg(i+1);
            Utils::FileSaver srcSaver(fileName);
            srcSaver.write(source);
            srcSaver.finalize();

            filePaths << fileName;
        }

        // Update Code Model
        m_cmm->updateSourceFiles(filePaths);

        // Wait for the parser in the future to give us the document
        QStringList filePathsNotYetInSnapshot(filePaths);
        forever {
            const Snapshot snapshot = m_cmm->snapshot();
            foreach (const QString &filePath, filePathsNotYetInSnapshot) {
                if (snapshot.contains(filePath))
                    filePathsNotYetInSnapshot.removeOne(filePath);
            }
            if (filePathsNotYetInSnapshot.isEmpty())
                break;
            QCoreApplication::processEvents();
        }
    }

    ~TestCase()
    {
        m_cmm->GC();
        QVERIFY(m_cmm->snapshot().isEmpty());
    }

    void run(int includesCount, int includedByCount) const
    {
        const QString fileName = QDir::tempPath() + QLatin1String("/file1.h");

        CppIncludeHierarchyModel model(0);
        model.buildHierarchy(fileName);
        QCOMPARE(model.rowCount(model.index(0, 0)), includesCount);
        QCOMPARE(model.rowCount(model.index(1, 0)), includedByCount);
    }

private:
    CppModelManagerInterface *m_cmm;
};
}

void LuaEditorPlugin::test_includeHierarchyModel_simpleIncludes()
{
    QList<QByteArray> sourceList;
    sourceList.append(QByteArray("#include \"file2.h\"\n"));
    sourceList.append(QByteArray());

    TestCase testCase(sourceList);
    testCase.run(1, 0);
}

void LuaEditorPlugin::test_includeHierarchyModel_simpleIncludedBy()
{
    QList<QByteArray> sourceList;
    sourceList.append(QByteArray());
    sourceList.append(QByteArray("#include \"file1.h\"\n"));

    TestCase testCase(sourceList);
    testCase.run(0, 1);
}

void LuaEditorPlugin::test_includeHierarchyModel_simpleIncludesAndIncludedBy()
{
    QList<QByteArray> sourceList;
    QByteArray source;
    sourceList.append(QByteArray("#include \"file2.h\"\n"));
    sourceList.append(QByteArray());
    sourceList.append(QByteArray("#include \"file1.h\"\n"));

    TestCase testCase(sourceList);
    testCase.run(1, 1);
}
