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


#include "locatorplugin.h"

#include "basefilefilter.h"
#include "locatorfiltertest.h"

#include <coreplugin/testdatadir.h>
#include <utils/fileutils.h>

#include <QDir>
#include <QTextStream>
#include <QtTest>

using namespace Locator::Internal::Tests;

namespace {

class MyTestDataDir : public Core::Internal::Tests::TestDataDir
{
public:
    MyTestDataDir(const QString &testDataDirectory)
        : TestDataDir(QLatin1String(SRCDIR "/../../../tests/locators/") + testDataDirectory) {}
};

class MyBaseFileFilter : public Locator::BaseFileFilter
{
public:
    MyBaseFileFilter(const QStringList &theFiles)
    {
        files().clear();
        files().append(theFiles);
        BaseFileFilter::generateFileNames();
    }

    void refresh(QFutureInterface<void> &) {}

protected:
    void updateFiles() {}
};

inline QString _(const QByteArray &ba) { return QString::fromLatin1(ba, ba.size()); }

class ReferenceData
{
public:
    ReferenceData() {}
    ReferenceData(const QString &searchText, const ResultDataList &results)
        : searchText(searchText), results(results) {}

    QString searchText;
    ResultDataList results;
};

} // anonymous namespace

Q_DECLARE_METATYPE(ReferenceData)
Q_DECLARE_METATYPE(QList<ReferenceData>)

void Locator::Internal::LocatorPlugin::test_basefilefilter()
{
    QFETCH(QStringList, testFiles);
    QFETCH(QList<ReferenceData>, referenceDataList);

    MyBaseFileFilter filter(testFiles);
    BasicLocatorFilterTest test(&filter);

    foreach (const ReferenceData &reference, referenceDataList) {
        const QList<FilterEntry> filterEntries = test.matchesFor(reference.searchText);
        const ResultDataList results = ResultData::fromFilterEntryList(filterEntries);
//        QTextStream(stdout) << "----" << endl;
//        ResultData::printFilterEntries(results);
        QCOMPARE(results, reference.results);
    }
}

void Locator::Internal::LocatorPlugin::test_basefilefilter_data()
{
    QTest::addColumn<QStringList>("testFiles");
    QTest::addColumn<QList<ReferenceData> >("referenceDataList");

    const QChar pathSeparator = QDir::separator();
    const MyTestDataDir testDir(QLatin1String("testdata_basic"));
    const QStringList testFiles = QStringList()
        << testDir.file(QLatin1String("file.cpp"))
        << testDir.file(QLatin1String("main.cpp"))
        << testDir.file(QLatin1String("subdir/main.cpp"));
    QStringList testFilesShort;
    foreach (const QString &file, testFiles)
        testFilesShort << Utils::FileUtils::shortNativePath(Utils::FileName::fromString(file));

    QTest::newRow("BaseFileFilter-EmptyInput")
        << testFiles
        << (QList<ReferenceData>()
            << ReferenceData(
                QString(),
                (QList<ResultData>()
                    << ResultData(_("file.cpp"), testFilesShort.at(0))
                    << ResultData(_("main.cpp"), testFilesShort.at(1))
                    << ResultData(_("main.cpp"), testFilesShort.at(2))))
            );

    QTest::newRow("BaseFileFilter-InputIsFileName")
        << testFiles
        << (QList<ReferenceData>()
            << ReferenceData(
                _("main.cpp"),
                (QList<ResultData>()
                    << ResultData(_("main.cpp"), testFilesShort.at(1))
                    << ResultData(_("main.cpp"), testFilesShort.at(2))))
           );

    QTest::newRow("BaseFileFilter-InputIsFilePath")
        << testFiles
        << (QList<ReferenceData>()
            << ReferenceData(
                QString(_("subdir") + pathSeparator + _("main.cpp")),
                (QList<ResultData>()
                     << ResultData(_("main.cpp"), testFilesShort.at(2))))
            );

    QTest::newRow("BaseFileFilter-InputIsDirIsPath")
        << testFiles
        << (QList<ReferenceData>()
            << ReferenceData( _("subdir"), QList<ResultData>())
            << ReferenceData(
                QString(_("subdir") + pathSeparator + _("main.cpp")),
                (QList<ResultData>()
                     << ResultData(_("main.cpp"), testFilesShort.at(2))))
            );

    QTest::newRow("BaseFileFilter-InputIsFileNameFilePathFileName")
        << testFiles
        << (QList<ReferenceData>()
            << ReferenceData(
                _("main.cpp"),
                (QList<ResultData>()
                    << ResultData(_("main.cpp"), testFilesShort.at(1))
                    << ResultData(_("main.cpp"), testFilesShort.at(2))))
            << ReferenceData(
                QString(_("subdir") + pathSeparator + _("main.cpp")),
                (QList<ResultData>()
                     << ResultData(_("main.cpp"), testFilesShort.at(2))))
            << ReferenceData(
                _("main.cpp"),
                (QList<ResultData>()
                    << ResultData(_("main.cpp"), testFilesShort.at(1))
                    << ResultData(_("main.cpp"), testFilesShort.at(2))))
            );
}
