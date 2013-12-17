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
#include "portfolio.h"

#include <QSharedData>

namespace OpenTrade {

namespace Internal {

class PortfolioPrivate : public QSharedData
{
public:
    PortfolioAccount m_account;
    PositionList m_positions;
    TransactionList m_transactions;
};

} // namespace Internal

Portfolio::~Portfolio()
{

}

Portfolio& Portfolio::operator=(const Portfolio &other)
{
    d = other.d;
    return *this;
}

bool Portfolio::operator==(const Portfolio &other) const
{
    if(d == other.d)
      return true;

    return d->m_account == other.d->m_account &&
           d->m_positions == other.d->m_positions &&
           d->m_transactions == other.d->m_transactions;
}

void Portfolio::add(const QDateTime& datetime, TransactionSide side, double qty, const Instrument& instrument, double price)
{

}

void Portfolio::add(const QDateTime& datetime, TransactionSide side, double qty, const Instrument& instrument, double price, const QString& text)
{

}

double Portfolio::getAccountValue()
{

}

double Portfolio::getCashFlow()
{

}

double Portfolio::getCoreEquity()
{

}

double Portfolio::getDebtEquityRatio()
{

}

double Portfolio::getDebtValue()
{

}

double Portfolio::getLeverage()
{

}

double Portfolio::getMarginValue()
{

}

double Portfolio::getNetCashFlow()
{

}

double Portfolio::getPositionValue()
{

}

double Portfolio::getTotalEquity()
{

}

double Portfolio::getValue()
{

}

bool Portfolio::hasPosition(const Instrument& instrument)
{

}

PortfolioAccount Portfolio::account() const
{
    return d->m_account;
}

PositionList Portfolio::positions() const
{
    return d->m_positions;
}

TransactionList Portfolio::transactions() const
{
    return d->m_transactions;
}


} // namespace OpenTrade

QDebug operator<<(QDebug c, const OpenTrade::Portfolio &portfolio)
{
    c.nospace() << "Portfolio("
                << "Account:" << portfolio.account() 
                << "Positions:" << portfolio.positions() 
                << "Transactions:" << portfolio.transactions() 
                <<')';
    return c.space();
}
