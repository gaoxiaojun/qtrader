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
#ifndef __OPENTRADE_PERFORMANCE_H__
#define __OPENTRADE_PERFORMANCE_H__

#include "opentrade_global.h"
#include "timeseries.h"

#include <QSharedDataPointer>
#include <QDebug>


namespace OpenTrade {

namespace Internal {
class PerformancePrivate;
}

class OPENTRADE_EXPORT Performance
{
public:

    ~Performance();

    Performance& operator=(const Performance &other);
    void swap(Performance &other) { qSwap(d, other.d); }

#ifdef Q_COMPILER_RVALUE_REFS
    inline Performance &operator=(Performance &&other)
    { qSwap(d, other.d); return *this; }
#endif

    bool operator==(const Performance &other) const;
    inline bool operator!=(const Performance &other) const { return !(operator==(other)); }


    double coreEquity() const;

    TimeSeries coreEquitySeries() const;

    double drawdown() const;

    double drawdownPercent() const;

    TimeSeries drawdownPercentSeries() const;

    TimeSeries drawdownSeries() const;

    double equity() const;

    TimeSeries equitySeries() const;

    double highEquity() const;

    bool isEnabled() const;
    void setIsEnabled(const bool& isenabled);

    double lowEquity() const;

    double pnL() const;

    TimeSeries pnLSeries() const;

private:
    QSharedDataPointer<Internal::PerformancePrivate> d;
};

QDebug OPENTRADE_EXPORT operator << (QDebug, const Performance &performance);

} // namespace OpenTrade

Q_DECLARE_SHARED(OpenTrade::Performance)

#endif // __OPENTRADE_PERFORMANCE_H__
