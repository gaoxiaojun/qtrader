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
#include "scenario.h"

#include <QSharedData>

namespace OpenTrade {

namespace Internal {

class ScenarioPrivate : public QSharedData
{
public:
    ExecutionProvider m_executionProvider;
    MarketDataProvider m_marketDataProvider;
    StrategyMode m_mode;
    PortfolioPricer m_portfolioPricer;
    bool m_resetOnStart;
    Solution m_solution;
    bool m_startOver;
    EventHandler m_startRequested;
    EventHandler m_stopRequested;
};

} // namespace Internal

Scenario::Scenario()
{

}

Scenario::~Scenario()
{

}

Scenario& Scenario::operator=(const Scenario &other)
{
    d = other.d;
    return *this;
}

bool Scenario::operator==(const Scenario &other) const
{
    if(d == other.d)
      return true;

    return d->m_executionProvider == other.d->m_executionProvider &&
           d->m_marketDataProvider == other.d->m_marketDataProvider &&
           d->m_mode == other.d->m_mode &&
           d->m_portfolioPricer == other.d->m_portfolioPricer &&
           d->m_resetOnStart == other.d->m_resetOnStart &&
           d->m_solution == other.d->m_solution &&
           d->m_startOver == other.d->m_startOver &&
           d->m_startRequested == other.d->m_startRequested &&
           d->m_stopRequested == other.d->m_stopRequested;
}

void Scenario::run()
{

}

void Scenario::start()
{

}

void Scenario::start(StrategyMode mode)
{

}

void Scenario::stop()
{

}

ExecutionProvider Scenario::executionProvider() const
{
    return d->m_executionProvider;
}

MarketDataProvider Scenario::marketDataProvider() const
{
    return d->m_marketDataProvider;
}

StrategyMode Scenario::mode() const
{
    return d->m_mode;
}

void Scenario::setMode(StrategyMode mode)
{
    d->m_mode = mode;
}

PortfolioPricer Scenario::portfolioPricer() const
{
    return d->m_portfolioPricer;
}

void Scenario::setPortfolioPricer(const PortfolioPricer& portfoliopricer)
{
    d->m_portfolioPricer = portfoliopricer;
}

bool Scenario::resetOnStart() const
{
    return d->m_resetOnStart;
}

void Scenario::setResetOnStart(const bool& resetonstart)
{
    d->m_resetOnStart = resetonstart;
}

Solution Scenario::solution() const
{
    return d->m_solution;
}

bool Scenario::startOver() const
{
    return d->m_startOver;
}

void Scenario::setStartOver(const bool& startover)
{
    d->m_startOver = startover;
}

EventHandler Scenario::startRequested() const
{
    return d->m_startRequested;
}

EventHandler Scenario::stopRequested() const
{
    return d->m_stopRequested;
}


} // namespace OpenTrade

QDebug operator<<(QDebug c, const OpenTrade::Scenario &scenario)
{
    c.nospace() << "Scenario("
                << "ExecutionProvider:" << scenario.executionProvider() 
                << "MarketDataProvider:" << scenario.marketDataProvider() 
                << "Mode:" << scenario.mode() 
                << "PortfolioPricer:" << scenario.portfolioPricer() 
                << "ResetOnStart:" << scenario.resetOnStart() 
                << "Solution:" << scenario.solution() 
                << "StartOver:" << scenario.startOver() 
                << "StartRequested:" << scenario.startRequested() 
                << "StopRequested:" << scenario.stopRequested() 
                <<')';
    return c.space();
}
