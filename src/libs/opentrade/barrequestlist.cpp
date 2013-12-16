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
#include "barrequestlist.h"

#include <QSharedData>

namespace OpenTrade {

namespace Internal {

class BarRequestListPrivate : public QSharedData
{
public:
    int m_count;
};

} // namespace Internal

BarRequestList::BarRequestList()
{

}

BarRequestList::~BarRequestList()
{

}

BarRequestList& BarRequestList::operator=(const BarRequestList &other)
{
    d = other.d;
    return *this;
}

bool BarRequestList::operator==(const BarRequestList &other) const
{
    if(d == other.d)
      return true;

    return d->m_count == other.d->m_count;
}

void BarRequestList::add(const BarRequest& barRequest)
{

}

BarRequest BarRequestList::add(BarType barType, long barSize, const bool& isBarFacroryRequest)
{

}

bool BarRequestList::contains(const BarRequest& barRequest)
{

}

bool BarRequestList::contains(BarType barType, long barSize)
{

}

bool BarRequestList::contains(BarType barType, long barSize, const bool& isBuiltFromTrades)
{

}

void BarRequestList::remove(const BarRequest& barRequest)
{

}

void BarRequestList::remove(BarType barType, long barSize)
{

}

int BarRequestList::count() const
{
    return d->m_count;
}


} // namespace OpenTrade

QDebug operator<<(QDebug c, const OpenTrade::BarRequestList &barrequestlist)
{
    c.nospace() << "BarRequestList("
                << "Count:" << barrequestlist.count() 
                <<')';
    return c.space();
}
