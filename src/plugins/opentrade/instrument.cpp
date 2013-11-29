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

#include "instrument.h"
#include "bar.h"
#include "orderbook.h"

#include <QSharedData>

namespace OpenTrade {

namespace Internal {

class InstrumentPrivate : public QSharedData
{
public:
    InstrumentPrivate(const QString& symbol, Instrument::InstrumentType type) :
        m_symbol(symbol), m_type(type), m_currency(QString("USD")),
        m_description(QString()), m_exchange(QString("SMART")),
        m_factory(1.0), m_group(QString("Unknow")),
        m_margin(0), m_maturity(QDateTime()), m_orderBook(OrderBook()),
        m_priceFormat(QString(".5f")), m_putCall(Instrument::Put),
        m_sector(QString()), m_stike(0), m_tickSize(0)
    {}

    QString m_symbol;
    Instrument::InstrumentType m_type;

    QString m_currency;
    QString m_description;
    QString m_exchange;
    double  m_factory;
    QString m_group;
    double  m_margin;
    QDateTime m_maturity;
    OrderBook m_orderBook;
    QString m_priceFormat;
    Instrument::PutCall m_putCall;
    QString m_sector;
    double m_stike;
    double m_tickSize;
};

} // namespace Internal

Instrument::Instrument(const QString& symbol, InstrumentType type)
    : d(new Internal::InstrumentPrivate(symbol, type))
{
}

Instrument::Instrument(const Instrument &other)
    :d(other.d)
{
}

Instrument::~Instrument ()
{
    d = 0;
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
    return d->m_symbol == other.d->m_symbol &&
            d->m_type == other.d->m_type;
}

QString Instrument::symbol() const
{
    return d->m_symbol;
}

Instrument::InstrumentType Instrument::type() const
{
    return d->m_type;
}

QString Instrument::exchange() const
{
    return d->m_exchange;
}

void Instrument::setExchange (const QString &exchange)
{
    d->m_exchange = exchange;
}

QString Instrument::currency() const
{
    return d->m_currency;
}

void Instrument::setCurrency (const QString &currency)
{
    d->m_currency = currency;
}

QString Instrument::description () const
{
    return d->m_description;
}

void Instrument::setDescription (const QString &desc)
{
    d->m_description = desc;
}

QString Instrument::group() const
{
    return d->m_group;
}

void Instrument::setGroup (const QString &group)
{
    d->m_group = group;
}

QString Instrument::sector() const
{
    return d->m_sector;
}

void Instrument::setSector (const QString &sector)
{
    d->m_sector = sector;
}

QString Instrument::priceFormat() const
{
    return d->m_priceFormat;
}

void Instrument::setPriceFormat (const QString format)
{
    d->m_priceFormat = format;
}

double Instrument::factor () const
{
    return d->m_factory;
}

void Instrument::setFactor (double factor)
{
    d->m_factory = factor;
}

double Instrument::margin () const
{
    return d->m_margin;
}

void Instrument::setMargin (double margin)
{
    d->m_margin = margin;
}

double Instrument::tickSize () const
{
    return d->m_tickSize;
}

QDateTime Instrument::maturity () const
{
    return d->m_maturity;
}

void Instrument::setMaturity (const QDateTime &date)
{
    d->m_maturity = date;
}

double Instrument::strike () const
{
    return d->m_stike;
}

void Instrument::setStrike (double strike)
{
    d->m_stike = strike;
}

Instrument::PutCall Instrument::putCall () const
{
    return d->m_putCall;
}

void Instrument::setPutCall (PutCall putCall)
{
    d->m_putCall = putCall;
}

OrderBook Instrument::orderBook ()
{
    return d->m_orderBook;
}

/* TODO
Bar Instrument::bar()
{

}

Quote Instrument::quote()
{

}*/

} // namespace OpenTrade

QDebug operator<<(QDebug s, const OpenTrade::Instrument &ins)
{
    s.nospace() << "Instrument("
                   <<')';
    return s.space();
}



