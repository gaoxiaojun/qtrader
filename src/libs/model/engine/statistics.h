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
#ifndef __OPENTRADE_STATISTICS_H__
#define __OPENTRADE_STATISTICS_H__

#include "opentrade_global.h"

#include <QSharedDataPointer>
#include <QDebug>


namespace OpenTrade {

namespace Internal {
class StatisticsPrivate;
}

class OPENTRADE_EXPORT Statistics
{
public:

    ~Statistics();

    Statistics& operator=(const Statistics &other);
    void swap(Statistics &other) { qSwap(d, other.d); }

#ifdef Q_COMPILER_RVALUE_REFS
    inline Statistics &operator=(Statistics &&other)
    { qSwap(d, other.d); return *this; }
#endif

    bool operator==(const Statistics &other) const;
    inline bool operator!=(const Statistics &other) const { return !(operator==(other)); }


    double annualReturn() const;

    qint64 duration() const;

    double finalWealth() const;

    double initialWealth() const;

    int longTrades() const;

    double longTradesPnL() const;

    int losingLongTrades() const;

    int losingShortTrades() const;

    int losingTrades() const;

    double pnLPerLongTrade() const;

    double pnLPerShortTrade() const;

    double pnLPerTrade() const;

    int shortTrades() const;

    double shortTradesPnL() const;

    double totalPnL() const;

    double totalReturn() const;

    int totalTrades() const;

    qint64 transactionsFrequency() const;

    int winningLongTrades() const;

    int winningShortTrades() const;

    int winningTrades() const;

private:
    QSharedDataPointer<Internal::StatisticsPrivate> d;
};

QDebug OPENTRADE_EXPORT operator << (QDebug, const Statistics &statistics);

} // namespace OpenTrade

Q_DECLARE_SHARED(OpenTrade::Statistics)

#endif // __OPENTRADE_STATISTICS_H__
