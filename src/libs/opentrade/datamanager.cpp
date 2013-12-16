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
#include "datamanager.h"

#include <QSharedData>

namespace OpenTrade {

namespace Internal {

class DataManagerPrivate : public QSharedData
{
public:
};

} // namespace Internal

DataManager::DataManager()
{

}

DataManager::~DataManager()
{

}

DataManager& DataManager::operator=(const DataManager &other)
{
    d = other.d;
    return *this;
}

bool DataManager::operator==(const DataManager &other) const
{
    if(d == other.d)
      return true;

}

void DataManager::add(const Instrument& instrument, const Bar& bar)
{

}

void DataManager::add(const Instrument& instrument, const OrderBookUpdate& update)
{

}

void DataManager::add(const Instrument& instrument, const Quote& quote)
{

}

void DataManager::add(const Instrument& instrument, const Trade& trade)
{

}

void DataManager::add(const Instrument& instrument, const QDateTime& datetime, double price, int size)
{

}

void DataManager::add(const Instrument& instrument, const QDateTime& datetime, double bid, int bidsize, double ask, int asksize)
{

}

void DataManager::add(const Instrument& instrument, const QDateTime& datetime, BidAsk side, OrderBookAction action, int position, double price, int size)
{

}

void DataManager::add(const Instrument& instrument, const QDateTime& datetime, double open, double high, double low, double close, long volume, long size)
{

}

BarSeries DataManager::compressBars(const BarSeries& bars, long barSize)
{

}

BarSeries DataManager::compressBars(const TradeSeries& trades, BarType barType, long barSize)
{

}

BarSeries DataManager::compressBars(const QuoteSeries& quotes, QuoteData input, BarType barType, long barSize)
{

}

void DataManager::deleteBar(const Instrument& instrument, const QDateTime& datetime, BarType barType, long barSize)
{

}

void DataManager::deleteBarSeries(const Instrument& instrument, BarType barType, long barSize)
{

}

void DataManager::deleteDaily(const Instrument& instrument, const QDateTime& date)
{

}

void DataManager::deleteDailySeries(const Instrument& instrument)
{

}

void DataManager::deleteQuote(const Instrument& instrument, const QDateTime& datetime)
{

}

void DataManager::deleteQuoteSeries(const Instrument& instrument)
{

}

void DataManager::deleteTrade(const Instrument& instrument, const QDateTime& datetime)
{

}

void DataManager::deleteTradeSeries(const Instrument& instrument)
{

}

void DataManager::flush()
{

}

BarSeriesInfo DataManager::getBarSeriesInfoList(const Instrument& instrument)
{

}

BrokerInfo DataManager::getBrokerInfo()
{

}

BrokerInfo DataManager::getBrokerInfo(const QString& provider)
{

}

BrokerInfo DataManager::getBrokerInfo(const QString& provider, int route)
{

}

BarSeries DataManager::getHistoricalBars(const Instrument& instrument)
{

}

BarSeries DataManager::getHistoricalBars(const Instrument& instrument, BarType barType, long barSize)
{

}

BarSeries DataManager::getHistoricalBars(const QString& provider, const Instrument& instrument, const QDateTime& begin, const QDateTime& end, int size)
{

}

BarSeries DataManager::getHistoricalBars(const Instrument& instrument, const QDateTime& begin, const QDateTime& end, BarType barType, long barSize)
{

}

QuoteSeries DataManager::getHistoricalQuotes(const Instrument& instrument, const QDateTime& begin, const QDateTime& end)
{

}

QuoteSeries DataManager::getHistoricalQuotes(const QString& provider, const Instrument& instrument, const QDateTime& begin, const QDateTime& end)
{

}

TradeSeries DataManager::getHistoricalTrades(const Instrument& instrument, const QDateTime& begin, const QDateTime& end)
{

}

TradeSeries DataManager::getHistoricalTrades(const QString& provider, const Instrument& instrument, const QDateTime& begin, const QDateTime& end)
{

}


} // namespace OpenTrade

QDebug operator<<(QDebug c, const OpenTrade::DataManager &datamanager)
{
    c.nospace() << "DataManager("
                <<')';
    return c.space();
}
