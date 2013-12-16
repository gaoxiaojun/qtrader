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
#include "brokerorder.h"

#include <QSharedData>

namespace OpenTrade {

namespace Internal {

class BrokerOrderPrivate : public QSharedData
{
public:
    QString m_currency;
    QString m_exchange;
    BrokerOrderFieldList m_fields;
    InstrumentType m_instrumentType;
    QString m_orderID;
    double m_price;
    double m_qty;
    OrderSide m_side;
    OrderStatus m_status;
    double m_stopPrice;
    QString m_symbol;
    OrderType m_type;
};

} // namespace Internal

BrokerOrder::~BrokerOrder()
{

}

BrokerOrder& BrokerOrder::operator=(const BrokerOrder &other)
{
    d = other.d;
    return *this;
}

bool BrokerOrder::operator==(const BrokerOrder &other) const
{
    if(d == other.d)
      return true;

    return d->m_currency == other.d->m_currency &&
           d->m_exchange == other.d->m_exchange &&
           d->m_fields == other.d->m_fields &&
           d->m_instrumentType == other.d->m_instrumentType &&
           d->m_orderID == other.d->m_orderID &&
           d->m_price == other.d->m_price &&
           d->m_qty == other.d->m_qty &&
           d->m_side == other.d->m_side &&
           d->m_status == other.d->m_status &&
           d->m_stopPrice == other.d->m_stopPrice &&
           d->m_symbol == other.d->m_symbol &&
           d->m_type == other.d->m_type;
}

void BrokerOrder::addCustomField(const QString& name, const QString& value)
{

}

QString BrokerOrder::currency() const
{
    return d->m_currency;
}

void BrokerOrder::setCurrency(const QString& currency)
{
    d->m_currency = currency;
}

QString BrokerOrder::exchange() const
{
    return d->m_exchange;
}

void BrokerOrder::setExchange(const QString& exchange)
{
    d->m_exchange = exchange;
}

BrokerOrderFieldList BrokerOrder::fields() const
{
    return d->m_fields;
}

InstrumentType BrokerOrder::instrumentType() const
{
    return d->m_instrumentType;
}

void BrokerOrder::setInstrumentType(InstrumentType instrumenttype)
{
    d->m_instrumentType = instrumenttype;
}

QString BrokerOrder::orderID() const
{
    return d->m_orderID;
}

void BrokerOrder::setOrderID(const QString& orderid)
{
    d->m_orderID = orderid;
}

double BrokerOrder::price() const
{
    return d->m_price;
}

void BrokerOrder::setPrice(double price)
{
    d->m_price = price;
}

double BrokerOrder::qty() const
{
    return d->m_qty;
}

void BrokerOrder::setQty(double qty)
{
    d->m_qty = qty;
}

OrderSide BrokerOrder::side() const
{
    return d->m_side;
}

void BrokerOrder::setSide(OrderSide side)
{
    d->m_side = side;
}

OrderStatus BrokerOrder::status() const
{
    return d->m_status;
}

void BrokerOrder::setStatus(OrderStatus status)
{
    d->m_status = status;
}

double BrokerOrder::stopPrice() const
{
    return d->m_stopPrice;
}

void BrokerOrder::setStopPrice(double stopprice)
{
    d->m_stopPrice = stopprice;
}

QString BrokerOrder::symbol() const
{
    return d->m_symbol;
}

void BrokerOrder::setSymbol(const QString& symbol)
{
    d->m_symbol = symbol;
}

OrderType BrokerOrder::type() const
{
    return d->m_type;
}

void BrokerOrder::setType(OrderType type)
{
    d->m_type = type;
}


} // namespace OpenTrade

QDebug operator<<(QDebug c, const OpenTrade::BrokerOrder &brokerorder)
{
    c.nospace() << "BrokerOrder("
                << "Currency:" << brokerorder.currency() 
                << "Exchange:" << brokerorder.exchange() 
                << "Fields:" << brokerorder.fields() 
                << "InstrumentType:" << brokerorder.instrumentType() 
                << "OrderID:" << brokerorder.orderID() 
                << "Price:" << brokerorder.price() 
                << "Qty:" << brokerorder.qty() 
                << "Side:" << brokerorder.side() 
                << "Status:" << brokerorder.status() 
                << "StopPrice:" << brokerorder.stopPrice() 
                << "Symbol:" << brokerorder.symbol() 
                << "Type:" << brokerorder.type() 
                <<')';
    return c.space();
}
