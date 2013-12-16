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
#ifndef __OPENTRADE_USERPROVIDER_H__
#define __OPENTRADE_USERPROVIDER_H__

#include "opentrade_global.h"
#include "brokerinfo.h"
#include "instrument.h"
#include "historicaldatarequest.h"
#include "order.h"

#include <QSharedDataPointer>
#include <QDebug>
#include <QString>
#include <QDateTime>


namespace OpenTrade {

namespace Internal {
class UserProviderPrivate;
}

class OPENTRADE_EXPORT UserProvider
{
public:

    UserProvider();
    ~UserProvider();

    UserProvider& operator=(const UserProvider &other);
    void swap(UserProvider &other) { qSwap(d, other.d); }

#ifdef Q_COMPILER_RVALUE_REFS
    inline UserProvider &operator=(UserProvider &&other)
    { qSwap(d, other.d); return *this; }
#endif

    bool operator==(const UserProvider &other) const;
    inline bool operator!=(const UserProvider &other) const { return !(operator==(other)); }

    BrokerInfo getBrokerInfo();
    void connect();
    void disconnect();
    void shutdown();
    void emitConnected();
    void emitDisconnected();
    void emitError(const QString& message);
    void emitError(int id, int code, const QString& message);
    void subscribe(const Instrument& instrument);
    void unsubscribe(const Instrument& instrument);
    void emitNewBar(const Instrument& instrument, BarType barType, long barSize, const QDateTime& beginDateTime, const QDateTime& endDateTime, double open, double high, double low, double close, long volume);
    void emitNewBarOpen(const Instrument& instrument, BarType barType, long barSize, const QDateTime& beginDateTime, const QDateTime& endDateTime, double open, double high, double low, double close, long volume);
    void emitNewBarSlice(long barSize);
    void emitNewQuote(const Instrument& instrument, const QDateTime& time, double bid, int bidSize, double ask, int askSize);
    void emitNewQuote(const Instrument& instrument, const QDateTime& time, int providerId, double bid, int bidSize, double ask, int askSize);
    void emitNewTrade(const Instrument& instrument, const QDateTime& time, double price, int size);
    void emitNewTrade(const Instrument& instrument, const QDateTime& time, int providerId, double price, int size);
    void emitNewOrderBookUpdate(const Instrument& instrument, const QDateTime& time, BidAsk side, OrderBookAction action, double price, int size, int position);
    void requestHistoricalData(const HistoricalDataRequest& request);
    void cancelHistoricalData(const HistoricalDataRequest& request);
    void emitHistoricalDataCancelled(const HistoricalDataRequest& request);
    void emitHistoricalDataCompleted(const HistoricalDataRequest& request);
    void emitHistoricalDataError(const HistoricalDataRequest& request, const QString& message);
    void emitNewHistoricalBar(const HistoricalDataRequest& request, const QDateTime& datetime, double open, double high, double low, double close, long volume);
    void emitNewHistoricalQuote(const HistoricalDataRequest& request, const QDateTime& datetime, double bid, int bidSize, double ask, int askSize);
    void emitNewHistoricalTrade(const HistoricalDataRequest& request, const QDateTime& datetime, double price, int size);
    void send(const Order& order);
    void cancel(const Order& order);
    void replace(const Order& order, double newQty, double newPrice, double newStopPrice);
    void emitAccepted(const Order& order);
    void emitCancelled(const Order& order);
    void emitRejected(const Order& order, const QString& message);
    void emitReplaced(const Order& order);
    void emitPendingCancel(const Order& order);
    void emitCancelReject(const Order& order, OrderStatus status, const QString& message);
    void emitPendingReplace(const Order& order);
    void emitReplaceReject(const Order& order, OrderStatus status, const QString& message);
    void emitFilled(const Order& order, double price, int quantity);
    void emitFilled(const Order& order, double price, int quantity, CommissionType commissionType, double commission);

    bool isConnected() const;

    QString description() const;

    int id() const;

    QString name() const;

    QString url() const;

private:
    QSharedDataPointer<Internal::UserProviderPrivate> d;
};

QDebug OPENTRADE_EXPORT operator << (QDebug, const UserProvider &userprovider);

} // namespace OpenTrade

Q_DECLARE_SHARED(OpenTrade::UserProvider)

#endif // __OPENTRADE_USERPROVIDER_H__
