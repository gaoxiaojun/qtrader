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

class InstrumentPrivate
{
public:
    QString currency;
    QString description;
    QString exchange;
    double  factory;
    QString group;
    double  margin;
    QDateTime maturity;
    OrderBook orderBook;
    QString priceFormat;
    Instrument::PutCall putCall;
    QString sector;
    double stike;
    QString symbol;
    double tickSize;
    Instrument::InstrumentType type;
};

Instrument::Instrument(const QString& symbol, InstrumentType type)
    : d(new InstrumentPrivate)
{
    d_func()->symbol = symbol;
    d_func()->type = type;
}

Instrument::~Instrument ()
{
    delete d;
}

Instrument::symbol()
{
    return d_func()->symbol;
}

Instrument::instrumentType()
{
    return d_func()->type;
}

Instrument::exchange()
{
    return d_func()->exchange;
}

Instrument::setExchange (const QString &exchange)
{
    d_func()->exchange = exchange;
}

Instrument::currency()
{
    return d_func()->currency;
}

Instrument::setCurrency (const QString &currency)
{
    d_func()->currency = currency;
}

Instrument::description ()
{
    return d_func()->description;
}

Instrument::setDescription (const QString &desc)
{
    d_func()->description = desc;
}

Instrument::group()
{
    return d_func()->group;
}

Instrument::setGroup (const QString &group)
{
    d_func()->group = group;
}

Instrument::sector()
{
    return d_func()->sector;
}

Instrument::setSector (const QString &sector)
{
    d_func()->sector = sector;
}

Instrument::priceFormat()
{
    return d_func()->priceFormat;
}

Instrument::setPriceFormat (const QString format)
{
    d_func()->priceFormat = format;
}

Instrument::factor ()
{
    return d_func()->factory;
}

Instrument::setFactor (double factor)
{
    d_func()->factory = factor;
}

Instrument::margin ()
{
    return d_func()->margin;
}

Instrument::setMargin (double margin)
{
    d_func()->margin = margin;
}

Instrument::tickSize ()
{
    return d_func()->tickSize;
}

Instrument::maturity ()
{
    return d_func()->maturity;
}

Instrument::setMaturity (const QDateTime &date)
{
    d_func()->maturity = date;
}

Instrument::strike ()
{
    return d_func()->stike;
}

Instrument::setStrike (double strike)
{
    d_func()->stike = strike;
}

Instrument::putCall ()
{
    return d_func()->putCall;
}

Instrument::setPutCall (PutCall putCall)
{
    d_func()->putCall = putCall;
}


