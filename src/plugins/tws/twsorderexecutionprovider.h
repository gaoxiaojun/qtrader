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

#include <opentrade/iorderexecutionprovider.h>
#include <opentrade/order.h>

namespace Tws {

class TwsOrderExecutionProvider : public OpenTrade::IOrderExecutionProvider
{
    Q_OBJECT

public:
    TwsOrderExecutionProvider();
    ~TwsOrderExecutionProvider();

public:
    void send(const Order& order);
    void cancel(const Order& order);
    void replace(const Order& order, double newQty, double newPrice, double newStopPrice);

};

#endif // TWSORDEREXECUTIONPROVIDER_H
