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
#include "brokeraccountlist.h"

#include <QSharedData>

namespace OpenTrade {

namespace Internal {

class BrokerAccountListPrivate : public QSharedData
{
public:
    int m_count;
};

} // namespace Internal

BrokerAccountList::~BrokerAccountList()
{

}

BrokerAccountList& BrokerAccountList::operator=(const BrokerAccountList &other)
{
    d = other.d;
    return *this;
}

bool BrokerAccountList::operator==(const BrokerAccountList &other) const
{
    if(d == other.d)
      return true;

    return d->m_count == other.d->m_count;
}

void BrokerAccountList::copyTo(const Array& array, int index)
{

}

int BrokerAccountList::count() const
{
    return d->m_count;
}


} // namespace OpenTrade

QDebug operator<<(QDebug c, const OpenTrade::BrokerAccountList &brokeraccountlist)
{
    c.nospace() << "BrokerAccountList("
                << "Count:" << brokeraccountlist.count() 
                <<')';
    return c.space();
}
