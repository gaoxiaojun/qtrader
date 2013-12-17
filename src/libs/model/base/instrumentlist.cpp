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
#include "instrumentlist.h"

#include <QSharedData>

namespace OpenTrade {

namespace Internal {

class InstrumentListPrivate : public QSharedData
{
public:
    int m_count;
};

} // namespace Internal

InstrumentList::InstrumentList()
{

}

InstrumentList::~InstrumentList()
{

}

InstrumentList& InstrumentList::operator=(const InstrumentList &other)
{
    d = other.d;
    return *this;
}

bool InstrumentList::operator==(const InstrumentList &other) const
{
    if(d == other.d)
      return true;

    return d->m_count == other.d->m_count;
}

int InstrumentList::count() const
{
    return d->m_count;
}


} // namespace OpenTrade

QDebug operator<<(QDebug c, const OpenTrade::InstrumentList &instrumentlist)
{
    c.nospace() << "InstrumentList("
                << "Count:" << instrumentlist.count() 
                <<')';
    return c.space();
}
