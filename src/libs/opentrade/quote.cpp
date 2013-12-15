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

#include "quote.h"

#include <QSharedData>

namespace OpenTrade {

namespace Internal {

class QuotePrivate: public QSharedData
{
public:
    inline QuotePrivate(const QDateTime& dt, double bid, double bidSize, double ask, double askSize) :
        m_stamp(dt), m_ask(ask), m_askSize(askSize), m_bid(bid), m_bidSize(bidSize)
    {}

    QDateTime m_stamp;
    double m_ask;
    double m_askSize;
    double m_bid;
    double m_bidSize;
};

} // namespace Internal

Quote::Quote(const QDateTime& dt, double bid, double bidSize, double ask, double askSize) :
    d(new Internal::QuotePrivate(dt, bid, bidSize, ask, askSize))
{
}

Quote::Quote(const Quote &other) :
    d(other.d)
{
}

Quote::~Quote()
{
    d = 0;
}

Quote& Quote::operator=(const Quote &other)
{
    d = other.d;
    return *this;
}

bool Quote::operator==(const Quote &other) const
{
    if(d == other.d)
        return true;
    return d->m_stamp == other.d->m_stamp &&
            d->m_ask == other.d->m_ask &&
            d->m_askSize == other.d->m_askSize &&
            d->m_bid == other.d->m_bid &&
            d->m_bidSize == other.d->m_bidSize;
}

double Quote::ask() const
{
    return d->m_ask;
}

double Quote::askSize() const
{
    return d->m_askSize;
}

double Quote::bid() const
{
    return d->m_bid;
}

double Quote::bidSize() const
{
    return d->m_bidSize;
}

QDateTime Quote::datetime() const
{
    return d->m_stamp;
}

} // namespace OpenTrade

QDebug operator<<(QDebug c, const OpenTrade::Quote &quote)
{
    c.nospace() << "Quote("
                << "Time:" << quote.datetime()
                << "Ask:" << quote.ask()
                << "AskSize:" << quote.askSize()
                << "Bid:" << quote.bid()
                << "BidSize" << quote.bidSize()
                <<')';
    return c.space();
}
