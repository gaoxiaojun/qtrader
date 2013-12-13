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

#ifndef IORDEREXECUTIONPROVIDER_HPP
#define IORDEREXECUTIONPROVIDER_HPP

#include "opentrade_global.h"
#include "iprovider.h"

#include "order.h"

namespace OpenTrade {

class Order;

class OPENTRADE_EXPORT IOrderExecutionProvider : public IProvider
{
    Q_OBJECT

public:
    IOrderExecutionProvider(QObject *parent) : IProvider(parent) {}
    virtual ~IOrderExecutionProvider() {}

    virtual void send(const Order& order) = 0;
    virtual void cancel(const Order& order) = 0;
    virtual void replace(const Order& order, double newQty, double newPrice, double newStopPrice) = 0;

signals:
    void orderAccepted(const Order& order);
    void orderCancelled(const Order& order);
    void orderRejected(const Order& order, const QString& message);
    void orderReplaced(const Order& order);
    void orderCancelReject(const Order& order, Order::OrderStatus status, const QString& message);
    void orderPendingReplace(const Order& order);
    void orderReplaceReject(const Order& order, Order::OrderStatus status, const QString& message );
    void orderFilled(const Order& order, double price, int quantity );
    //void orderFilled(const Order& order, double price, int quantity, CommissionType commissionType, double commission );
};

} // namespace OpenTrade
#endif // IORDEREXECUTIONPROVIDER_HPP
