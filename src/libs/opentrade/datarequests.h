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
#ifndef __OPENTRADE_DATAREQUESTS_H__
#define __OPENTRADE_DATAREQUESTS_H__

#include "opentrade_global.h"
#include "barrequest.h"
#include "barrequestlist.h"

#include <QSharedDataPointer>
#include <QDebug>


namespace OpenTrade {

namespace Internal {
class DataRequestsPrivate;
}

class OPENTRADE_EXPORT DataRequests
{
public:

    DataRequests();
    ~DataRequests();

    DataRequests& operator=(const DataRequests &other);
    void swap(DataRequests &other) { qSwap(d, other.d); }

#ifdef Q_COMPILER_RVALUE_REFS
    inline DataRequests &operator=(DataRequests &&other)
    { qSwap(d, other.d); return *this; }
#endif

    bool operator==(const DataRequests &other) const;
    inline bool operator!=(const DataRequests &other) const { return !(operator==(other)); }

    BarRequest add(BarType barType, long barSize, const bool& isBarFacroryRequest);
    void addDaily();
    void addQuote();
    void addTrade();
    void remove(BarType barType, long barSize);
    void removeDaily();
    void removeQuote();
    void removeTrade();

    BarRequestList barRequests() const;

    bool hasBarRequests() const;
    void setHasBarRequests(const bool& hasbarrequests);

    bool hasDailyRequest() const;
    void setHasDailyRequest(const bool& hasdailyrequest);

    bool hasMarketDepthRequest() const;
    void setHasMarketDepthRequest(const bool& hasmarketdepthrequest);

    bool hasQuoteRequest() const;
    void setHasQuoteRequest(const bool& hasquoterequest);

    bool hasTradeRequest() const;
    void setHasTradeRequest(const bool& hastraderequest);

private:
    QSharedDataPointer<Internal::DataRequestsPrivate> d;
};

QDebug OPENTRADE_EXPORT operator << (QDebug, const DataRequests &datarequests);

} // namespace OpenTrade

Q_DECLARE_SHARED(OpenTrade::DataRequests)

#endif // __OPENTRADE_DATAREQUESTS_H__
