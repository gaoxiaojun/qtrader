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
#include "performance.h"

#include <QSharedData>

namespace OpenTrade {

namespace Internal {

class PerformancePrivate : public QSharedData
{
public:
    double m_coreEquity;
    TimeSeries m_coreEquitySeries;
    double m_drawdown;
    double m_drawdownPercent;
    TimeSeries m_drawdownPercentSeries;
    TimeSeries m_drawdownSeries;
    double m_equity;
    TimeSeries m_equitySeries;
    double m_highEquity;
    bool m_isEnabled;
    double m_lowEquity;
    double m_pnL;
    TimeSeries m_pnLSeries;
};

} // namespace Internal

Performance::~Performance()
{

}

Performance& Performance::operator=(const Performance &other)
{
    d = other.d;
    return *this;
}

bool Performance::operator==(const Performance &other) const
{
    if(d == other.d)
      return true;

    return d->m_coreEquity == other.d->m_coreEquity &&
           d->m_coreEquitySeries == other.d->m_coreEquitySeries &&
           d->m_drawdown == other.d->m_drawdown &&
           d->m_drawdownPercent == other.d->m_drawdownPercent &&
           d->m_drawdownPercentSeries == other.d->m_drawdownPercentSeries &&
           d->m_drawdownSeries == other.d->m_drawdownSeries &&
           d->m_equity == other.d->m_equity &&
           d->m_equitySeries == other.d->m_equitySeries &&
           d->m_highEquity == other.d->m_highEquity &&
           d->m_isEnabled == other.d->m_isEnabled &&
           d->m_lowEquity == other.d->m_lowEquity &&
           d->m_pnL == other.d->m_pnL &&
           d->m_pnLSeries == other.d->m_pnLSeries;
}

double Performance::coreEquity() const
{
    return d->m_coreEquity;
}

TimeSeries Performance::coreEquitySeries() const
{
    return d->m_coreEquitySeries;
}

double Performance::drawdown() const
{
    return d->m_drawdown;
}

double Performance::drawdownPercent() const
{
    return d->m_drawdownPercent;
}

TimeSeries Performance::drawdownPercentSeries() const
{
    return d->m_drawdownPercentSeries;
}

TimeSeries Performance::drawdownSeries() const
{
    return d->m_drawdownSeries;
}

double Performance::equity() const
{
    return d->m_equity;
}

TimeSeries Performance::equitySeries() const
{
    return d->m_equitySeries;
}

double Performance::highEquity() const
{
    return d->m_highEquity;
}

bool Performance::isEnabled() const
{
    return d->m_isEnabled;
}

void Performance::setIsEnabled(const bool& isenabled)
{
    d->m_isEnabled = isenabled;
}

double Performance::lowEquity() const
{
    return d->m_lowEquity;
}

double Performance::pnL() const
{
    return d->m_pnL;
}

TimeSeries Performance::pnLSeries() const
{
    return d->m_pnLSeries;
}


} // namespace OpenTrade

QDebug operator<<(QDebug c, const OpenTrade::Performance &performance)
{
    c.nospace() << "Performance("
                << "CoreEquity:" << performance.coreEquity() 
                << "CoreEquitySeries:" << performance.coreEquitySeries() 
                << "Drawdown:" << performance.drawdown() 
                << "DrawdownPercent:" << performance.drawdownPercent() 
                << "DrawdownPercentSeries:" << performance.drawdownPercentSeries() 
                << "DrawdownSeries:" << performance.drawdownSeries() 
                << "Equity:" << performance.equity() 
                << "EquitySeries:" << performance.equitySeries() 
                << "HighEquity:" << performance.highEquity() 
                << "IsEnabled:" << performance.isEnabled() 
                << "LowEquity:" << performance.lowEquity() 
                << "PnL:" << performance.pnL() 
                << "PnLSeries:" << performance.pnLSeries() 
                <<')';
    return c.space();
}
