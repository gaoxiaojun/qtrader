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
#ifndef __OPENTRADE_ORDERBOOK_H__
#define __OPENTRADE_ORDERBOOK_H__

#include "opentrade_global.h"
#include "quote.h"

#include <QSharedDataPointer>
#include <QDebug>


namespace OpenTrade {

namespace Internal {
class OrderBookPrivate;
}

class OPENTRADE_EXPORT OrderBook
{
public:

    ~OrderBook();

    OrderBook& operator=(const OrderBook &other);
    void swap(OrderBook &other) { qSwap(d, other.d); }

#ifdef Q_COMPILER_RVALUE_REFS
    inline OrderBook &operator=(OrderBook &&other)
    { qSwap(d, other.d); return *this; }
#endif

    bool operator==(const OrderBook &other) const;
    inline bool operator!=(const OrderBook &other) const { return !(operator==(other)); }

    int getAskVolume();
    ouble getAvgAskPrice();
    double getAvgBidPrice();
    int getBidVolume();
    Quote getQuote(int level);

    int count() const;

private:
    QSharedDataPointer<Internal::OrderBookPrivate> d;
};

QDebug OPENTRADE_EXPORT operator << (QDebug, const OrderBook &orderbook);

} // namespace OpenTrade

Q_DECLARE_SHARED(OpenTrade::OrderBook)

#endif // __OPENTRADE_ORDERBOOK_H__
