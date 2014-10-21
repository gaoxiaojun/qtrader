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
#include "brokeraccountfieldlist.h"

#include <QSharedData>

namespace OpenTrade {

namespace Internal {

class BrokerAccountFieldListPrivate : public QSharedData
{
public:
    int m_count;
};

} // namespace Internal

BrokerAccountFieldList::~BrokerAccountFieldList()
{

}

BrokerAccountFieldList& BrokerAccountFieldList::operator=(const BrokerAccountFieldList &other)
{
    d = other.d;
    return *this;
}

bool BrokerAccountFieldList::operator==(const BrokerAccountFieldList &other) const
{
    if(d == other.d)
      return true;

    return d->m_count == other.d->m_count;
}

bool BrokerAccountFieldList::contains(const QString& name)
{

}

bool BrokerAccountFieldList::contains(const QString& name, const QString& currency)
{

}

void BrokerAccountFieldList::copyTo(const Array& array, int index)
{

}

BrokerAccountField BrokerAccountFieldList::getAllByName(const QString& name)
{

}

int BrokerAccountFieldList::count() const
{
    return d->m_count;
}


} // namespace OpenTrade

QDebug operator<<(QDebug c, const OpenTrade::BrokerAccountFieldList &brokeraccountfieldlist)
{
    c.nospace() << "BrokerAccountFieldList("
                << "Count:" << brokeraccountfieldlist.count() 
                <<')';
    return c.space();
}
