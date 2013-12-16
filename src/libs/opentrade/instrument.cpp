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
#include "instrument.h"

#include <QSharedData>

namespace OpenTrade {

namespace Internal {

class InstrumentPrivate : public QSharedData
{
public:
    AltIDGroupList m_altIDGroups;
    Bar m_bar;
    QString m_currency;
    QString m_description;
    QString m_exchange;
    double m_factor;
    QString m_group;
    double m_margin;
    QDateTime m_maturity;
    OrderBook m_orderBook;
    QString m_priceFormat;
    PutCall m_putCall;
    Quote m_quote;
    QString m_sector;
    double m_strike;
    QString m_symbol;
    double m_tickSize;
    Trade m_trade;
    InstrumentType m_type;
};

} // namespace Internal

Instrument::Instrument(InstrumentType type, const QString& symbol)
{

}

Instrument::Instrument(InstrumentType type, const QString& symbol, const QString& secutityExchange, const QString& currency)
{

}

Instrument::~Instrument()
{

}

Instrument& Instrument::operator=(const Instrument &other)
{
    d = other.d;
    return *this;
}

bool Instrument::operator==(const Instrument &other) const
{
    if(d == other.d)
      return true;

    return d->m_altIDGroups == other.d->m_altIDGroups &&
           d->m_bar == other.d->m_bar &&
           d->m_currency == other.d->m_currency &&
           d->m_description == other.d->m_description &&
           d->m_exchange == other.d->m_exchange &&
           d->m_factor == other.d->m_factor &&
           d->m_group == other.d->m_group &&
           d->m_margin == other.d->m_margin &&
           d->m_maturity == other.d->m_maturity &&
           d->m_orderBook == other.d->m_orderBook &&
           d->m_priceFormat == other.d->m_priceFormat &&
           d->m_putCall == other.d->m_putCall &&
           d->m_quote == other.d->m_quote &&
           d->m_sector == other.d->m_sector &&
           d->m_strike == other.d->m_strike &&
           d->m_symbol == other.d->m_symbol &&
           d->m_tickSize == other.d->m_tickSize &&
           d->m_trade == other.d->m_trade &&
           d->m_type == other.d->m_type;
}

QString Instrument::getExchange(const QString& source)
{

}

QString Instrument::getSymbol(const QString& source)
{

}

AltIDGroupList Instrument::altIDGroups() const
{
    return d->m_altIDGroups;
}

void Instrument::setAltIDGroups(const AltIDGroupList& altidgroups)
{
    d->m_altIDGroups = altidgroups;
}

Bar Instrument::bar() const
{
    return d->m_bar;
}

QString Instrument::currency() const
{
    return d->m_currency;
}

void Instrument::setCurrency(const QString& currency)
{
    d->m_currency = currency;
}

QString Instrument::description() const
{
    return d->m_description;
}

void Instrument::setDescription(const QString& description)
{
    d->m_description = description;
}

QString Instrument::exchange() const
{
    return d->m_exchange;
}

void Instrument::setExchange(const QString& exchange)
{
    d->m_exchange = exchange;
}

double Instrument::factor() const
{
    return d->m_factor;
}

void Instrument::setFactor(double factor)
{
    d->m_factor = factor;
}

QString Instrument::group() const
{
    return d->m_group;
}

void Instrument::setGroup(const QString& group)
{
    d->m_group = group;
}

double Instrument::margin() const
{
    return d->m_margin;
}

void Instrument::setMargin(double margin)
{
    d->m_margin = margin;
}

QDateTime Instrument::maturity() const
{
    return d->m_maturity;
}

void Instrument::setMaturity(const QDateTime& maturity)
{
    d->m_maturity = maturity;
}

OrderBook Instrument::orderBook() const
{
    return d->m_orderBook;
}

QString Instrument::priceFormat() const
{
    return d->m_priceFormat;
}

void Instrument::setPriceFormat(const QString& priceformat)
{
    d->m_priceFormat = priceformat;
}

PutCall Instrument::putCall() const
{
    return d->m_putCall;
}

void Instrument::setPutCall(PutCall putcall)
{
    d->m_putCall = putcall;
}

Quote Instrument::quote() const
{
    return d->m_quote;
}

QString Instrument::sector() const
{
    return d->m_sector;
}

void Instrument::setSector(const QString& sector)
{
    d->m_sector = sector;
}

double Instrument::strike() const
{
    return d->m_strike;
}

void Instrument::setStrike(double strike)
{
    d->m_strike = strike;
}

QString Instrument::symbol() const
{
    return d->m_symbol;
}

double Instrument::tickSize() const
{
    return d->m_tickSize;
}

void Instrument::setTickSize(double ticksize)
{
    d->m_tickSize = ticksize;
}

Trade Instrument::trade() const
{
    return d->m_trade;
}

InstrumentType Instrument::type() const
{
    return d->m_type;
}


} // namespace OpenTrade

QDebug operator<<(QDebug c, const OpenTrade::Instrument &instrument)
{
    c.nospace() << "Instrument("
                << "AltIDGroups:" << instrument.altIDGroups() 
                << "Bar:" << instrument.bar() 
                << "Currency:" << instrument.currency() 
                << "Description:" << instrument.description() 
                << "Exchange:" << instrument.exchange() 
                << "Factor:" << instrument.factor() 
                << "Group:" << instrument.group() 
                << "Margin:" << instrument.margin() 
                << "Maturity:" << instrument.maturity() 
                << "OrderBook:" << instrument.orderBook() 
                << "PriceFormat:" << instrument.priceFormat() 
                << "PutCall:" << instrument.putCall() 
                << "Quote:" << instrument.quote() 
                << "Sector:" << instrument.sector() 
                << "Strike:" << instrument.strike() 
                << "Symbol:" << instrument.symbol() 
                << "TickSize:" << instrument.tickSize() 
                << "Trade:" << instrument.trade() 
                << "Type:" << instrument.type() 
                <<')';
    return c.space();
}
