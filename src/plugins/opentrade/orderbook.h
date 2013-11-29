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

#ifndef ORDERBOOK_H
#define ORDERBOOK_H

#include "opentrade_global.h"

#include <QSharedDataPointer>
#include <QMetaType>
#include <QDebug>

namespace OpenTrade {

namespace Internal {
  class OrderBookPrivate;
}

class OPENTRADE_EXPORT OrderBook
{
public:
    enum OrderBookAction{
        Insert = 0,
        Update = 1,
        Delete = 2,
        Reset  = 3,
        Undefined = 4
    };

    OrderBook();
    OrderBook(const OrderBook& other);
    ~OrderBook();

    OrderBook& operator=(const OrderBook& other);
    void swap(OrderBook& other) { qSwap(d, other.d); }

#ifdef Q_COMPILER_RVALUE_REFS
    inline OrderBook &operator=(OrderBook &&other)
    { qSwap(d, other.d); return *this; }
#endif
    bool operator==(const OrderBook &other) const;
    inline bool operator!=(const OrderBook &other) const { return !(operator==(other)); }

private:
    QSharedDataPointer<Internal::OrderBookPrivate> d;
    friend class Internal::OrderBookPrivate;
};
QDebug OPENTRADE_EXPORT operator<<(QDebug, const OrderBook &ob);
//Q_DECLARE_METATYPE(OrderBook)

} // namespace OpenTrade

Q_DECLARE_SHARED(OpenTrade::OrderBook)

#endif // ORDERBOOK_H
