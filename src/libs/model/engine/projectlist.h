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
#ifndef __OPENTRADE_PROJECTLIST_H__
#define __OPENTRADE_PROJECTLIST_H__

#include "opentrade_global.h"
#include "project.h"

#include <QSharedDataPointer>
#include <QDebug>
#include <QString>


namespace OpenTrade {

namespace Internal {
class ProjectListPrivate;
}

class OPENTRADE_EXPORT ProjectList
{
public:

    ~ProjectList();

    ProjectList& operator=(const ProjectList &other);
    void swap(ProjectList &other) { qSwap(d, other.d); }

#ifdef Q_COMPILER_RVALUE_REFS
    inline ProjectList &operator=(ProjectList &&other)
    { qSwap(d, other.d); return *this; }
#endif

    bool operator==(const ProjectList &other) const;
    inline bool operator!=(const ProjectList &other) const { return !(operator==(other)); }

    bool contains(const QString& name);
    bool tryGetValue(const QString& name, const Project& project);

    int count() const;

private:
    QSharedDataPointer<Internal::ProjectListPrivate> d;
};

QDebug OPENTRADE_EXPORT operator << (QDebug, const ProjectList &projectlist);

} // namespace OpenTrade

Q_DECLARE_SHARED(OpenTrade::ProjectList)

#endif // __OPENTRADE_PROJECTLIST_H__
