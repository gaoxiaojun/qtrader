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
#include "orderlist.h"

#include <QSharedData>

namespace OpenTrade {

namespace Internal {

class OrderListPrivate : public QSharedData
{
public:
    int m_count;
};

} // namespace Internal

OrderList::OrderList()
{

}

OrderList::~OrderList()
{

}

OrderList& OrderList::operator=(const OrderList &other)
{
    d = other.d;
    return *this;
}

bool OrderList::operator==(const OrderList &other) const
{
    if(d == other.d)
      return true;

    return d->m_count == other.d->m_count;
}

int OrderList::count() const
{
    return d->m_count;
}


} // namespace OpenTrade

QDebug operator<<(QDebug c, const OpenTrade::OrderList &orderlist)
{
    c.nospace() << "OrderList("
                << "Count:" << orderlist.count() 
                <<')';
    return c.space();
}
