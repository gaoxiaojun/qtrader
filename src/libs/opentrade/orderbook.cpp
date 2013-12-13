/****************************************************************************
**
** Copyright (C) 2013 Xiaojun Gao
** Contact: http://www.dailypips.org/legal
**
** This file is part of QTrader.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Digia gives you certain additional
** rights.  These rights are described in the Digia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
****************************************************************************/

#include "orderbook.h"

namespace OpenTrade {

namespace Internal {

class OrderBookPrivate : public QSharedData
{
public:
};

} // namespace Internal


OrderBook::OrderBook():
    d(new Internal::OrderBookPrivate)
{
}

OrderBook::OrderBook(const OrderBook &other) :
    d(other.d)
{
}

OrderBook::~OrderBook()
{
    d = 0;
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
    return true;
}

} // namespace OpenTrade

QDebug operator<<(QDebug s, const OpenTrade::OrderBook &ob)
{
    s.nospace() << "OrderBook("
                <<')';
    return s.space();
}


