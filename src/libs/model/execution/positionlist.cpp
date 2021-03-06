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
#include "positionlist.h"

#include <QSharedData>

namespace OpenTrade {

namespace Internal {

class PositionListPrivate : public QSharedData
{
public:
    int m_count;
};

} // namespace Internal

PositionList::~PositionList()
{

}

PositionList& PositionList::operator=(const PositionList &other)
{
    d = other.d;
    return *this;
}

bool PositionList::operator==(const PositionList &other) const
{
    if(d == other.d)
      return true;

    return d->m_count == other.d->m_count;
}

int PositionList::count() const
{
    return d->m_count;
}


} // namespace OpenTrade

QDebug operator<<(QDebug c, const OpenTrade::PositionList &positionlist)
{
    c.nospace() << "PositionList("
                << "Count:" << positionlist.count() 
                <<')';
    return c.space();
}
