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
#include "strategy.h"

#include <QSharedData>

namespace OpenTrade {

namespace Internal {

class StrategyPrivate : public QSharedData
{
public:
    bool m_active;
    Bar m_bar;
    BarSeries m_bars;
    double m_cash;
    Chart m_chart;
    DataRequests m_dataRequests;
    ExecutionProvider m_executionProvider;
    static m_hashtable;
    bool m_hasPosition;
    Instrument m_instrument;
    IStrategyLogList m_instrumentLogs;
    InstrumentList m_instruments;
    MarketDataProvider m_marketDataProvider;
    Performance m_metaPerformance;
    Portfolio m_metaPortfolio;
    StrategyMode m_mode;
    QString m_name;
    OrderBook m_orderBook;
    OrderList m_orders;
    Performance m_performance;
    Portfolio m_portfolio;
    Position m_position;
    Quote m_quote;
    QuoteSeries m_quotes;
    IStrategyLogList m_solutionLogs;
    QDateTime m_startDate;
    QDateTime m_stopDate;
    IStrategyLogList m_strategyLogs;
    bool m_traceOnBar;
    bool m_traceOnQuote;
    bool m_traceOnTrade;
    Trade m_trade;
    TradeSeries m_trades;
};

} // namespace Internal

Strategy::Strategy()
{

}

Strategy::~Strategy()
{

}

Strategy& Strategy::operator=(const Strategy &other)
{
    d = other.d;
    return *this;
}

bool Strategy::operator==(const Strategy &other) const
{
    if(d == other.d)
      return true;

    return d->m_active == other.d->m_active &&
           d->m_bar == other.d->m_bar &&
           d->m_bars == other.d->m_bars &&
           d->m_cash == other.d->m_cash &&
           d->m_chart == other.d->m_chart &&
           d->m_dataRequests == other.d->m_dataRequests &&
           d->m_executionProvider == other.d->m_executionProvider &&
           d->m_hashtable == other.d->m_hashtable &&
           d->m_hasPosition == other.d->m_hasPosition &&
           d->m_instrument == other.d->m_instrument &&
           d->m_instrumentLogs == other.d->m_instrumentLogs &&
           d->m_instruments == other.d->m_instruments &&
           d->m_marketDataProvider == other.d->m_marketDataProvider &&
           d->m_metaPerformance == other.d->m_metaPerformance &&
           d->m_metaPortfolio == other.d->m_metaPortfolio &&
           d->m_mode == other.d->m_mode &&
           d->m_name == other.d->m_name &&
           d->m_orderBook == other.d->m_orderBook &&
           d->m_orders == other.d->m_orders &&
           d->m_performance == other.d->m_performance &&
           d->m_portfolio == other.d->m_portfolio &&
           d->m_position == other.d->m_position &&
           d->m_quote == other.d->m_quote &&
           d->m_quotes == other.d->m_quotes &&
           d->m_solutionLogs == other.d->m_solutionLogs &&
           d->m_startDate == other.d->m_startDate &&
           d->m_stopDate == other.d->m_stopDate &&
           d->m_strategyLogs == other.d->m_strategyLogs &&
           d->m_traceOnBar == other.d->m_traceOnBar &&
           d->m_traceOnQuote == other.d->m_traceOnQuote &&
           d->m_traceOnTrade == other.d->m_traceOnTrade &&
           d->m_trade == other.d->m_trade &&
           d->m_trades == other.d->m_trades;
}

void Strategy::addTimer(const QDateTime& datetime)
{

}

void Strategy::addTimer(const QDateTime& datetime, const QVariant& data)
{

}

void Strategy::buy(double qty)
{

}

void Strategy::buy(double qty, const QString& text)
{

}

void Strategy::buy(const Instrument& instrument, double qty, const QString& text)
{

}

void Strategy::buyLimit(double qty, double limitPrice)
{

}

void Strategy::buyLimit(double qty, double limitPrice, const QString& text)
{

}

void Strategy::buyLimit(const Instrument& instrument, double qty, double limitPrice)
{

}

void Strategy::buyLimit(const Instrument& instrument, double qty, double limitPrice, const QString& text)
{

}

Order Strategy::buyLimitOrder(double qty, double limitPrice)
{

}

Order Strategy::buyLimitOrder(double qty, double limitPrice, const QString& text)
{

}

Order Strategy::buyLimitOrder(const Instrument& instrument, double qty, double limitPrice)
{

}

Order Strategy::buyLimitOrder(const Instrument& instrument, double qty, double limitPrice, const QString& text)
{

}

Order Strategy::buyOrder(double qty)
{

}

Order Strategy::buyOrder(double qty, const QString& text)
{

}

Order Strategy::buyOrder(const Instrument& instrument, double qty)
{

}

Order Strategy::buyOrder(const Instrument& instrument, double qty, const QString& text)
{

}

void Strategy::buyStop(double qty, double stopPrice)
{

}

void Strategy::buyStop(double qty, double stopPrice, const QString& text)
{

}

void Strategy::buyStop(const Instrument& instrument, double qty, double stopPrice)
{

}

void Strategy::buyStop(const Instrument& instrument, double qty, double stopPrice, const QString& text)
{

}

void Strategy::buyStopLimit(double qty, double limitPrice, double stopPrice)
{

}

void Strategy::buyStopLimit(double qty, double limitPrice, double stopPrice, const QString& text)
{

}

void Strategy::buyStopLimit(const Instrument& instrument, double qty, double limitPrice, double stopPrice)
{

}

void Strategy::buyStopLimit(const Instrument& instrument, double qty, double limitPrice, double stopPrice, const QString& text)
{

}

Order Strategy::buyStopLimitOrder(double qty, double limitPrice, double stopPrice)
{

}

Order Strategy::buyStopLimitOrder(double qty, double limitPrice, double stopPrice, const QString& text)
{

}

Order Strategy::buyStopLimitOrder(const Instrument& instrument, double qty, double limitPrice, double stopPrice)
{

}

Order Strategy::buyStopLimitOrder(const Instrument& instrument, double qty, double limitPrice, double stopPrice, const QString& text)
{

}

Order Strategy::buyStopOrder(double qty, double stopPrice)
{

}

Order Strategy::buyStopOrder(double qty, double stopPrice, const QString& text)
{

}

Order Strategy::buyStopOrder(const Instrument& instrument, double qty, double stopPrice)
{

}

Order Strategy::buyStopOrder(const Instrument& instrument, double qty, double stopPrice, const QString& text)
{

}

void Strategy::cancelAllOrders()
{

}

void Strategy::cancelOrders()
{

}

void Strategy::closeAllPositions()
{

}

void Strategy::closeAllPositions(const QString& text)
{

}

void Strategy::closePosition()
{

}

void Strategy::closePosition(const QString& text)
{

}

void Strategy::draw(const Indicator& indicator)
{

}

void Strategy::draw(const TimeSeries& series)
{

}

void Strategy::draw(const Indicator& indicator, DrawStyle style)
{

}

void Strategy::draw(const Indicator& indicator, int padNumber)
{

}

void Strategy::draw(const TimeSeries& series, DrawStyle style)
{

}

void Strategy::draw(const TimeSeries& series, int padNumber)
{

}

void Strategy::draw(const Indicator& indicator, int padNumber, DrawStyle style)
{

}

void Strategy::draw(const TimeSeries& series, int padNumber, DrawStyle style)
{

}

BarSeries Strategy::getBars(long barSize)
{

}

BarSeries Strategy::getBars(const Instrument& instrument)
{

}

BarSeries Strategy::getBars(BarType barType, long barSize)
{

}

BarSeries Strategy::getBars(const Instrument& instrument, long barSize)
{

}

BarSeries Strategy::getBars(const Instrument& instrument, BarType barType, long barSize)
{

}

BarSeries Strategy::getHistoricalBars()
{

}

BarSeries Strategy::getHistoricalBars(const QDateTime& begin, const QDateTime& end)
{

}

BarSeries Strategy::getHistoricalBars(BarType barType, long barSize)
{

}

BarSeries Strategy::getHistoricalBars(const QDateTime& begin, const QDateTime& end, BarType barType, long barSize)
{

}

BarSeries Strategy::getHistoricalBars(const QString& provider, const QDateTime& begin, const QDateTime& end, int size)
{

}

BarSeries Strategy::getHistoricalBars(const QString& provider, const Instrument& instrument, const QDateTime& begin, const QDateTime& end, int size)
{

}

QuoteSeries Strategy::getHistoricalQuotes(const QDateTime& begin, const QDateTime& end)
{

}

QuoteSeries Strategy::getHistoricalQuotes(const QString& provider, const QDateTime& begin, const QDateTime& end)
{

}

QuoteSeries Strategy::getHistoricalQuotes(const QString& provider, const Instrument& instrument, const QDateTime& begin, const QDateTime& end)
{

}

TradeSeries Strategy::getHistoricalTrades(const QDateTime& begin, const QDateTime& end)
{

}

TradeSeries Strategy::getHistoricalTrades(const QString& provider, const QDateTime& begin, const QDateTime& end)
{

}

TradeSeries Strategy::getHistoricalTrades(const QString& provider, const Instrument& instrument, const QDateTime& begin, const QDateTime& end)
{

}

QuoteSeries Strategy::getQuotes(const Instrument& instrument)
{

}

TradeSeries Strategy::getTrades(const Instrument& instrument)
{

}

bool Strategy::hasPositionAmount(double amount)
{

}

bool Strategy::hasPositionQty(double qty)
{

}

Order Strategy::limitOrder(OrderSide side, double qty, double limitPrice)
{

}

Order Strategy::limitOrder(const Instrument& instrument, OrderSide side, double qty, double limitPrice)
{

}

Order Strategy::limitOrder(OrderSide side, double qty, double limitPrice, const QString& text)
{

}

Order Strategy::limitOrder(const Instrument& instrument, OrderSide side, double qty, double limitPrice, const QString& text)
{

}

Order Strategy::marketOrder(OrderSide side, double qty)
{

}

Order Strategy::marketOrder(const Instrument& instrument, OrderSide side, double qty)
{

}

Order Strategy::marketOrder(OrderSide side, double qty, const QString& text)
{

}

Order Strategy::marketOrder(const Instrument& instrument, OrderSide side, double qty, const QString& text)
{

}

void Strategy::onActiveChanged()
{

}

void Strategy::onQuote(const Quote& quote)
{

}

void Strategy::onTrade(const Trade& trade)
{

}

void Strategy::onBar(const Bar& bar)
{

}

void Strategy::onBarOpen(const Bar& bar)
{

}

void Strategy::onBarSlice(long size)
{

}

void Strategy::onOrderBookChanged(const OrderBookUpdate& update)
{

}

void Strategy::onConnected(const QString& provider)
{

}

void Strategy::onDisconnected(const QString& provider)
{

}

void Strategy::onError(const ProviderError& error)
{

}

void Strategy::onNewOrder(const Order& order)
{

}

void Strategy::onOrderCancelled(const Order& order)
{

}

void Strategy::onOrderCancelReject(const Order& order)
{

}

void Strategy::onOrderDone(const Order& order)
{

}

void Strategy::onOrderExpired(const Order& order)
{

}

void Strategy::onOrderFilled(const Order& order)
{

}

void Strategy::onOrderPartiallyFilled(const Order& order)
{

}

void Strategy::onOrderRejected(const Order& order)
{

}

void Strategy::onOrderReplaced(const Order& order)
{

}

void Strategy::onOrderReplaceReject(const Order& order)
{

}

void Strategy::onOrderStatusChanged(const Order& order)
{

}

void Strategy::onPositionChanged()
{

}

void Strategy::onPositionClosed()
{

}

void Strategy::onPositionOpened()
{

}

void Strategy::onPositionValueChanged()
{

}

void Strategy::onStopExecuted(const Stop& stop)
{

}

void Strategy::onStrategyStart()
{

}

void Strategy::onStrategyStop()
{

}

void Strategy::onTimer(const QDateTime& datetime, const QVariant& data)
{

}

void Strategy::onUserCommand(const UserCommand& command)
{

}

void Strategy::onCustomCommand(const QVariant& parameters)
{

}

void Strategy::removeTimer(const QDateTime& datetime)
{

}

void Strategy::removeTimer(const QDateTime& datetime, const QVariant& data)
{

}

void Strategy::removeTimers()
{

}

void Strategy::removeTimers(const QDateTime& datetime)
{

}

void Strategy::scan(BarData barData)
{

}

void Strategy::scan(const ISeries& series)
{

}

void Strategy::sell(double qty)
{

}

void Strategy::sell(double qty, const QString& text)
{

}

void Strategy::sell(const Instrument& instrument, double qty)
{

}

void Strategy::sell(const Instrument& instrument, double qty, const QString& text)
{

}

void Strategy::sellLimit(double qty, double limitPrice)
{

}

void Strategy::sellLimit(double qty, double limitPrice, const QString& text)
{

}

void Strategy::sellLimit(const Instrument& instrument, double qty, double limitPrice)
{

}

void Strategy::sellLimit(const Instrument& instrument, double qty, double limitPrice, const QString& text)
{

}

Order Strategy::sellLimitOrder(double qty, double limitPrice)
{

}

Order Strategy::sellLimitOrder(double qty, double limitPrice, const QString& text)
{

}

Order Strategy::sellLimitOrder(const Instrument& instrument, double qty, double limitPrice)
{

}

Order Strategy::sellLimitOrder(const Instrument& instrument, double qty, double limitPrice, const QString& text)
{

}

Order Strategy::sellOrder(double qty)
{

}

Order Strategy::sellOrder(double qty, const QString& text)
{

}

Order Strategy::sellOrder(const Instrument& instrument, double qty)
{

}

Order Strategy::sellOrder(const Instrument& instrument, double qty, const QString& text)
{

}

void Strategy::sellStop(double qty, double stopPrice)
{

}

void Strategy::sellStop(double qty, double stopPrice, const QString& text)
{

}

void Strategy::sellStop(const Instrument& instrument, double qty, double stopPrice)
{

}

void Strategy::sellStop(const Instrument& instrument, double qty, double stopPrice, const QString& text)
{

}

void Strategy::sellStopLimit(double qty, double limitPrice, double stopPrice)
{

}

void Strategy::sellStopLimit(double qty, double limitPrice, double stopPrice, const QString& text)
{

}

void Strategy::sellStopLimit(const Instrument& instrument, double qty, double limitPrice, double stopPrice)
{

}

void Strategy::sellStopLimit(const Instrument& instrument, double qty, double limitPrice, double stopPrice, const QString& text)
{

}

Order Strategy::sellStopLimitOrder(double qty, double limitPrice, double stopPrice)
{

}

Order Strategy::sellStopLimitOrder(double qty, double limitPrice, double stopPrice, const QString& text)
{

}

Order Strategy::sellStopLimitOrder(const Instrument& instrument, double qty, double limitPrice, double stopPrice)
{

}

Order Strategy::sellStopLimitOrder(const Instrument& instrument, double qty, double limitPrice, double stopPrice, const QString& text)
{

}

Order Strategy::sellStopOrder(double qty, double stopPrice)
{

}

Order Strategy::sellStopOrder(double qty, double stopPrice, const QString& text)
{

}

Order Strategy::sellStopOrder(const Instrument& instrument, double qty, double stopPrice)
{

}

Order Strategy::sellStopOrder(const Instrument& instrument, double qty, double stopPrice, const QString& text)
{

}

void Strategy::sendCustomCommand(const params& parameters)
{

}

void Strategy::sendCustomCommand(const QString& projectName, const params& parameters)
{

}

void Strategy::sendCustomCommand(const QString& projectName, const QString& symbol, const params& parameters)
{

}

void Strategy::sendLimitOrder(OrderSide side, double qty, double limitPrice)
{

}

void Strategy::sendLimitOrder(const Instrument& instrument, OrderSide side, double qty, double limitPrice)
{

}

void Strategy::sendLimitOrder(OrderSide side, double qty, double limitPrice, const QString& text)
{

}

void Strategy::sendLimitOrder(const Instrument& instrument, OrderSide side, double qty, double limitPrice, const QString& text)
{

}

void Strategy::sendMarketOrder(OrderSide side, double qty)
{

}

void Strategy::sendMarketOrder(const Instrument& instrument, OrderSide side, double qty)
{

}

void Strategy::sendMarketOrder(OrderSide side, double qty, const QString& text)
{

}

void Strategy::sendMarketOrder(const Instrument& instrument, OrderSide side, double qty, const QString& text)
{

}

void Strategy::sendStopLimitOrder(OrderSide side, double qty, double limitPrice, double stopPrice)
{

}

void Strategy::sendStopLimitOrder(const Instrument& instrument, OrderSide side, double qty, double limitPrice, double stopPrice)
{

}

void Strategy::sendStopLimitOrder(OrderSide side, double qty, double limitPrice, double stopPrice, const QString& text)
{

}

void Strategy::sendStopLimitOrder(const Instrument& instrument, OrderSide side, double qty, double limitPrice, double stopPrice, const QString& text)
{

}

void Strategy::sendStopOrder(OrderSide side, double qty, double stopPrice)
{

}

void Strategy::sendStopOrder(const Instrument& instrument, OrderSide side, double qty, double stopPrice)
{

}

void Strategy::sendStopOrder(OrderSide side, double qty, double stopPrice, const QString& text)
{

}

void Strategy::sendStopOrder(const Instrument& instrument, OrderSide side, double qty, double stopPrice, const QString& text)
{

}

Stop Strategy::setStop(const QDateTime& dateTime)
{

}

Stop Strategy::setStop(const Position& position, const QDateTime& dateTime)
{

}

Stop Strategy::setStop(double level, StopType type, StopMode mode)
{

}

Stop Strategy::setStop(const Position& position, double level, StopType type, StopMode mode)
{

}

Order Strategy::stopLimitOrder(OrderSide side, double qty, double limitPrice, double stopPrice)
{

}

Order Strategy::stopLimitOrder(const Instrument& instrument, OrderSide side, double qty, double limitPrice, double stopPrice)
{

}

Order Strategy::stopLimitOrder(OrderSide side, double qty, double limitPrice, double stopPrice, const QString& text)
{

}

Order Strategy::stopLimitOrder(const Instrument& instrument, OrderSide side, double qty, double limitPrice, double stopPrice, const QString& text)
{

}

Order Strategy::stopOrder(OrderSide side, double qty, double stopPrice)
{

}

Order Strategy::stopOrder(const Instrument& instrument, OrderSide side, double qty, double stopPrice)
{

}

Order Strategy::stopOrder(OrderSide side, double qty, double stopPrice, const QString& text)
{

}

Order Strategy::stopOrder(const Instrument& instrument, OrderSide side, double qty, double stopPrice, const QString& text)
{

}

void Strategy::stopStrategy()
{

}

bool Strategy::active() const
{
    return d->m_active;
}

Bar Strategy::bar() const
{
    return d->m_bar;
}

BarSeries Strategy::bars() const
{
    return d->m_bars;
}

double Strategy::cash() const
{
    return d->m_cash;
}

Chart Strategy::chart() const
{
    return d->m_chart;
}

DataRequests Strategy::dataRequests() const
{
    return d->m_dataRequests;
}

ExecutionProvider Strategy::executionProvider() const
{
    return d->m_executionProvider;
}

static Strategy::hashtable() const
{
    return d->m_hashtable;
}

bool Strategy::hasPosition() const
{
    return d->m_hasPosition;
}

Instrument Strategy::instrument() const
{
    return d->m_instrument;
}

IStrategyLogList Strategy::instrumentLogs() const
{
    return d->m_instrumentLogs;
}

InstrumentList Strategy::instruments() const
{
    return d->m_instruments;
}

MarketDataProvider Strategy::marketDataProvider() const
{
    return d->m_marketDataProvider;
}

Performance Strategy::metaPerformance() const
{
    return d->m_metaPerformance;
}

Portfolio Strategy::metaPortfolio() const
{
    return d->m_metaPortfolio;
}

StrategyMode Strategy::mode() const
{
    return d->m_mode;
}

QString Strategy::name() const
{
    return d->m_name;
}

OrderBook Strategy::orderBook() const
{
    return d->m_orderBook;
}

OrderList Strategy::orders() const
{
    return d->m_orders;
}

Performance Strategy::performance() const
{
    return d->m_performance;
}

Portfolio Strategy::portfolio() const
{
    return d->m_portfolio;
}

Position Strategy::position() const
{
    return d->m_position;
}

Quote Strategy::quote() const
{
    return d->m_quote;
}

QuoteSeries Strategy::quotes() const
{
    return d->m_quotes;
}

IStrategyLogList Strategy::solutionLogs() const
{
    return d->m_solutionLogs;
}

QDateTime Strategy::startDate() const
{
    return d->m_startDate;
}

QDateTime Strategy::stopDate() const
{
    return d->m_stopDate;
}

IStrategyLogList Strategy::strategyLogs() const
{
    return d->m_strategyLogs;
}

bool Strategy::traceOnBar() const
{
    return d->m_traceOnBar;
}

void Strategy::setTraceOnBar(const bool& traceonbar)
{
    d->m_traceOnBar = traceonbar;
}

bool Strategy::traceOnQuote() const
{
    return d->m_traceOnQuote;
}

void Strategy::setTraceOnQuote(const bool& traceonquote)
{
    d->m_traceOnQuote = traceonquote;
}

bool Strategy::traceOnTrade() const
{
    return d->m_traceOnTrade;
}

void Strategy::setTraceOnTrade(const bool& traceontrade)
{
    d->m_traceOnTrade = traceontrade;
}

Trade Strategy::trade() const
{
    return d->m_trade;
}

TradeSeries Strategy::trades() const
{
    return d->m_trades;
}


} // namespace OpenTrade

