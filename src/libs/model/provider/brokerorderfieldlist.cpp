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
#include "brokerorderfieldlist.h"

#include <QSharedData>

namespace OpenTrade {

namespace Internal {

class BrokerOrderFieldListPrivate : public QSharedData
{
public:
    int m_count;
};

} // namespace Internal

BrokerOrderFieldList::~BrokerOrderFieldList()
{

}

BrokerOrderFieldList& BrokerOrderFieldList::operator=(const BrokerOrderFieldList &other)
{
    d = other.d;
    return *this;
}

bool BrokerOrderFieldList::operator==(const BrokerOrderFieldList &other) const
{
    if(d == other.d)
      return true;

    return d->m_count == other.d->m_count;
}

void BrokerOrderFieldList::copyTo(const Array& array, int index)
{

}

int BrokerOrderFieldList::count() const
{
    return d->m_count;
}


} // namespace OpenTrade

QDebug operator<<(QDebug c, const OpenTrade::BrokerOrderFieldList &brokerorderfieldlist)
{
    c.nospace() << "BrokerOrderFieldList("
                << "Count:" << brokerorderfieldlist.count() 
                <<')';
    return c.space();
}
