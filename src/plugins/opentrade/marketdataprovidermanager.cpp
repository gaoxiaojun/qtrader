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

#include "marketdataprovidermanager.h"
#include "instrument.h"
#include "order.h"
#include "bar.h"
#include "quote.h"

#include <extensionsystem/pluginmanager.h>

using namespace OpenTrade;

static MarketDataProviderManager *m_instance = 0;

MarketDataProviderManager *MarketDataProviderManager::instance()
{
    return m_instance;
}

MarketDataProviderManager::MarketDataProviderManager(QObject *parent) :
    QObject(parent)
{
    m_instance = this;
}

MarketDataProviderManager::~MarketDataProviderManager()
{
    foreach(IMarketDataProvider *provider, m_providers) {
        disconnectToProvider (provider);
    }

    m_providers.clear();
}

void MarketDataProviderManager::init()
{
    connect(ExtensionSystem::PluginManager::instance(), SIGNAL(objectAdded(QObject*)),
            this, SLOT(objectAdded(QObject*)));
    connect(ExtensionSystem::PluginManager::instance(), SIGNAL(aboutToRemoveObject(QObject*)),
            this, SLOT(aboutToRemoveObject(QObject*)));
}

void MarketDataProviderManager::extensionsInitalized()
{
}

void MarketDataProviderManager::connectToProvider (IMarketDataProvider *provider)
{
    connect(provider, SIGNAL(newBar(const Instrument&, Bar::BarType, long, const QDateTime&,
                                    const QDateTime&, double, double, double, double, double)),
            this, SLOT(newBar(const Instrument&, Bar::BarType, long, const QDateTime&,
                              const QDateTime&, double, double, double, double, double)));

    connect(provider, SIGNAL(newBarOpen(const Instrument&, Bar::BarType, long, const QDateTime&,
                                    const QDateTime&, double, double, double, double, double)),
            this, SLOT(newBar(const Instrument&, Bar::BarType, long, const QDateTime&,
                              const QDateTime&, double, double, double, double, double)));
    connect(provider, SIGNAL(newBarSlice(long)), this, SLOT(newBarSlice(long)));

    connect(provider, SIGNAL(newQuote(const Instrument&, const QDateTime&, double, double, int, int)),
            this, SLOT(newQuote(const Instrument&, const QDateTime&, double, double, int, int)));

    connect(provider, SIGNAL(newOrderBookUpdate(const Instrument&, const QDateTime&, Bar::BidAsk,
                                                OrderBook::OrderBookAction, double, int, int )),
            this, SLOT(newOrderBookUpdate(const Instrument&, const QDateTime&, Bar::BidAsk,
                                          OrderBook::OrderBookAction, double, int, int)));

}

void MarketDataProviderManager::disconnectToProvider (IMarketDataProvider *provider)
{
    disconnect(provider, SIGNAL(newBar(const Instrument&, Bar::BarType, long, const QDateTime&,
                                    const QDateTime&, double, double, double, double, double)),
            this, SLOT(newBar(const Instrument&, Bar::BarType, long, const QDateTime&,
                              const QDateTime&, double, double, double, double, double)));

    disconnect(provider, SIGNAL(newBarOpen(const Instrument&, Bar::BarType, long, const QDateTime&,
                                    const QDateTime&, double, double, double, double, double)),
            this, SLOT(newBar(const Instrument&, Bar::BarType, long, const QDateTime&,
                              const QDateTime&, double, double, double, double, double)));
    disconnect(provider, SIGNAL(newBarSlice(long)), this, SLOT(newBarSlice(long)));

    disconnect(provider, SIGNAL(newQuote(const Instrument&, const QDateTime&, double, double, int, int)),
            this, SLOT(newQuote(const Instrument&, const QDateTime&, double, double, int, int)));

    disconnect(provider, SIGNAL(newOrderBookUpdate(const Instrument&, const QDateTime&, Bar::BidAsk,
                                                OrderBook::OrderBookAction, double, int, int )),
            this, SLOT(newOrderBookUpdate(const Instrument&, const QDateTime&, Bar::BidAsk,
                                          OrderBook::OrderBookAction, double, int, int)));

}

void MarketDataProviderManager::objectAdded(QObject *obj)
{
    IMarketDataProvider *provider = Aggregation::query<IMarketDataProvider>(obj);

    if(provider) {
        m_providers.append (provider);
        connectToProvider(provider);
    }

}

void MarketDataProviderManager::aboutToRemoveObject(QObject *obj)
{
    IMarketDataProvider *provider = Aggregation::query<IMarketDataProvider>(obj);

    if(provider) {
        m_providers.removeOne (provider);
        disconnectToProvider(provider);
    }
}

void MarketDataProviderManager::newBar(const Instrument& instrument, Bar::BarType barType, long barSize, const QDateTime& begin,
            const QDateTime& end, double open, double hight, double low, double close, double volume)
{

}

void MarketDataProviderManager::newBarOpen(const Instrument& instrument, Bar::BarType barType, long barSize, const QDateTime& begin,
                const QDateTime& end, double open, double hight, double low, double close, double volume)
{

}

void MarketDataProviderManager::newBarSlice(long barSize)
{

}


void MarketDataProviderManager::newQuote(const Instrument& instrument, const QDateTime& time, double bid, double ask,
              int bidSize, int askSize)
{

}

void MarketDataProviderManager::newOrderBookUpdate(const Instrument& instrument, const QDateTime& time, Bar::BidAsk side,
                        OrderBook::OrderBookAction action, double price, int size, int position )
{

}

