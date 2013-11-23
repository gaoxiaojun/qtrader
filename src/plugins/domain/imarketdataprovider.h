/****************************************************************************
**
** Copyright (C) 2013 Xiaojun Gao
** Contact: http://www.dailypips.org/legal
**
** This file is part of QTrader.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Digia gives you certain additional
** rights.  These rights are described in the Digia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
****************************************************************************/

#ifndef IMARKETDATAPROVIDER_H
#define IMARKETDATAPROVIDER_H

#include "iprovider.h"

#include <QObject>
#include <QDateTime>

namespace Domain {

class Instrument;
class Bar;

class IMarketDataProvider : public IProvider
{
    Q_OBJECT

public:
    enum OrderBookAction{
        Insert = 0,
        Update = 1,
        Delete = 2,
        Reset  = 3,
        Undefined = 4
    };

    explicit IMarketDataProvider(QObject *parent = 0) : QObject(parent) {}
    virtual ~IMarketDataProvider() {}

public:
    virtual void subscribe(const Instrument& instrument) = 0;
    virtual void unsubscribe(const Instrument& instrument) = 0;

signals:
    void newBar(int providerId, const Instrument& instrument, BarType barType, long barSize, const QDateTime& begin,
                const QDateTime& end, double open, double hight, double low, double close, double volume);

    void newBarOpen(int providerId, const Instrument& instrument, BarType barType, long barSize, const QDateTime& begin,
                    const QDateTime& end, double open, double hight, double low, double close, double volume);

    void newBarSlice(int providerId, long barSize);


    void newQuote(int providerId, const Instrument& instrument, const QDateTime& time, double bid, double ask,
                  int bidSize, int askSize);

    void newOrderBookUpdate(int providerId, const Instrument& instrument, const QDateTime& time, BidAsk side,
                            OrderBookAction action, double price, int size, int position );

};

} // namespace Domain

#endif // IMARKETDATAPROVIDER_H
