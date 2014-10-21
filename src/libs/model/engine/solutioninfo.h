/****************************************************************************
**
** Copyright (C) 2013 Xiaojun Gao
** Contact: http://www.dailypips.org/legal
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
****************************************************************************/
#ifndef __OPENTRADE_SOLUTIONINFO_H__
#define __OPENTRADE_SOLUTIONINFO_H__

#include "opentrade_global.h"
#include "projectinfolist.h"

#include <QSharedDataPointer>
#include <QDebug>
#include <QString>


namespace OpenTrade {

namespace Internal {
class SolutionInfoPrivate;
}

class OPENTRADE_EXPORT SolutionInfo
{
public:

    ~SolutionInfo();

    SolutionInfo& operator=(const SolutionInfo &other);
    void swap(SolutionInfo &other) { qSwap(d, other.d); }

#ifdef Q_COMPILER_RVALUE_REFS
    inline SolutionInfo &operator=(SolutionInfo &&other)
    { qSwap(d, other.d); return *this; }
#endif

    bool operator==(const SolutionInfo &other) const;
    inline bool operator!=(const SolutionInfo &other) const { return !(operator==(other)); }


    QString name() const;
    void setName(const QString& name);

    ProjectInfoList projects() const;

    FileInfo scenarioFile() const;
    void setScenarioFile(const FileInfo& scenariofile);

    FileInfo solutionFile() const;
    void setSolutionFile(const FileInfo& solutionfile);

private:
    QSharedDataPointer<Internal::SolutionInfoPrivate> d;
};

QDebug OPENTRADE_EXPORT operator << (QDebug, const SolutionInfo &solutioninfo);

} // namespace OpenTrade

Q_DECLARE_SHARED(OpenTrade::SolutionInfo)

#endif // __OPENTRADE_SOLUTIONINFO_H__
