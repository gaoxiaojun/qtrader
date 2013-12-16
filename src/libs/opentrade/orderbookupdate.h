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
#ifndef __OPENTRADE_ORDERBOOKUPDATE_H__
#define __OPENTRADE_ORDERBOOKUPDATE_H__

#include "opentrade_global.h"

#include <QSharedDataPointer>
#include <QDebug>
#include <QDateTime>


namespace OpenTrade {

namespace Internal {
class OrderBookUpdatePrivate;
}

class OPENTRADE_EXPORT OrderBookUpdate
{
public:

    ~OrderBookUpdate();

    OrderBookUpdate& operator=(const OrderBookUpdate &other);
    void swap(OrderBookUpdate &other) { qSwap(d, other.d); }

#ifdef Q_COMPILER_RVALUE_REFS
    inline OrderBookUpdate &operator=(OrderBookUpdate &&other)
    { qSwap(d, other.d); return *this; }
#endif

    bool operator==(const OrderBookUpdate &other) const;
    inline bool operator!=(const OrderBookUpdate &other) const { return !(operator==(other)); }


    OrderBookAction action() const;

    QDateTime dateTime() const;

    int position() const;

    double price() const;

    BidAsk side() const;

    int size() const;

private:
    QSharedDataPointer<Internal::OrderBookUpdatePrivate> d;
};

QDebug OPENTRADE_EXPORT operator << (QDebug, const OrderBookUpdate &orderbookupdate);

} // namespace OpenTrade

Q_DECLARE_SHARED(OpenTrade::OrderBookUpdate)

#endif // __OPENTRADE_ORDERBOOKUPDATE_H__
