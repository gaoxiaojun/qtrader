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
#include "order.h"

#include <QSharedData>

namespace OpenTrade {

namespace Internal {

class OrderPrivate : public QSharedData
{
public:
    QString m_account;
    double m_avgPrice;
    QString m_clientID;
    double m_cumQty;
    QDateTime m_dateTime;
    int m_expireSeconds;
    QDateTime m_expireTime;
    IBEx m_iB;
    Instrument m_instrument;
    bool m_isCancelled;
    bool m_isDone;
    bool m_isExpired;
    bool m_isFilled;
    bool m_isNew;
    bool m_isPartiallyFilled;
    bool m_isPendingCancel;
    bool m_isPendingNew;
    bool m_isPendingReplace;
    bool m_isRejected;
    double m_lastPrice;
    double m_lastQty;
    double m_leavesQty;
    QString m_oCAGroup;
    QString m_orderID;
    double m_price;
    double m_qty;
    int m_route;
    OrderSide m_side;
    OrderStatus m_status;
    double m_stopPrice;
    bool m_strategyFill;
    double m_strategyPrice;
    QString m_text;
    TimeInForce m_timeInForce;
    int m_tradeVolumeDelay;
    double m_trailingAmt;
    OrderType m_type;
};

} // namespace Internal

Order::~Order()
{

}

Order& Order::operator=(const Order &other)
{
    d = other.d;
    return *this;
}

bool Order::operator==(const Order &other) const
{
    if(d == other.d)
      return true;

    return d->m_account == other.d->m_account &&
           d->m_avgPrice == other.d->m_avgPrice &&
           d->m_clientID == other.d->m_clientID &&
           d->m_cumQty == other.d->m_cumQty &&
           d->m_dateTime == other.d->m_dateTime &&
           d->m_expireSeconds == other.d->m_expireSeconds &&
           d->m_expireTime == other.d->m_expireTime &&
           d->m_iB == other.d->m_iB &&
           d->m_instrument == other.d->m_instrument &&
           d->m_isCancelled == other.d->m_isCancelled &&
           d->m_isDone == other.d->m_isDone &&
           d->m_isExpired == other.d->m_isExpired &&
           d->m_isFilled == other.d->m_isFilled &&
           d->m_isNew == other.d->m_isNew &&
           d->m_isPartiallyFilled == other.d->m_isPartiallyFilled &&
           d->m_isPendingCancel == other.d->m_isPendingCancel &&
           d->m_isPendingNew == other.d->m_isPendingNew &&
           d->m_isPendingReplace == other.d->m_isPendingReplace &&
           d->m_isRejected == other.d->m_isRejected &&
           d->m_lastPrice == other.d->m_lastPrice &&
           d->m_lastQty == other.d->m_lastQty &&
           d->m_leavesQty == other.d->m_leavesQty &&
           d->m_oCAGroup == other.d->m_oCAGroup &&
           d->m_orderID == other.d->m_orderID &&
           d->m_price == other.d->m_price &&
           d->m_qty == other.d->m_qty &&
           d->m_route == other.d->m_route &&
           d->m_side == other.d->m_side &&
           d->m_status == other.d->m_status &&
           d->m_stopPrice == other.d->m_stopPrice &&
           d->m_strategyFill == other.d->m_strategyFill &&
           d->m_strategyPrice == other.d->m_strategyPrice &&
           d->m_text == other.d->m_text &&
           d->m_timeInForce == other.d->m_timeInForce &&
           d->m_tradeVolumeDelay == other.d->m_tradeVolumeDelay &&
           d->m_trailingAmt == other.d->m_trailingAmt &&
           d->m_type == other.d->m_type;
}

void Order::cancel()
{

}

void Order::replace()
{

}

void Order::send()
{

}

QString Order::account() const
{
    return d->m_account;
}

void Order::setAccount(const QString& account)
{
    d->m_account = account;
}

double Order::avgPrice() const
{
    return d->m_avgPrice;
}

QString Order::clientID() const
{
    return d->m_clientID;
}

void Order::setClientID(const QString& clientid)
{
    d->m_clientID = clientid;
}

double Order::cumQty() const
{
    return d->m_cumQty;
}

QDateTime Order::dateTime() const
{
    return d->m_dateTime;
}

int Order::expireSeconds() const
{
    return d->m_expireSeconds;
}

void Order::setExpireSeconds(int expireseconds)
{
    d->m_expireSeconds = expireseconds;
}

QDateTime Order::expireTime() const
{
    return d->m_expireTime;
}

void Order::setExpireTime(const QDateTime& expiretime)
{
    d->m_expireTime = expiretime;
}

IBEx Order::iB() const
{
    return d->m_iB;
}

Instrument Order::instrument() const
{
    return d->m_instrument;
}

bool Order::isCancelled() const
{
    return d->m_isCancelled;
}

bool Order::isDone() const
{
    return d->m_isDone;
}

bool Order::isExpired() const
{
    return d->m_isExpired;
}

bool Order::isFilled() const
{
    return d->m_isFilled;
}

bool Order::isNew() const
{
    return d->m_isNew;
}

bool Order::isPartiallyFilled() const
{
    return d->m_isPartiallyFilled;
}

bool Order::isPendingCancel() const
{
    return d->m_isPendingCancel;
}

bool Order::isPendingNew() const
{
    return d->m_isPendingNew;
}

bool Order::isPendingReplace() const
{
    return d->m_isPendingReplace;
}

bool Order::isRejected() const
{
    return d->m_isRejected;
}

double Order::lastPrice() const
{
    return d->m_lastPrice;
}

double Order::lastQty() const
{
    return d->m_lastQty;
}

double Order::leavesQty() const
{
    return d->m_leavesQty;
}

QString Order::oCAGroup() const
{
    return d->m_oCAGroup;
}

void Order::setOCAGroup(const QString& ocagroup)
{
    d->m_oCAGroup = ocagroup;
}

QString Order::orderID() const
{
    return d->m_orderID;
}

void Order::setOrderID(const QString& orderid)
{
    d->m_orderID = orderid;
}

double Order::price() const
{
    return d->m_price;
}

void Order::setPrice(double price)
{
    d->m_price = price;
}

double Order::qty() const
{
    return d->m_qty;
}

void Order::setQty(double qty)
{
    d->m_qty = qty;
}

int Order::route() const
{
    return d->m_route;
}

void Order::setRoute(int route)
{
    d->m_route = route;
}

OrderSide Order::side() const
{
    return d->m_side;
}

OrderStatus Order::status() const
{
    return d->m_status;
}

double Order::stopPrice() const
{
    return d->m_stopPrice;
}

void Order::setStopPrice(double stopprice)
{
    d->m_stopPrice = stopprice;
}

bool Order::strategyFill() const
{
    return d->m_strategyFill;
}

void Order::setStrategyFill(bool strategyfill)
{
    d->m_strategyFill = strategyfill;
}

double Order::strategyPrice() const
{
    return d->m_strategyPrice;
}

void Order::setStrategyPrice(double strategyprice)
{
    d->m_strategyPrice = strategyprice;
}

QString Order::text() const
{
    return d->m_text;
}

void Order::setText(const QString& text)
{
    d->m_text = text;
}

TimeInForce Order::timeInForce() const
{
    return d->m_timeInForce;
}

void Order::setTimeInForce(TimeInForce timeinforce)
{
    d->m_timeInForce = timeinforce;
}

int Order::tradeVolumeDelay() const
{
    return d->m_tradeVolumeDelay;
}

void Order::setTradeVolumeDelay(int tradevolumedelay)
{
    d->m_tradeVolumeDelay = tradevolumedelay;
}

double Order::trailingAmt() const
{
    return d->m_trailingAmt;
}

void Order::setTrailingAmt(double trailingamt)
{
    d->m_trailingAmt = trailingamt;
}

OrderType Order::type() const
{
    return d->m_type;
}

void Order::setType(OrderType type)
{
    d->m_type = type;
}


} // namespace OpenTrade

