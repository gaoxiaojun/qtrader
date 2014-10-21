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
#include "orderbookupdate.h"

#include <QSharedData>

namespace OpenTrade {

namespace Internal {

class OrderBookUpdatePrivate : public QSharedData
{
public:
    OrderBookAction m_action;
    QDateTime m_dateTime;
    int m_position;
    double m_price;
    BidAsk m_side;
    int m_size;
};

} // namespace Internal

OrderBookUpdate::~OrderBookUpdate()
{

}

OrderBookUpdate& OrderBookUpdate::operator=(const OrderBookUpdate &other)
{
    d = other.d;
    return *this;
}

bool OrderBookUpdate::operator==(const OrderBookUpdate &other) const
{
    if(d == other.d)
      return true;

    return d->m_action == other.d->m_action &&
           d->m_dateTime == other.d->m_dateTime &&
           d->m_position == other.d->m_position &&
           d->m_price == other.d->m_price &&
           d->m_side == other.d->m_side &&
           d->m_size == other.d->m_size;
}

OrderBookAction OrderBookUpdate::action() const
{
    return d->m_action;
}

QDateTime OrderBookUpdate::dateTime() const
{
    return d->m_dateTime;
}

int OrderBookUpdate::position() const
{
    return d->m_position;
}

double OrderBookUpdate::price() const
{
    return d->m_price;
}

BidAsk OrderBookUpdate::side() const
{
    return d->m_side;
}

int OrderBookUpdate::size() const
{
    return d->m_size;
}


} // namespace OpenTrade

QDebug operator<<(QDebug c, const OpenTrade::OrderBookUpdate &orderbookupdate)
{
    c.nospace() << "OrderBookUpdate("
                << "Action:" << orderbookupdate.action() 
                << "DateTime:" << orderbookupdate.dateTime() 
                << "Position:" << orderbookupdate.position() 
                << "Price:" << orderbookupdate.price() 
                << "Side:" << orderbookupdate.side() 
                << "Size:" << orderbookupdate.size() 
                <<')';
    return c.space();
}
