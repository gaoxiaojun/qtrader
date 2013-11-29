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

#include "order.h"
#include "instrument.h"

namespace OpenTrade {

namespace Internal {

class OrderPrivate
{
public:
    OrderPrivate(const Instrument& inst) : m_instrument(inst) {}
    ~OrderPrivate() {}

    Instrument m_instrument;
    Order::OrderType m_type;
    Order::OrderSide m_side;
    unsigned int m_route;
    QString m_text;
    Order::TimeInForce m_tif;

    QString m_OCA;
    double m_price;
    double m_qty;
    double m_stopPrice;
    double m_tailingAmt;

    QString m_account;
    Order::OrderStatus m_status;


    QDateTime m_create;

    QString m_clientId;
    QString m_orderId;

    double m_avgPrice;
    double m_lastPrice;
    double m_lastQty;
    double m_leavesQty;
    double m_cumQty;

    unsigned int m_expireSeconds;
    QDateTime m_expireTime;
    bool m_strategyFill;
    double m_strategyPrice;
};

} // namespace Internal

Order::Order(const Instrument& inst, QObject *parent) :
    QObject(parent)
{
    d = new Internal::OrderPrivate(inst);
}

Order::~Order()
{
    delete d;
    d = 0;
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

QString Order::account()
{
    return d->m_account;
}

void Order::setAccount(const QString& acct)
{
    d->m_account = acct;
}

QString Order::clientId()
{
    return d->m_clientId;
}

void Order::setClientId(const QString& id)
{
    d->m_clientId = id;
}

double Order::avgPrice()
{
    return d->m_avgPrice;
}

double Order::cumQty()
{
    return d->m_cumQty;
}

QDateTime Order::createTime()
{
    return d->m_create;
}

unsigned int Order::expireSeconds()
{
    return d->m_expireSeconds;
}

QDateTime Order::expireTime()
{
    return d->m_expireTime;
}

void Order::setExpireTime(const QDateTime& dt)
{
    d->m_expireTime = dt;
}

Instrument Order::instrument()
{
    return d->m_instrument;
}

double Order::lastPrice()
{
    return d->m_lastPrice;
}

double Order::lastQty()
{
    return d->m_lastQty;
}

double Order::leavesQty()
{
    return d->m_leavesQty;
}

QString Order::ocaGroup()
{
    return d->m_OCA;
}

void Order::setOCAGroup(const QString& oca)
{
    d->m_OCA = oca;
}

double Order::price()
{
    return d->m_price;
}

void Order::setPrice(double price)
{
    d->m_price = price;
}

double Order::qty()
{
    return d->m_qty;
}

void Order::setQty(double qty)
{
    d->m_qty = qty;
}

Order::OrderSide Order::side()
{
    return d->m_side;
}

void Order::setSide(Order::OrderSide side)
{
    d->m_side = side;
}

Order::OrderStatus Order::status()
{
    return d->m_status;
}

void Order::setStatus(Order::OrderStatus status)
{
    d->m_status = status;
}

double Order::stopPrice()
{
    return d->m_stopPrice;
}

void Order::setStopPrice(double price)
{
    d->m_stopPrice = price;
}

bool Order::strategyFill()
{
    return d->m_strategyFill;
}

double Order::strategyPrice()
{
    return d->m_strategyPrice;
}

QString Order::text()
{
    return d->m_text;
}

void Order::setText(const QString& text)
{
    d->m_text = text;
}

Order::TimeInForce Order::tif()
{
    return d->m_tif;
}

void Order::setTIF(Order::TimeInForce tif)
{
    d->m_tif = tif;
}

double Order::trailingAmt()
{
    return d->m_tailingAmt;
}

void Order::setTrailingAmt(double amt)
{
    d->m_tailingAmt = amt;
}

Order::OrderType Order::type()
{
    return d->m_type;
}

void Order::setOrderType(Order::OrderType type)
{
    d->m_type = type;
}

unsigned int Order::route()
{
    return d->m_route;
}

void Order::setRoute(unsigned int route)
{
    d->m_route = route;
}

bool Order::isCancelled()
{
    return d->m_status == Order::Cancelled;
}

bool Order::isDone()
{
    return ((d->m_status == Order::Filled) ||
            (d->m_status == Order::Rejected) ||
            (d->m_status == Order::Cancelled)
            );
}

bool Order::isExPired()
{
    return d->m_status == Order::Expired;
}

bool Order::isFilled()
{
    return d->m_status == Order::Filled;
}

bool Order::isNew()
{
    return d->m_status == Order::New;
}

bool Order::isPartiallyFilled()
{
    return d->m_status == Order::PartiallyFilled;
}

bool Order::isPendingCancel()
{
    return d->m_status == Order::PendingCancel;
}

bool Order::isPendingNew()
{
    return d->m_status == Order::PendingNew;
}

bool Order::isPendingReplace()
{
    return d->m_status == Order::PendingReplace;
}

bool Order::isRejected()
{
    return d->m_status == Order::Rejected;
}

} // namespace OpenTrade
