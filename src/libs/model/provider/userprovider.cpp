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
#include "userprovider.h"

#include <QSharedData>

namespace OpenTrade {

namespace Internal {

class UserProviderPrivate : public QSharedData
{
public:
    bool m_isConnected;
    QString m_description;
    int m_id;
    QString m_name;
    QString m_url;
};

} // namespace Internal

UserProvider::UserProvider()
{

}

UserProvider::~UserProvider()
{

}

UserProvider& UserProvider::operator=(const UserProvider &other)
{
    d = other.d;
    return *this;
}

bool UserProvider::operator==(const UserProvider &other) const
{
    if(d == other.d)
      return true;

    return d->m_isConnected == other.d->m_isConnected &&
           d->m_description == other.d->m_description &&
           d->m_id == other.d->m_id &&
           d->m_name == other.d->m_name &&
           d->m_url == other.d->m_url;
}

BrokerInfo UserProvider::getBrokerInfo()
{

}

void UserProvider::connect()
{

}

void UserProvider::disconnect()
{

}

void UserProvider::shutdown()
{

}

void UserProvider::emitConnected()
{

}

void UserProvider::emitDisconnected()
{

}

void UserProvider::emitError(const QString& message)
{

}

void UserProvider::emitError(int id, int code, const QString& message)
{

}

void UserProvider::subscribe(const Instrument& instrument)
{

}

void UserProvider::unsubscribe(const Instrument& instrument)
{

}

void UserProvider::emitNewBar(const Instrument& instrument, BarType barType, long barSize, const QDateTime& beginDateTime, const QDateTime& endDateTime, double open, double high, double low, double close, long volume)
{

}

void UserProvider::emitNewBarOpen(const Instrument& instrument, BarType barType, long barSize, const QDateTime& beginDateTime, const QDateTime& endDateTime, double open, double high, double low, double close, long volume)
{

}

void UserProvider::emitNewBarSlice(long barSize)
{

}

void UserProvider::emitNewQuote(const Instrument& instrument, const QDateTime& time, double bid, int bidSize, double ask, int askSize)
{

}

void UserProvider::emitNewQuote(const Instrument& instrument, const QDateTime& time, int providerId, double bid, int bidSize, double ask, int askSize)
{

}

void UserProvider::emitNewTrade(const Instrument& instrument, const QDateTime& time, double price, int size)
{

}

void UserProvider::emitNewTrade(const Instrument& instrument, const QDateTime& time, int providerId, double price, int size)
{

}

void UserProvider::emitNewOrderBookUpdate(const Instrument& instrument, const QDateTime& time, BidAsk side, OrderBookAction action, double price, int size, int position)
{

}

void UserProvider::requestHistoricalData(const HistoricalDataRequest& request)
{

}

void UserProvider::cancelHistoricalData(const HistoricalDataRequest& request)
{

}

void UserProvider::emitHistoricalDataCancelled(const HistoricalDataRequest& request)
{

}

void UserProvider::emitHistoricalDataCompleted(const HistoricalDataRequest& request)
{

}

void UserProvider::emitHistoricalDataError(const HistoricalDataRequest& request, const QString& message)
{

}

void UserProvider::emitNewHistoricalBar(const HistoricalDataRequest& request, const QDateTime& datetime, double open, double high, double low, double close, long volume)
{

}

void UserProvider::emitNewHistoricalQuote(const HistoricalDataRequest& request, const QDateTime& datetime, double bid, int bidSize, double ask, int askSize)
{

}

void UserProvider::emitNewHistoricalTrade(const HistoricalDataRequest& request, const QDateTime& datetime, double price, int size)
{

}

void UserProvider::send(const Order& order)
{

}

void UserProvider::cancel(const Order& order)
{

}

void UserProvider::replace(const Order& order, double newQty, double newPrice, double newStopPrice)
{

}

void UserProvider::emitAccepted(const Order& order)
{

}

void UserProvider::emitCancelled(const Order& order)
{

}

void UserProvider::emitRejected(const Order& order, const QString& message)
{

}

void UserProvider::emitReplaced(const Order& order)
{

}

void UserProvider::emitPendingCancel(const Order& order)
{

}

void UserProvider::emitCancelReject(const Order& order, OrderStatus status, const QString& message)
{

}

void UserProvider::emitPendingReplace(const Order& order)
{

}

void UserProvider::emitReplaceReject(const Order& order, OrderStatus status, const QString& message)
{

}

void UserProvider::emitFilled(const Order& order, double price, int quantity)
{

}

void UserProvider::emitFilled(const Order& order, double price, int quantity, CommissionType commissionType, double commission)
{

}

bool UserProvider::isConnected() const
{
    return d->m_isConnected;
}

QString UserProvider::description() const
{
    return d->m_description;
}

int UserProvider::id() const
{
    return d->m_id;
}

QString UserProvider::name() const
{
    return d->m_name;
}

QString UserProvider::url() const
{
    return d->m_url;
}


} // namespace OpenTrade

QDebug operator<<(QDebug c, const OpenTrade::UserProvider &userprovider)
{
    c.nospace() << "UserProvider("
                << "IsConnected:" << userprovider.isConnected() 
                << "description:" << userprovider.description() 
                << "id:" << userprovider.id() 
                << "name:" << userprovider.name() 
                << "url:" << userprovider.url() 
                <<')';
    return c.space();
}