QDebug operator<<(QDebug c, const OpenTrade::Order &order)
{
    c.nospace() << "Order("
                << "Account:" << order.account() 
                << "AvgPrice:" << order.avgPrice() 
                << "ClientID:" << order.clientID() 
                << "CumQty:" << order.cumQty() 
                << "DateTime:" << order.dateTime() 
                << "ExpireSeconds:" << order.expireSeconds() 
                << "ExpireTime:" << order.expireTime() 
                << "IB:" << order.iB() 
                << "Instrument:" << order.instrument() 
                << "IsCancelled:" << order.isCancelled() 
                << "IsDone:" << order.isDone() 
                << "IsExpired:" << order.isExpired() 
                << "IsFilled:" << order.isFilled() 
                << "IsNew:" << order.isNew() 
                << "IsPartiallyFilled:" << order.isPartiallyFilled() 
                << "IsPendingCancel:" << order.isPendingCancel() 
                << "IsPendingNew:" << order.isPendingNew() 
                << "IsPendingReplace:" << order.isPendingReplace() 
                << "IsRejected:" << order.isRejected() 
                << "LastPrice:" << order.lastPrice() 
                << "LastQty:" << order.lastQty() 
                << "LeavesQty:" << order.leavesQty() 
                << "OCAGroup:" << order.oCAGroup() 
                << "OrderID:" << order.orderID() 
                << "Price:" << order.price() 
                << "Qty:" << order.qty() 
                << "Route:" << order.route() 
                << "Side:" << order.side() 
                << "Status:" << order.status() 
                << "StopPrice:" << order.stopPrice() 
                << "StrategyFill:" << order.strategyFill() 
                << "StrategyPrice:" << order.strategyPrice() 
                << "Text:" << order.text() 
                << "TimeInForce:" << order.timeInForce() 
                << "TradeVolumeDelay:" << order.tradeVolumeDelay() 
                << "TrailingAmt:" << order.trailingAmt() 
                << "Type:" << order.type() 
                <<')';
    return c.space();
}
