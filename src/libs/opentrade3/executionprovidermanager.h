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

#ifndef OrderExecutionProviderManager_H
#define OrderExecutionProviderManager_H

#include <QObject>
#include "iexecutionprovider.h"

namespace OpenTrade {


class OrderExecutionProviderManager : public QObject
{
    Q_OBJECT
public:
    static OrderExecutionProviderManager *instance();

    explicit OrderExecutionProviderManager(QObject *parent = 0);
    ~OrderExecutionProviderManager();

    static QList<IOrderExecutionProvider *> getProviders();

    void initialize();
    void extensionsInitalized();

private slots:
    void objectAdded(QObject *obj);
    void aboutToRemoveObject(QObject *obj);

private slots:
    void orderAccepted(const Order& order);
    void orderCancelled(const Order& order);
    void orderRejected(const Order& order, const QString& message);
    void orderReplaced(const Order& order);
    void orderCancelReject(const Order& order, Order::OrderStatus status, const QString& message);
    void orderPendingReplace(const Order& order);
    void orderReplaceReject(const Order& order, Order::OrderStatus status, const QString& message );
    void orderFilled(const Order& order, double price, int quantity );
    //void orderFilled(const Order& order, double price, int quantity, CommissionType commissionType, double commission );

private:
    void connectToProvider(IOrderExecutionProvider *provider);
    void disconnectToProvider(IOrderExecutionProvider *provider);

    QList<IOrderExecutionProvider *> m_providers;

};

} // namespace OpenTrade
#endif // OrderExecutionProviderManager_H
