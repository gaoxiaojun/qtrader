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
#ifndef __OPENTRADE_SCENARIO_H__
#define __OPENTRADE_SCENARIO_H__

#include "opentrade_global.h"
#include "executionprovider.h"
#include "marketdataprovider.h"
#include "portfoliopricer.h"
#include "solution.h"

#include <QSharedDataPointer>
#include <QDebug>


namespace OpenTrade {

namespace Internal {
class ScenarioPrivate;
}

class OPENTRADE_EXPORT Scenario
{
public:

    Scenario();
    ~Scenario();

    Scenario& operator=(const Scenario &other);
    void swap(Scenario &other) { qSwap(d, other.d); }

#ifdef Q_COMPILER_RVALUE_REFS
    inline Scenario &operator=(Scenario &&other)
    { qSwap(d, other.d); return *this; }
#endif

    bool operator==(const Scenario &other) const;
    inline bool operator!=(const Scenario &other) const { return !(operator==(other)); }

    void run();
    void start();
    void start(StrategyMode mode);
    void stop();

    ExecutionProvider executionProvider() const;

    MarketDataProvider marketDataProvider() const;

    StrategyMode mode() const;
    void setMode(StrategyMode mode);

    PortfolioPricer portfolioPricer() const;
    void setPortfolioPricer(const PortfolioPricer& portfoliopricer);

    bool resetOnStart() const;
    void setResetOnStart(bool resetonstart);

    Solution solution() const;

    bool startOver() const;
    void setStartOver(bool startover);

    EventHandler startRequested() const;

    EventHandler stopRequested() const;

private:
    QSharedDataPointer<Internal::ScenarioPrivate> d;
};

QDebug OPENTRADE_EXPORT operator << (QDebug, const Scenario &scenario);

} // namespace OpenTrade

Q_DECLARE_SHARED(OpenTrade::Scenario)

#endif // __OPENTRADE_SCENARIO_H__
