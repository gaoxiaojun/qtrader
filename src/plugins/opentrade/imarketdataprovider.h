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

#ifndef IMARKETDATAPROVIDER_H
#define IMARKETDATAPROVIDER_H

#include "opentrade_global.h"
#include "iprovider.h"

#include "bar.h"
#include "instrument.h"
#include "orderbook.h"

#include <QObject>
#include <QDateTime>

namespace OpenTrade {

class Instrument;
class Bar;

class OPENTRADE_EXPORT IMarketDataProvider : public IProvider
{
    Q_OBJECT

public:
    explicit IMarketDataProvider(QObject *parent = 0) : IProvider(parent) {}
    virtual ~IMarketDataProvider() {}

public:
    virtual bool subscribe(const Instrument& instrument) = 0;
    virtual bool unsubscribe(const Instrument& instrument) = 0;
    virtual QString errorString() = 0;

signals:
    void newBar(const Instrument& instrument, Bar::BarType barType, long barSize, const QDateTime& begin,
                const QDateTime& end, double open, double hight, double low, double close, double volume);

    void newBarOpen(const Instrument& instrument, Bar::BarType barType, long barSize, const QDateTime& begin,
                    const QDateTime& end, double open, double hight, double low, double close, double volume);

    void newBarSlice(long barSize);


    void newQuote(const Instrument& instrument, const QDateTime& time, double bid, double ask,
                  int bidSize, int askSize);

    void newOrderBookUpdate(const Instrument& instrument, const QDateTime& time, Bar::BidAsk side,
                            OrderBook::OrderBookAction action, double price, int size, int position );

};

} // namespace OpenTrade

#endif // IMARKETDATAPROVIDER_H
