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
#include "brokerpositionfieldlist.h"

#include <QSharedData>

namespace OpenTrade {

namespace Internal {

class BrokerPositionFieldListPrivate : public QSharedData
{
public:
    int m_count;
};

} // namespace Internal

BrokerPositionFieldList::~BrokerPositionFieldList()
{

}

BrokerPositionFieldList& BrokerPositionFieldList::operator=(const BrokerPositionFieldList &other)
{
    d = other.d;
    return *this;
}

bool BrokerPositionFieldList::operator==(const BrokerPositionFieldList &other) const
{
    if(d == other.d)
      return true;

    return d->m_count == other.d->m_count;
}

void BrokerPositionFieldList::copyTo(const Array& array, int index)
{

}

int BrokerPositionFieldList::count() const
{
    return d->m_count;
}


} // namespace OpenTrade

QDebug operator<<(QDebug c, const OpenTrade::BrokerPositionFieldList &brokerpositionfieldlist)
{
    c.nospace() << "BrokerPositionFieldList("
                << "Count:" << brokerpositionfieldlist.count() 
                <<')';
    return c.space();
}
