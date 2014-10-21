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
#ifndef __OPENTRADE_PORTFOLIO_H__
#define __OPENTRADE_PORTFOLIO_H__

#include "opentrade_global.h"
#include "instrument.h"
#include "portfolioaccount.h"
#include "positionlist.h"
#include "transactionlist.h"

#include <QSharedDataPointer>
#include <QDebug>
#include <QDateTime>
#include <QString>


namespace OpenTrade {

namespace Internal {
class PortfolioPrivate;
}

class OPENTRADE_EXPORT Portfolio
{
public:

    ~Portfolio();

    Portfolio& operator=(const Portfolio &other);
    void swap(Portfolio &other) { qSwap(d, other.d); }

#ifdef Q_COMPILER_RVALUE_REFS
    inline Portfolio &operator=(Portfolio &&other)
    { qSwap(d, other.d); return *this; }
#endif

    bool operator==(const Portfolio &other) const;
    inline bool operator!=(const Portfolio &other) const { return !(operator==(other)); }

    void add(const QDateTime& datetime, TransactionSide side, double qty, const Instrument& instrument, double price);
    void add(const QDateTime& datetime, TransactionSide side, double qty, const Instrument& instrument, double price, const QString& text);
    double getAccountValue();
    double getCashFlow();
    double getCoreEquity();
    double getDebtEquityRatio();
    double getDebtValue();
    double getLeverage();
    double getMarginValue();
    double getNetCashFlow();
    double getPositionValue();
    double getTotalEquity();
    double getValue();
    bool hasPosition(const Instrument& instrument);

    PortfolioAccount account() const;

    PositionList positions() const;

    TransactionList transactions() const;

private:
    QSharedDataPointer<Internal::PortfolioPrivate> d;
};

QDebug OPENTRADE_EXPORT operator << (QDebug, const Portfolio &portfolio);

} // namespace OpenTrade

Q_DECLARE_SHARED(OpenTrade::Portfolio)

#endif // __OPENTRADE_PORTFOLIO_H__
