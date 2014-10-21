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
#ifndef __OPENTRADE_STRATEGY_H__
#define __OPENTRADE_STRATEGY_H__

#include "opentrade_global.h"
#include "instrument.h"
#include "order.h"
#include "indicator.h"
#include "timeseries.h"
#include "barseries.h"
#include "quoteseries.h"
#include "tradeseries.h"
#include "quote.h"
#include "trade.h"
#include "bar.h"
#include "orderbookupdate.h"
#include "providererror.h"
#include "stop.h"
#include "usercommand.h"
#include "position.h"
#include "chart.h"
#include "datarequests.h"
#include "executionprovider.h"
#include "instrumentlist.h"
#include "marketdataprovider.h"
#include "performance.h"
#include "portfolio.h"
#include "orderbook.h"
#include "orderlist.h"

#include <QSharedDataPointer>
#include <QDebug>
#include <QDateTime>
#include <QVariant>
#include <QString>


namespace OpenTrade {

namespace Internal {
class StrategyPrivate;
}

class OPENTRADE_EXPORT Strategy
{
public:

    Strategy();
    ~Strategy();

    Strategy& operator=(const Strategy &other);
    void swap(Strategy &other) { qSwap(d, other.d); }

#ifdef Q_COMPILER_RVALUE_REFS
    inline Strategy &operator=(Strategy &&other)
    { qSwap(d, other.d); return *this; }
#endif

    bool operator==(const Strategy &other) const;
    inline bool operator!=(const Strategy &other) const { return !(operator==(other)); }

