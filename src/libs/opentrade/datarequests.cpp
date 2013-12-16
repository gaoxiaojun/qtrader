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
#include "datarequests.h"

#include <QSharedData>

namespace OpenTrade {

namespace Internal {

class DataRequestsPrivate : public QSharedData
{
public:
    BarRequestList m_barRequests;
    bool m_hasBarRequests;
    bool m_hasDailyRequest;
    bool m_hasMarketDepthRequest;
    bool m_hasQuoteRequest;
    bool m_hasTradeRequest;
};

} // namespace Internal

DataRequests::DataRequests()
{

}

DataRequests::~DataRequests()
{

}

DataRequests& DataRequests::operator=(const DataRequests &other)
{
    d = other.d;
    return *this;
}

bool DataRequests::operator==(const DataRequests &other) const
{
    if(d == other.d)
      return true;

    return d->m_barRequests == other.d->m_barRequests &&
           d->m_hasBarRequests == other.d->m_hasBarRequests &&
           d->m_hasDailyRequest == other.d->m_hasDailyRequest &&
           d->m_hasMarketDepthRequest == other.d->m_hasMarketDepthRequest &&
           d->m_hasQuoteRequest == other.d->m_hasQuoteRequest &&
           d->m_hasTradeRequest == other.d->m_hasTradeRequest;
}

BarRequest DataRequests::add(BarType barType, long barSize, const bool& isBarFacroryRequest)
{

}

void DataRequests::addDaily()
{

}

void DataRequests::addQuote()
{

}

void DataRequests::addTrade()
{

}

void DataRequests::remove(BarType barType, long barSize)
{

}

void DataRequests::removeDaily()
{

}

void DataRequests::removeQuote()
{

}

void DataRequests::removeTrade()
{

}

BarRequestList DataRequests::barRequests() const
{
    return d->m_barRequests;
}

bool DataRequests::hasBarRequests() const
{
    return d->m_hasBarRequests;
}

void DataRequests::setHasBarRequests(const bool& hasbarrequests)
{
    d->m_hasBarRequests = hasbarrequests;
}

bool DataRequests::hasDailyRequest() const
{
    return d->m_hasDailyRequest;
}

void DataRequests::setHasDailyRequest(const bool& hasdailyrequest)
{
    d->m_hasDailyRequest = hasdailyrequest;
}

bool DataRequests::hasMarketDepthRequest() const
{
    return d->m_hasMarketDepthRequest;
}

void DataRequests::setHasMarketDepthRequest(const bool& hasmarketdepthrequest)
{
    d->m_hasMarketDepthRequest = hasmarketdepthrequest;
}

bool DataRequests::hasQuoteRequest() const
{
    return d->m_hasQuoteRequest;
}

void DataRequests::setHasQuoteRequest(const bool& hasquoterequest)
{
    d->m_hasQuoteRequest = hasquoterequest;
}

bool DataRequests::hasTradeRequest() const
{
    return d->m_hasTradeRequest;
}

void DataRequests::setHasTradeRequest(const bool& hastraderequest)
{
    d->m_hasTradeRequest = hastraderequest;
}


} // namespace OpenTrade

QDebug operator<<(QDebug c, const OpenTrade::DataRequests &datarequests)
{
    c.nospace() << "DataRequests("
                << "BarRequests:" << datarequests.barRequests() 
                << "HasBarRequests:" << datarequests.hasBarRequests() 
                << "HasDailyRequest:" << datarequests.hasDailyRequest() 
                << "HasMarketDepthRequest:" << datarequests.hasMarketDepthRequest() 
                << "HasQuoteRequest:" << datarequests.hasQuoteRequest() 
                << "HasTradeRequest:" << datarequests.hasTradeRequest() 
                <<')';
    return c.space();
}
