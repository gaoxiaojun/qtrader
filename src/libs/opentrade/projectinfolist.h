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
#ifndef __OPENTRADE_PROJECTINFOLIST_H__
#define __OPENTRADE_PROJECTINFOLIST_H__

#include "opentrade_global.h"
#include "projectinfo.h"

#include <QSharedDataPointer>
#include <QDebug>
#include <QString>


namespace OpenTrade {

namespace Internal {
class ProjectInfoListPrivate;
}

class OPENTRADE_EXPORT ProjectInfoList
{
public:

    ~ProjectInfoList();

    ProjectInfoList& operator=(const ProjectInfoList &other);
    void swap(ProjectInfoList &other) { qSwap(d, other.d); }

#ifdef Q_COMPILER_RVALUE_REFS
    inline ProjectInfoList &operator=(ProjectInfoList &&other)
    { qSwap(d, other.d); return *this; }
#endif

    bool operator==(const ProjectInfoList &other) const;
    inline bool operator!=(const ProjectInfoList &other) const { return !(operator==(other)); }

    bool contains(const QString& name);
    bool tryGetValue(const QString& name, const ProjectInfo& project);

    int count() const;

private:
    QSharedDataPointer<Internal::ProjectInfoListPrivate> d;
};

QDebug OPENTRADE_EXPORT operator << (QDebug, const ProjectInfoList &projectinfolist);

} // namespace OpenTrade

Q_DECLARE_SHARED(OpenTrade::ProjectInfoList)

#endif // __OPENTRADE_PROJECTINFOLIST_H__