    void addTimer(const QDateTime& datetime);
    void addTimer(const QDateTime& datetime, const QVariant& data);
    void buy(double qty);
    void buy(double qty, const QString& text);
    void buy(const Instrument& instrument, double qty, const QString& text);
    void buyLimit(double qty, double limitPrice);
    void buyLimit(double qty, double limitPrice, const QString& text);
    void buyLimit(const Instrument& instrument, double qty, double limitPrice);
    void buyLimit(const Instrument& instrument, double qty, double limitPrice, const QString& text);
    Order buyLimitOrder(double qty, double limitPrice);
    Order buyLimitOrder(double qty, double limitPrice, const QString& text);
    Order buyLimitOrder(const Instrument& instrument, double qty, double limitPrice);
    Order buyLimitOrder(const Instrument& instrument, double qty, double limitPrice, const QString& text);
    Order buyOrder(double qty);
    Order buyOrder(double qty, const QString& text);
    Order buyOrder(const Instrument& instrument, double qty);
    Order buyOrder(const Instrument& instrument, double qty, const QString& text);
    void buyStop(double qty, double stopPrice);
    void buyStop(double qty, double stopPrice, const QString& text);
    void buyStop(const Instrument& instrument, double qty, double stopPrice);
    void buyStop(const Instrument& instrument, double qty, double stopPrice, const QString& text);
    void buyStopLimit(double qty, double limitPrice, double stopPrice);
    void buyStopLimit(double qty, double limitPrice, double stopPrice, const QString& text);
    void buyStopLimit(const Instrument& instrument, double qty, double limitPrice, double stopPrice);
    void buyStopLimit(const Instrument& instrument, double qty, double limitPrice, double stopPrice, const QString& text);
    Order buyStopLimitOrder(double qty, double limitPrice, double stopPrice);
    Order buyStopLimitOrder(double qty, double limitPrice, double stopPrice, const QString& text);
    Order buyStopLimitOrder(const Instrument& instrument, double qty, double limitPrice, double stopPrice);
    Order buyStopLimitOrder(const Instrument& instrument, double qty, double limitPrice, double stopPrice, const QString& text);
    Order buyStopOrder(double qty, double stopPrice);
    Order buyStopOrder(double qty, double stopPrice, const QString& text);
    Order buyStopOrder(const Instrument& instrument, double qty, double stopPrice);
    Order buyStopOrder(const Instrument& instrument, double qty, double stopPrice, const QString& text);
    void cancelAllOrders();
    void cancelOrders();
    void closeAllPositions();
    void closeAllPositions(const QString& text);
    void closePosition();
    void closePosition(const QString& text);
    void draw(const Indicator& indicator);
    void draw(const TimeSeries& series);
    void draw(const Indicator& indicator, DrawStyle style);
    void draw(const Indicator& indicator, int padNumber);
    void draw(const TimeSeries& series, DrawStyle style);
    void draw(const TimeSeries& series, int padNumber);
    void draw(const Indicator& indicator, int padNumber, DrawStyle style);
    void draw(const TimeSeries& series, int padNumber, DrawStyle style);
    BarSeries getBars(long barSize);
    BarSeries getBars(const Instrument& instrument);
    BarSeries getBars(BarType barType, long barSize);
    BarSeries getBars(const Instrument& instrument, long barSize);
    BarSeries getBars(const Instrument& instrument, BarType barType, long barSize);
    BarSeries getHistoricalBars();
    BarSeries getHistoricalBars(const QDateTime& begin, const QDateTime& end);
    BarSeries getHistoricalBars(BarType barType, long barSize);
    BarSeries getHistoricalBars(const QDateTime& begin, const QDateTime& end, BarType barType, long barSize);
    BarSeries getHistoricalBars(const QString& provider, const QDateTime& begin, const QDateTime& end, int size);
    BarSeries getHistoricalBars(const QString& provider, const Instrument& instrument, const QDateTime& begin, const QDateTime& end, int size);
    QuoteSeries getHistoricalQuotes(const QDateTime& begin, const QDateTime& end);
    QuoteSeries getHistoricalQuotes(const QString& provider, const QDateTime& begin, const QDateTime& end);
    QuoteSeries getHistoricalQuotes(const QString& provider, const Instrument& instrument, const QDateTime& begin, const QDateTime& end);
    TradeSeries getHistoricalTrades(const QDateTime& begin, const QDateTime& end);
    TradeSeries getHistoricalTrades(const QString& provider, const QDateTime& begin, const QDateTime& end);
    TradeSeries getHistoricalTrades(const QString& provider, const Instrument& instrument, const QDateTime& begin, const QDateTime& end);
    QuoteSeries getQuotes(const Instrument& instrument);
    TradeSeries getTrades(const Instrument& instrument);
    bool hasPositionAmount(double amount);
    bool hasPositionQty(double qty);
    Order limitOrder(OrderSide side, double qty, double limitPrice);
    Order limitOrder(const Instrument& instrument, OrderSide side, double qty, double limitPrice);
    Order limitOrder(OrderSide side, double qty, double limitPrice, const QString& text);
    Order limitOrder(const Instrument& instrument, OrderSide side, double qty, double limitPrice, const QString& text);
    Order marketOrder(OrderSide side, double qty);
    Order marketOrder(const Instrument& instrument, OrderSide side, double qty);
    Order marketOrder(OrderSide side, double qty, const QString& text);
    Order marketOrder(const Instrument& instrument, OrderSide side, double qty, const QString& text);
    void onActiveChanged();
    void onQuote(const Quote& quote);
    void onTrade(const Trade& trade);
    void onBar(const Bar& bar);
    void onBarOpen(const Bar& bar);
    void onBarSlice(long size);
    void onOrderBookChanged(const OrderBookUpdate& update);
    void onConnected(const QString& provider);
    void onDisconnected(const QString& provider);
    void onError(const ProviderError& error);
    void onNewOrder(const Order& order);
    void onOrderCancelled(const Order& order);
    void onOrderCancelReject(const Order& order);
    void onOrderDone(const Order& order);
    void onOrderExpired(const Order& order);
    void onOrderFilled(const Order& order);
    void onOrderPartiallyFilled(const Order& order);
    void onOrderRejected(const Order& order);
    void onOrderReplaced(const Order& order);
    void onOrderReplaceReject(const Order& order);
    void onOrderStatusChanged(const Order& order);
    void onPositionChanged();
    void onPositionClosed();
    void onPositionOpened();
    void onPositionValueChanged();
    void onStopExecuted(const Stop& stop);
    void onStrategyStart();
    void onStrategyStop();
    void onTimer(const QDateTime& datetime, const QVariant& data);
    void onUserCommand(const UserCommand& command);
    void onCustomCommand(const QVariant& parameters);
    void removeTimer(const QDateTime& datetime);
    void removeTimer(const QDateTime& datetime, const QVariant& data);
    void removeTimers();
    void removeTimers(const QDateTime& datetime);
    void scan(BarData barData);
    void scan(const ISeries& series);
    void sell(double qty);
    void sell(double qty, const QString& text);
    void sell(const Instrument& instrument, double qty);
    void sell(const Instrument& instrument, double qty, const QString& text);
    void sellLimit(double qty, double limitPrice);
    void sellLimit(double qty, double limitPrice, const QString& text);
    void sellLimit(const Instrument& instrument, double qty, double limitPrice);
    void sellLimit(const Instrument& instrument, double qty, double limitPrice, const QString& text);
    Order sellLimitOrder(double qty, double limitPrice);
    Order sellLimitOrder(double qty, double limitPrice, const QString& text);
    Order sellLimitOrder(const Instrument& instrument, double qty, double limitPrice);
    Order sellLimitOrder(const Instrument& instrument, double qty, double limitPrice, const QString& text);
    Order sellOrder(double qty);
    Order sellOrder(double qty, const QString& text);
    Order sellOrder(const Instrument& instrument, double qty);
    Order sellOrder(const Instrument& instrument, double qty, const QString& text);
    void sellStop(double qty, double stopPrice);
    void sellStop(double qty, double stopPrice, const QString& text);
    void sellStop(const Instrument& instrument, double qty, double stopPrice);
    void sellStop(const Instrument& instrument, double qty, double stopPrice, const QString& text);
    void sellStopLimit(double qty, double limitPrice, double stopPrice);
    void sellStopLimit(double qty, double limitPrice, double stopPrice, const QString& text);
    void sellStopLimit(const Instrument& instrument, double qty, double limitPrice, double stopPrice);
    void sellStopLimit(const Instrument& instrument, double qty, double limitPrice, double stopPrice, const QString& text);
    Order sellStopLimitOrder(double qty, double limitPrice, double stopPrice);
    Order sellStopLimitOrder(double qty, double limitPrice, double stopPrice, const QString& text);
    Order sellStopLimitOrder(const Instrument& instrument, double qty, double limitPrice, double stopPrice);
    Order sellStopLimitOrder(const Instrument& instrument, double qty, double limitPrice, double stopPrice, const QString& text);
    Order sellStopOrder(double qty, double stopPrice);
    Order sellStopOrder(double qty, double stopPrice, const QString& text);
    Order sellStopOrder(const Instrument& instrument, double qty, double stopPrice);
    Order sellStopOrder(const Instrument& instrument, double qty, double stopPrice, const QString& text);
    void sendCustomCommand(const params& parameters);
    void sendCustomCommand(const QString& projectName, const params& parameters);
    void sendCustomCommand(const QString& projectName, const QString& symbol, const params& parameters);
    void sendLimitOrder(OrderSide side, double qty, double limitPrice);
    void sendLimitOrder(const Instrument& instrument, OrderSide side, double qty, double limitPrice);
    void sendLimitOrder(OrderSide side, double qty, double limitPrice, const QString& text);
    void sendLimitOrder(const Instrument& instrument, OrderSide side, double qty, double limitPrice, const QString& text);
    void sendMarketOrder(OrderSide side, double qty);
    void sendMarketOrder(const Instrument& instrument, OrderSide side, double qty);
    void sendMarketOrder(OrderSide side, double qty, const QString& text);
    void sendMarketOrder(const Instrument& instrument, OrderSide side, double qty, const QString& text);
    void sendStopLimitOrder(OrderSide side, double qty, double limitPrice, double stopPrice);
    void sendStopLimitOrder(const Instrument& instrument, OrderSide side, double qty, double limitPrice, double stopPrice);
    void sendStopLimitOrder(OrderSide side, double qty, double limitPrice, double stopPrice, const QString& text);
    void sendStopLimitOrder(const Instrument& instrument, OrderSide side, double qty, double limitPrice, double stopPrice, const QString& text);
    void sendStopOrder(OrderSide side, double qty, double stopPrice);
    void sendStopOrder(const Instrument& instrument, OrderSide side, double qty, double stopPrice);
    void sendStopOrder(OrderSide side, double qty, double stopPrice, const QString& text);
    void sendStopOrder(const Instrument& instrument, OrderSide side, double qty, double stopPrice, const QString& text);
    Stop setStop(const QDateTime& dateTime);
    Stop setStop(const Position& position, const QDateTime& dateTime);
    Stop setStop(double level, StopType type, StopMode mode);
    Stop setStop(const Position& position, double level, StopType type, StopMode mode);
    Order stopLimitOrder(OrderSide side, double qty, double limitPrice, double stopPrice);
    Order stopLimitOrder(const Instrument& instrument, OrderSide side, double qty, double limitPrice, double stopPrice);
    Order stopLimitOrder(OrderSide side, double qty, double limitPrice, double stopPrice, const QString& text);
    Order stopLimitOrder(const Instrument& instrument, OrderSide side, double qty, double limitPrice, double stopPrice, const QString& text);
    Order stopOrder(OrderSide side, double qty, double stopPrice);
    Order stopOrder(const Instrument& instrument, OrderSide side, double qty, double stopPrice);
    Order stopOrder(OrderSide side, double qty, double stopPrice, const QString& text);
    Order stopOrder(const Instrument& instrument, OrderSide side, double qty, double stopPrice, const QString& text);
    void stopStrategy();

