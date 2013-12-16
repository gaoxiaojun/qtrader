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
#include "projectlist.h"

#include <QSharedData>

namespace OpenTrade {

namespace Internal {

class ProjectListPrivate : public QSharedData
{
public:
    int m_count;
};

} // namespace Internal

ProjectList::~ProjectList()
{

}

ProjectList& ProjectList::operator=(const ProjectList &other)
{
    d = other.d;
    return *this;
}

bool ProjectList::operator==(const ProjectList &other) const
{
    if(d == other.d)
      return true;

    return d->m_count == other.d->m_count;
}

bool ProjectList::contains(const QString& name)
{

}

bool ProjectList::tryGetValue(const QString& name, const Project& project)
{

}

int ProjectList::count() const
{
    return d->m_count;
}


} // namespace OpenTrade

QDebug operator<<(QDebug c, const OpenTrade::ProjectList &projectlist)
{
    c.nospace() << "ProjectList("
                << "Count:" << projectlist.count() 
                <<')';
    return c.space();
}