QDebug operator<<(QDebug c, const OpenTrade::Strategy &strategy)
{
    c.nospace() << "Strategy("
                << "Active:" << strategy.active() 
                << "Bar:" << strategy.bar() 
                << "Bars:" << strategy.bars() 
                << "Cash:" << strategy.cash() 
                << "Chart:" << strategy.chart() 
                << "DataRequests:" << strategy.dataRequests() 
                << "ExecutionProvider:" << strategy.executionProvider() 
                << "Hashtable:" << strategy.hashtable() 
                << "HasPosition:" << strategy.hasPosition() 
                << "Instrument:" << strategy.instrument() 
                << "InstrumentLogs:" << strategy.instrumentLogs() 
                << "Instruments:" << strategy.instruments() 
                << "MarketDataProvider:" << strategy.marketDataProvider() 
                << "MetaPerformance:" << strategy.metaPerformance() 
                << "MetaPortfolio:" << strategy.metaPortfolio() 
                << "Mode:" << strategy.mode() 
                << "Name:" << strategy.name() 
                << "OrderBook:" << strategy.orderBook() 
                << "Orders:" << strategy.orders() 
                << "Performance:" << strategy.performance() 
                << "Portfolio:" << strategy.portfolio() 
                << "Position:" << strategy.position() 
                << "Quote:" << strategy.quote() 
                << "Quotes:" << strategy.quotes() 
                << "SolutionLogs:" << strategy.solutionLogs() 
                << "StartDate:" << strategy.startDate() 
                << "StopDate:" << strategy.stopDate() 
                << "StrategyLogs:" << strategy.strategyLogs() 
                << "TraceOnBar:" << strategy.traceOnBar() 
                << "TraceOnQuote:" << strategy.traceOnQuote() 
                << "TraceOnTrade:" << strategy.traceOnTrade() 
                << "Trade:" << strategy.trade() 
                << "Trades:" << strategy.trades() 
                <<')';
    return c.space();
}
