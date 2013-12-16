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
#include "brokerposition.h"

#include <QSharedData>

namespace OpenTrade {

namespace Internal {

class BrokerPositionPrivate : public QSharedData
{
public:
    QString m_currency;
    QString m_exchange;
    BrokerPositionFieldList m_fields;
    InstrumentType m_instrumentType;
    double m_longQty;
    QDateTime m_maturity;
    PutCall m_putCall;
    double m_qty;
    double m_shortQty;
    double m_strike;
    QString m_symbol;
};

} // namespace Internal

BrokerPosition::~BrokerPosition()
{

}

BrokerPosition& BrokerPosition::operator=(const BrokerPosition &other)
{
    d = other.d;
    return *this;
}

bool BrokerPosition::operator==(const BrokerPosition &other) const
{
    if(d == other.d)
      return true;

    return d->m_currency == other.d->m_currency &&
           d->m_exchange == other.d->m_exchange &&
           d->m_fields == other.d->m_fields &&
           d->m_instrumentType == other.d->m_instrumentType &&
           d->m_longQty == other.d->m_longQty &&
           d->m_maturity == other.d->m_maturity &&
           d->m_putCall == other.d->m_putCall &&
           d->m_qty == other.d->m_qty &&
           d->m_shortQty == other.d->m_shortQty &&
           d->m_strike == other.d->m_strike &&
           d->m_symbol == other.d->m_symbol;
}

void BrokerPosition::addCustomField(const QString& name, const QString& value)
{

}

QString BrokerPosition::currency() const
{
    return d->m_currency;
}

void BrokerPosition::setCurrency(const QString& currency)
{
    d->m_currency = currency;
}

QString BrokerPosition::exchange() const
{
    return d->m_exchange;
}

void BrokerPosition::setExchange(const QString& exchange)
{
    d->m_exchange = exchange;
}

BrokerPositionFieldList BrokerPosition::fields() const
{
    return d->m_fields;
}

InstrumentType BrokerPosition::instrumentType() const
{
    return d->m_instrumentType;
}

void BrokerPosition::setInstrumentType(InstrumentType instrumenttype)
{
    d->m_instrumentType = instrumenttype;
}

double BrokerPosition::longQty() const
{
    return d->m_longQty;
}

void BrokerPosition::setLongQty(double longqty)
{
    d->m_longQty = longqty;
}

QDateTime BrokerPosition::maturity() const
{
    return d->m_maturity;
}

void BrokerPosition::setMaturity(const QDateTime& maturity)
{
    d->m_maturity = maturity;
}

PutCall BrokerPosition::putCall() const
{
    return d->m_putCall;
}

void BrokerPosition::setPutCall(PutCall putcall)
{
    d->m_putCall = putcall;
}

double BrokerPosition::qty() const
{
    return d->m_qty;
}

void BrokerPosition::setQty(double qty)
{
    d->m_qty = qty;
}

double BrokerPosition::shortQty() const
{
    return d->m_shortQty;
}

void BrokerPosition::setShortQty(double shortqty)
{
    d->m_shortQty = shortqty;
}

double BrokerPosition::strike() const
{
    return d->m_strike;
}

void BrokerPosition::setStrike(double strike)
{
    d->m_strike = strike;
}

QString BrokerPosition::symbol() const
{
    return d->m_symbol;
}

void BrokerPosition::setSymbol(const QString& symbol)
{
    d->m_symbol = symbol;
}


} // namespace OpenTrade

QDebug operator<<(QDebug c, const OpenTrade::BrokerPosition &brokerposition)
{
    c.nospace() << "BrokerPosition("
                << "Currency:" << brokerposition.currency() 
                << "Exchange:" << brokerposition.exchange() 
                << "Fields:" << brokerposition.fields() 
                << "InstrumentType:" << brokerposition.instrumentType() 
                << "LongQty:" << brokerposition.longQty() 
                << "Maturity:" << brokerposition.maturity() 
                << "PutCall:" << brokerposition.putCall() 
                << "Qty:" << brokerposition.qty() 
                << "ShortQty:" << brokerposition.shortQty() 
                << "Strike:" << brokerposition.strike() 
                << "Symbol:" << brokerposition.symbol() 
                <<')';
    return c.space();
}
