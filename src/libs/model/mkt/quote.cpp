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
#include "quote.h"

#include <QSharedData>

namespace OpenTrade {

namespace Internal {

class QuotePrivate : public QSharedData
{
public:
    double m_ask;
    int m_askSize;
    double m_bid;
    int m_bidSize;
    QDateTime m_dateTime;
    int m_providerId;
};

} // namespace Internal

Quote::Quote(const QDateTime& dateTime, double bid, int bidSize, double ask, int askSize)
{

}

Quote::~Quote()
{

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

    return d->m_ask == other.d->m_ask &&
           d->m_askSize == other.d->m_askSize &&
           d->m_bid == other.d->m_bid &&
           d->m_bidSize == other.d->m_bidSize &&
           d->m_dateTime == other.d->m_dateTime &&
           d->m_providerId == other.d->m_providerId;
}

double Quote::ask() const
{
    return d->m_ask;
}

int Quote::askSize() const
{
    return d->m_askSize;
}

double Quote::bid() const
{
    return d->m_bid;
}

int Quote::bidSize() const
{
    return d->m_bidSize;
}

QDateTime Quote::dateTime() const
{
    return d->m_dateTime;
}

int Quote::providerId() const
{
    return d->m_providerId;
}


} // namespace OpenTrade

QDebug operator<<(QDebug c, const OpenTrade::Quote &quote)
{
    c.nospace() << "Quote("
                << "Ask:" << quote.ask() 
                << "AskSize:" << quote.askSize() 
                << "Bid:" << quote.bid() 
                << "BidSize:" << quote.bidSize() 
                << "DateTime:" << quote.dateTime() 
                << "ProviderId:" << quote.providerId() 
                <<')';
    return c.space();
}
