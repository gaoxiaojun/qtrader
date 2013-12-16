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
#ifndef __OPENTRADE_DATAMANAGER_H__
#define __OPENTRADE_DATAMANAGER_H__

#include "opentrade_global.h"
#include "instrument.h"
#include "bar.h"
#include "orderbookupdate.h"
#include "quote.h"
#include "trade.h"
#include "barseries.h"
#include "tradeseries.h"
#include "quoteseries.h"
#include "barseriesinfo.h"
#include "brokerinfo.h"

#include <QSharedDataPointer>
#include <QDebug>
#include <QDateTime>
#include <QuoteData>
#include <QString>


namespace OpenTrade {

namespace Internal {
class DataManagerPrivate;
}

class OPENTRADE_EXPORT DataManager
{
public:

    DataManager();
    ~DataManager();

    DataManager& operator=(const DataManager &other);
    void swap(DataManager &other) { qSwap(d, other.d); }

#ifdef Q_COMPILER_RVALUE_REFS
    inline DataManager &operator=(DataManager &&other)
    { qSwap(d, other.d); return *this; }
#endif

    bool operator==(const DataManager &other) const;
    inline bool operator!=(const DataManager &other) const { return !(operator==(other)); }

    void add(const Instrument& instrument, const Bar& bar);
    void add(const Instrument& instrument, const OrderBookUpdate& update);
    void add(const Instrument& instrument, const Quote& quote);
    void add(const Instrument& instrument, const Trade& trade);
    void add(const Instrument& instrument, const QDateTime& datetime, double price, int size);
    void add(const Instrument& instrument, const QDateTime& datetime, double bid, int bidsize, double ask, int asksize);
    void add(const Instrument& instrument, const QDateTime& datetime, BidAsk side, OrderBookAction action, int position, double price, int size);
    void add(const Instrument& instrument, const QDateTime& datetime, double open, double high, double low, double close, long volume, long size);
    BarSeries compressBars(const BarSeries& bars, long barSize);
    BarSeries compressBars(const TradeSeries& trades, BarType barType, long barSize);
    BarSeries compressBars(const QuoteSeries& quotes, QuoteData input, BarType barType, long barSize);
    void deleteBar(const Instrument& instrument, const QDateTime& datetime, BarType barType, long barSize);
    void deleteBarSeries(const Instrument& instrument, BarType barType, long barSize);
    void deleteDaily(const Instrument& instrument, const QDateTime& date);
    void deleteDailySeries(const Instrument& instrument);
    void deleteQuote(const Instrument& instrument, const QDateTime& datetime);
    void deleteQuoteSeries(const Instrument& instrument);
    void deleteTrade(const Instrument& instrument, const QDateTime& datetime);
    void deleteTradeSeries(const Instrument& instrument);
    void flush();
    BarSeriesInfo getBarSeriesInfoList(const Instrument& instrument);
    BrokerInfo getBrokerInfo();
    BrokerInfo getBrokerInfo(const QString& provider);
    BrokerInfo getBrokerInfo(const QString& provider, int route);
    BarSeries getHistoricalBars(const Instrument& instrument);
    BarSeries getHistoricalBars(const Instrument& instrument, BarType barType, long barSize);
    BarSeries getHistoricalBars(const QString& provider, const Instrument& instrument, const QDateTime& begin, const QDateTime& end, int size);
    BarSeries getHistoricalBars(const Instrument& instrument, const QDateTime& begin, const QDateTime& end, BarType barType, long barSize);
    QuoteSeries getHistoricalQuotes(const Instrument& instrument, const QDateTime& begin, const QDateTime& end);
    QuoteSeries getHistoricalQuotes(const QString& provider, const Instrument& instrument, const QDateTime& begin, const QDateTime& end);
    TradeSeries getHistoricalTrades(const Instrument& instrument, const QDateTime& begin, const QDateTime& end);
    TradeSeries getHistoricalTrades(const QString& provider, const Instrument& instrument, const QDateTime& begin, const QDateTime& end);

private:
    QSharedDataPointer<Internal::DataManagerPrivate> d;
};

QDebug OPENTRADE_EXPORT operator << (QDebug, const DataManager &datamanager);

} // namespace OpenTrade

Q_DECLARE_SHARED(OpenTrade::DataManager)

#endif // __OPENTRADE_DATAMANAGER_H__
