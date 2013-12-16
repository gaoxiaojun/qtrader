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
#include "statistics.h"

#include <QSharedData>

namespace OpenTrade {

namespace Internal {

class StatisticsPrivate : public QSharedData
{
public:
    double m_annualReturn;
    qint64 m_duration;
    double m_finalWealth;
    double m_initialWealth;
    int m_longTrades;
    double m_longTradesPnL;
    int m_losingLongTrades;
    int m_losingShortTrades;
    int m_losingTrades;
    double m_pnLPerLongTrade;
    double m_pnLPerShortTrade;
    double m_pnLPerTrade;
    int m_shortTrades;
    double m_shortTradesPnL;
    double m_totalPnL;
    double m_totalReturn;
    int m_totalTrades;
    qint64 m_transactionsFrequency;
    int m_winningLongTrades;
    int m_winningShortTrades;
    int m_winningTrades;
};

} // namespace Internal

Statistics::~Statistics()
{

}

Statistics& Statistics::operator=(const Statistics &other)
{
    d = other.d;
    return *this;
}

bool Statistics::operator==(const Statistics &other) const
{
    if(d == other.d)
      return true;

    return d->m_annualReturn == other.d->m_annualReturn &&
           d->m_duration == other.d->m_duration &&
           d->m_finalWealth == other.d->m_finalWealth &&
           d->m_initialWealth == other.d->m_initialWealth &&
           d->m_longTrades == other.d->m_longTrades &&
           d->m_longTradesPnL == other.d->m_longTradesPnL &&
           d->m_losingLongTrades == other.d->m_losingLongTrades &&
           d->m_losingShortTrades == other.d->m_losingShortTrades &&
           d->m_losingTrades == other.d->m_losingTrades &&
           d->m_pnLPerLongTrade == other.d->m_pnLPerLongTrade &&
           d->m_pnLPerShortTrade == other.d->m_pnLPerShortTrade &&
           d->m_pnLPerTrade == other.d->m_pnLPerTrade &&
           d->m_shortTrades == other.d->m_shortTrades &&
           d->m_shortTradesPnL == other.d->m_shortTradesPnL &&
           d->m_totalPnL == other.d->m_totalPnL &&
           d->m_totalReturn == other.d->m_totalReturn &&
           d->m_totalTrades == other.d->m_totalTrades &&
           d->m_transactionsFrequency == other.d->m_transactionsFrequency &&
           d->m_winningLongTrades == other.d->m_winningLongTrades &&
           d->m_winningShortTrades == other.d->m_winningShortTrades &&
           d->m_winningTrades == other.d->m_winningTrades;
}

double Statistics::annualReturn() const
{
    return d->m_annualReturn;
}

qint64 Statistics::duration() const
{
    return d->m_duration;
}

double Statistics::finalWealth() const
{
    return d->m_finalWealth;
}

double Statistics::initialWealth() const
{
    return d->m_initialWealth;
}

int Statistics::longTrades() const
{
    return d->m_longTrades;
}

double Statistics::longTradesPnL() const
{
    return d->m_longTradesPnL;
}

int Statistics::losingLongTrades() const
{
    return d->m_losingLongTrades;
}

int Statistics::losingShortTrades() const
{
    return d->m_losingShortTrades;
}

int Statistics::losingTrades() const
{
    return d->m_losingTrades;
}

double Statistics::pnLPerLongTrade() const
{
    return d->m_pnLPerLongTrade;
}

double Statistics::pnLPerShortTrade() const
{
    return d->m_pnLPerShortTrade;
}

double Statistics::pnLPerTrade() const
{
    return d->m_pnLPerTrade;
}

int Statistics::shortTrades() const
{
    return d->m_shortTrades;
}

double Statistics::shortTradesPnL() const
{
    return d->m_shortTradesPnL;
}

double Statistics::totalPnL() const
{
    return d->m_totalPnL;
}

double Statistics::totalReturn() const
{
    return d->m_totalReturn;
}

int Statistics::totalTrades() const
{
    return d->m_totalTrades;
}

qint64 Statistics::transactionsFrequency() const
{
    return d->m_transactionsFrequency;
}

int Statistics::winningLongTrades() const
{
    return d->m_winningLongTrades;
}

int Statistics::winningShortTrades() const
{
    return d->m_winningShortTrades;
}

int Statistics::winningTrades() const
{
    return d->m_winningTrades;
}


} // namespace OpenTrade

QDebug operator<<(QDebug c, const OpenTrade::Statistics &statistics)
{
    c.nospace() << "Statistics("
                << "AnnualReturn:" << statistics.annualReturn() 
                << "Duration:" << statistics.duration() 
                << "FinalWealth:" << statistics.finalWealth() 
                << "InitialWealth:" << statistics.initialWealth() 
                << "LongTrades:" << statistics.longTrades() 
                << "LongTradesPnL:" << statistics.longTradesPnL() 
                << "LosingLongTrades:" << statistics.losingLongTrades() 
                << "LosingShortTrades:" << statistics.losingShortTrades() 
                << "LosingTrades:" << statistics.losingTrades() 
                << "PnLPerLongTrade:" << statistics.pnLPerLongTrade() 
                << "PnLPerShortTrade:" << statistics.pnLPerShortTrade() 
                << "PnLPerTrade:" << statistics.pnLPerTrade() 
                << "ShortTrades:" << statistics.shortTrades() 
                << "ShortTradesPnL:" << statistics.shortTradesPnL() 
                << "TotalPnL:" << statistics.totalPnL() 
                << "TotalReturn:" << statistics.totalReturn() 
                << "TotalTrades:" << statistics.totalTrades() 
                << "TransactionsFrequency:" << statistics.transactionsFrequency() 
                << "WinningLongTrades:" << statistics.winningLongTrades() 
                << "WinningShortTrades:" << statistics.winningShortTrades() 
                << "WinningTrades:" << statistics.winningTrades() 
                <<')';
    return c.space();
}