    bool active() const;

    Bar bar() const;

    BarSeries bars() const;

    double cash() const;

    Chart chart() const;

    DataRequests dataRequests() const;

    ExecutionProvider executionProvider() const;

    static hashtable() const;

    bool hasPosition() const;

    Instrument instrument() const;

    IStrategyLogList instrumentLogs() const;

    InstrumentList instruments() const;

    MarketDataProvider marketDataProvider() const;

    Performance metaPerformance() const;

    Portfolio metaPortfolio() const;

    StrategyMode mode() const;

    QString name() const;

    OrderBook orderBook() const;

    OrderList orders() const;

    Performance performance() const;

    Portfolio portfolio() const;

    Position position() const;

    Quote quote() const;

    QuoteSeries quotes() const;

    IStrategyLogList solutionLogs() const;

    QDateTime startDate() const;

    QDateTime stopDate() const;

    IStrategyLogList strategyLogs() const;

    bool traceOnBar() const;
    void setTraceOnBar(bool traceonbar);

    bool traceOnQuote() const;
    void setTraceOnQuote(bool traceonquote);

    bool traceOnTrade() const;
    void setTraceOnTrade(bool traceontrade);

    Trade trade() const;

    TradeSeries trades() const;

private:
    QSharedDataPointer<Internal::StrategyPrivate> d;
};

QDebug OPENTRADE_EXPORT operator << (QDebug, const Strategy &strategy);

} // namespace OpenTrade

Q_DECLARE_SHARED(OpenTrade::Strategy)

#endif // __OPENTRADE_STRATEGY_H__
