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
#ifndef __OPENTRADE_ORDER_H__
#define __OPENTRADE_ORDER_H__

#include "opentrade_global.h"
#include "ibex.h"
#include "instrument.h"

#include <QSharedDataPointer>
#include <QDebug>
#include <QString>
#include <QDateTime>


namespace OpenTrade {

namespace Internal {
class OrderPrivate;
}

class OPENTRADE_EXPORT Order
{
public:

    ~Order();

    Order& operator=(const Order &other);
    void swap(Order &other) { qSwap(d, other.d); }

#ifdef Q_COMPILER_RVALUE_REFS
    inline Order &operator=(Order &&other)
    { qSwap(d, other.d); return *this; }
#endif

    bool operator==(const Order &other) const;
    inline bool operator!=(const Order &other) const { return !(operator==(other)); }

    void cancel();
    void replace();
    void send();

    QString account() const;
    void setAccount(const QString& account);

    double avgPrice() const;

    QString clientID() const;
    void setClientID(const QString& clientid);

    double cumQty() const;

    QDateTime dateTime() const;

    int expireSeconds() const;
    void setExpireSeconds(int expireseconds);

    QDateTime expireTime() const;
    void setExpireTime(const QDateTime& expiretime);

    IBEx iB() const;

    Instrument instrument() const;

    bool isCancelled() const;

    bool isDone() const;

    bool isExpired() const;

    bool isFilled() const;

    bool isNew() const;

    bool isPartiallyFilled() const;

    bool isPendingCancel() const;

    bool isPendingNew() const;

    bool isPendingReplace() const;

    bool isRejected() const;

    double lastPrice() const;

    double lastQty() const;

    double leavesQty() const;

    QString oCAGroup() const;
    void setOCAGroup(const QString& ocagroup);

    QString orderID() const;
    void setOrderID(const QString& orderid);

    double price() const;
    void setPrice(double price);

    double qty() const;
    void setQty(double qty);

    int route() const;
    void setRoute(int route);

    OrderSide side() const;

    OrderStatus status() const;

    double stopPrice() const;
    void setStopPrice(double stopprice);

    bool strategyFill() const;
    void setStrategyFill(bool strategyfill);

    double strategyPrice() const;
    void setStrategyPrice(double strategyprice);

    QString text() const;
    void setText(const QString& text);

    TimeInForce timeInForce() const;
    void setTimeInForce(TimeInForce timeinforce);

    int tradeVolumeDelay() const;
    void setTradeVolumeDelay(int tradevolumedelay);

    double trailingAmt() const;
    void setTrailingAmt(double trailingamt);

    OrderType type() const;
    void setType(OrderType type);

private:
    QSharedDataPointer<Internal::OrderPrivate> d;
};

QDebug OPENTRADE_EXPORT operator << (QDebug, const Order &order);

} // namespace OpenTrade

Q_DECLARE_SHARED(OpenTrade::Order)

#endif // __OPENTRADE_ORDER_H__
