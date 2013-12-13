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

#ifndef MARKETDATAPROVIDERMANAGER_H
#define MARKETDATAPROVIDERMANAGER_H

#include "imarketdataprovider.h"

#include <QObject>

namespace OpenTrade {

class MarketDataProviderManager : public QObject
{
    Q_OBJECT
public:
    static MarketDataProviderManager *instance();

    explicit MarketDataProviderManager(QObject *parent = 0);
    ~MarketDataProviderManager();

    static QList<IMarketDataProvider *> getProviders();

    void initialize();
    void extensionsInitalized();

private slots:
    void objectAdded(QObject *obj);
    void aboutToRemoveObject(QObject *obj);

    void newBar(const Instrument& instrument, long barSize, const QDateTime& begin,
                const QDateTime& end, double open, double hight, double low, double close, double volume);

    void newBarOpen(const Instrument& instrument, long barSize, const QDateTime& begin,
                    const QDateTime& end, double open, double hight, double low, double close, double volume);

    void newBarSlice(long barSize);


    void newQuote(const Instrument& instrument, const QDateTime& time, double bid, double ask,
                  int bidSize, int askSize);

    //void newOrderBookUpdate(const Instrument& instrument, const QDateTime& time, Bar::BidAsk side,
    //                        OrderBook::OrderBookAction action, double price, int size, int position );


private:
    void connectToProvider(IMarketDataProvider *provider);
    void disconnectToProvider(IMarketDataProvider *provider);

    QList<IMarketDataProvider *> m_providers;
};

} // namespace OpenTrade

#endif // MARKETDATAPROVIDERMANAGER_H
