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

#ifndef TWSORDEREXECUTIONPROVIDER_H
#define TWSORDEREXECUTIONPROVIDER_H

#include "twscontroller.h"
#include "twsproviderinfo.h"

#include <coreplugin/providermanager/iprovider.h>
#include <coreplugin/providermanager/iorderexecutionprovider.h>
#include <coreplugin/model/order.h>

namespace TWS {

class TwsOrderExecutionProvider : public OpenTrade::IOrderExecutionProvider
{
    Q_OBJECT

public:
    explicit TwsOrderExecutionProvider(QObject *parent);
    ~TwsOrderExecutionProvider();

public:
    // IProvider
    OpenTrade::ProviderInfo* info() const;
    bool isConnected() const;

    void connect();
    void disonnect();
    void shutdown();

public:
    void send(const OpenTrade::Order& order);
    void cancel(const OpenTrade::Order& order);
    void replace(const OpenTrade::Order& order, double newQty, double newPrice, double newStopPrice);

private:
    TwsController* m_controller;
    TwsProviderInfo *m_info;
};

} // namespace TWS

#endif // TWSORDEREXECUTIONPROVIDER_H
