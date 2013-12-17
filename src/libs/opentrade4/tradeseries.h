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
#ifndef __OPENTRADE_TRADESERIES_H__
#define __OPENTRADE_TRADESERIES_H__

#include "opentrade_global.h"
#include "trade.h"
#include "barseries.h"

#include <QSharedDataPointer>
#include <QDebug>


namespace OpenTrade {

namespace Internal {
class TradeSeriesPrivate;
}

class OPENTRADE_EXPORT TradeSeries
{
public:

    TradeSeries();
    ~TradeSeries();

    TradeSeries& operator=(const TradeSeries &other);
    void swap(TradeSeries &other) { qSwap(d, other.d); }

#ifdef Q_COMPILER_RVALUE_REFS
    inline TradeSeries &operator=(TradeSeries &&other)
    { qSwap(d, other.d); return *this; }
#endif

    bool operator==(const TradeSeries &other) const;
    inline bool operator!=(const TradeSeries &other) const { return !(operator==(other)); }

    void add(const Trade& trade);
    BarSeries compressBars(BarType barType, long barSize);

    int count() const;

    Trade last() const;

private:
    QSharedDataPointer<Internal::TradeSeriesPrivate> d;
};

QDebug OPENTRADE_EXPORT operator << (QDebug, const TradeSeries &tradeseries);

} // namespace OpenTrade

Q_DECLARE_SHARED(OpenTrade::TradeSeries)

#endif // __OPENTRADE_TRADESERIES_H__
