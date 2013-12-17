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
#ifndef __OPENTRADE_CANVAS_H__
#define __OPENTRADE_CANVAS_H__

#include "opentrade_global.h"
#include "barseries.h"
#include "indicator.h"
#include "order.h"
#include "quoteseries.h"
#include "timeseries.h"
#include "tradeseries.h"
#include "transaction.h"

#include <QSharedDataPointer>
#include <QDebug>
#include <QDateTime>


namespace OpenTrade {

namespace Internal {
class CanvasPrivate;
}

class OPENTRADE_EXPORT Canvas
{
public:

    Canvas(const QString& name);
    ~Canvas();

    Canvas& operator=(const Canvas &other);
    void swap(Canvas &other) { qSwap(d, other.d); }

#ifdef Q_COMPILER_RVALUE_REFS
    inline Canvas &operator=(Canvas &&other)
    { qSwap(d, other.d); return *this; }
#endif

    bool operator==(const Canvas &other) const;
    inline bool operator!=(const Canvas &other) const { return !(operator==(other)); }

    void add(const BarSeries& series);
    void add(const Indicator& indicator);
    void add(const Order& order);
    void add(const QuoteSeries& quoteSeries);
    void add(const TimeSeries& series);
    void add(const TradeSeries& tradeSeries);
    void add(const Transaction& transaction);
    void cd(int pad);
    void clear();
    void divide(int x, int y);
    void run();
    void setRangeX(const QDateTime& dateTime1, const QDateTime& dateTime2);
    void setRangeX(double minX, double maxX);
    void setRangeY(double minY, double maxY);
    void update();

private:
    QSharedDataPointer<Internal::CanvasPrivate> d;
};

QDebug OPENTRADE_EXPORT operator << (QDebug, const Canvas &canvas);

} // namespace OpenTrade

Q_DECLARE_SHARED(OpenTrade::Canvas)

#endif // __OPENTRADE_CANVAS_H__
