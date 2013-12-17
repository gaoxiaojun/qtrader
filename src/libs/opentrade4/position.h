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
#ifndef __OPENTRADE_POSITION_H__
#define __OPENTRADE_POSITION_H__

#include "opentrade_global.h"
#include "instrument.h"
#include "transactionlist.h"

#include <QSharedDataPointer>
#include <QDebug>
#include <QDateTime>


namespace OpenTrade {

namespace Internal {
class PositionPrivate;
}

class OPENTRADE_EXPORT Position
{
public:

    ~Position();

    Position& operator=(const Position &other);
    void swap(Position &other) { qSwap(d, other.d); }

#ifdef Q_COMPILER_RVALUE_REFS
    inline Position &operator=(Position &&other)
    { qSwap(d, other.d); return *this; }
#endif

    bool operator==(const Position &other) const;
    inline bool operator!=(const Position &other) const { return !(operator==(other)); }

    double getCashFlow();
    double getDebtValue();
    qint64 getDuration();
    double getLeverage();
    double getMarginValue();
    double getNetCashFlow();
    double getNetPnL();
    double getNetPnLPercent();
    double getPnL();
    double getPnLPercent();
    double getPrice();
    double getUnrealizedPnL();
    double getValue();

    double amount() const;

    double debt() const;

    QDateTime entryDate() const;

    double entryPrice() const;

    double entryQty() const;

    Instrument instrument() const;

    double margin() const;

    double qty() const;

    double qtyBought() const;

    double qtySold() const;

    double qtySoldShort() const;

    PositionSide side() const;

    TransactionList transactions() const;

private:
    QSharedDataPointer<Internal::PositionPrivate> d;
};

QDebug OPENTRADE_EXPORT operator << (QDebug, const Position &position);

} // namespace OpenTrade

Q_DECLARE_SHARED(OpenTrade::Position)

#endif // __OPENTRADE_POSITION_H__
