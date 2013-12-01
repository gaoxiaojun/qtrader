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

#include "twsorderexecutionprovider.h"

using namespace TWS;

TwsOrderExecutionProvider::TwsOrderExecutionProvider(QObject *parent) :
    IOrderExecutionProvider(parent)
{
}

TwsOrderExecutionProvider::~TwsOrderExecutionProvider()
{

}

void TwsOrderExecutionProvider::send(const OpenTrade::Order& order)
{

}

void TwsOrderExecutionProvider::cancel(const OpenTrade::Order& order)
{

}

void TwsOrderExecutionProvider::replace(const OpenTrade::Order& order, double newQty, double newPrice, double newStopPrice)
{

}
