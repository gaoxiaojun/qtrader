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
#include "orderbook.h"

#include <QSharedData>

namespace OpenTrade {

namespace Internal {

class OrderBookPrivate : public QSharedData
{
public:
    int m_count;
};

} // namespace Internal

OrderBook::~OrderBook()
{

}

OrderBook& OrderBook::operator=(const OrderBook &other)
{
    d = other.d;
    return *this;
}

bool OrderBook::operator==(const OrderBook &other) const
{
    if(d == other.d)
      return true;

    return d->m_count == other.d->m_count;
}

int OrderBook::getAskVolume()
{

}

ouble OrderBook::getAvgAskPrice()
{

}

double OrderBook::getAvgBidPrice()
{

}

int OrderBook::getBidVolume()
{

}

Quote OrderBook::getQuote(int level)
{

}

int OrderBook::count() const
{
    return d->m_count;
}


} // namespace OpenTrade

QDebug operator<<(QDebug c, const OpenTrade::OrderBook &orderbook)
{
    c.nospace() << "OrderBook("
                << "Count:" << orderbook.count() 
                <<')';
    return c.space();
}
