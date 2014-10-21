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
#include "projectinfolist.h"

#include <QSharedData>

namespace OpenTrade {

namespace Internal {

class ProjectInfoListPrivate : public QSharedData
{
public:
    int m_count;
};

} // namespace Internal

ProjectInfoList::~ProjectInfoList()
{

}

ProjectInfoList& ProjectInfoList::operator=(const ProjectInfoList &other)
{
    d = other.d;
    return *this;
}

bool ProjectInfoList::operator==(const ProjectInfoList &other) const
{
    if(d == other.d)
      return true;

    return d->m_count == other.d->m_count;
}

bool ProjectInfoList::contains(const QString& name)
{

}

bool ProjectInfoList::tryGetValue(const QString& name, const ProjectInfo& project)
{

}

int ProjectInfoList::count() const
{
    return d->m_count;
}


} // namespace OpenTrade

QDebug operator<<(QDebug c, const OpenTrade::ProjectInfoList &projectinfolist)
{
    c.nospace() << "ProjectInfoList("
                << "Count:" << projectinfolist.count() 
                <<')';
    return c.space();
}
