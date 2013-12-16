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
#ifndef __OPENTRADE_BROKERORDER_H__
#define __OPENTRADE_BROKERORDER_H__

#include "opentrade_global.h"
#include "brokerorderfieldlist.h"

#include <QSharedDataPointer>
#include <QDebug>
#include <QString>


namespace OpenTrade {

namespace Internal {
class BrokerOrderPrivate;
}

class OPENTRADE_EXPORT BrokerOrder
{
public:

    ~BrokerOrder();

    BrokerOrder& operator=(const BrokerOrder &other);
    void swap(BrokerOrder &other) { qSwap(d, other.d); }

#ifdef Q_COMPILER_RVALUE_REFS
    inline BrokerOrder &operator=(BrokerOrder &&other)
    { qSwap(d, other.d); return *this; }
#endif

    bool operator==(const BrokerOrder &other) const;
    inline bool operator!=(const BrokerOrder &other) const { return !(operator==(other)); }

    void addCustomField(const QString& name, const QString& value);

    QString currency() const;
    void setCurrency(const QString& currency);

    QString exchange() const;
    void setExchange(const QString& exchange);

    BrokerOrderFieldList fields() const;

    InstrumentType instrumentType() const;
    void setInstrumentType(InstrumentType instrumenttype);

    QString orderID() const;
    void setOrderID(const QString& orderid);

    double price() const;
    void setPrice(double price);

    double qty() const;
    void setQty(double qty);

    OrderSide side() const;
    void setSide(OrderSide side);

    OrderStatus status() const;
    void setStatus(OrderStatus status);

    double stopPrice() const;
    void setStopPrice(double stopprice);

    QString symbol() const;
    void setSymbol(const QString& symbol);

    OrderType type() const;
    void setType(OrderType type);

private:
    QSharedDataPointer<Internal::BrokerOrderPrivate> d;
};

QDebug OPENTRADE_EXPORT operator << (QDebug, const BrokerOrder &brokerorder);

} // namespace OpenTrade

Q_DECLARE_SHARED(OpenTrade::BrokerOrder)

#endif // __OPENTRADE_BROKERORDER_H__
