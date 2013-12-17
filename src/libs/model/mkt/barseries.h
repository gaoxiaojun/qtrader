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
#ifndef __OPENTRADE_BARSERIES_H__
#define __OPENTRADE_BARSERIES_H__

#include "opentrade_global.h"
#include "bar.h"
#include "barseries.h"
#include "indicator.h"
#include "timeseries.h"

#include <QSharedDataPointer>
#include <QDebug>
#include <QDateTime>
#include <QString>


namespace OpenTrade {

namespace Internal {
class BarSeriesPrivate;
}

class OPENTRADE_EXPORT BarSeries : public ISeries
{
public:

    BarSeries();
    BarSeries(const QString& name);
    BarSeries(const QString& name, const QString& title);
    ~BarSeries();

    BarSeries& operator=(const BarSeries &other);
    void swap(BarSeries &other) { qSwap(d, other.d); }

#ifdef Q_COMPILER_RVALUE_REFS
    inline BarSeries &operator=(BarSeries &&other)
    { qSwap(d, other.d); return *this; }
#endif

    bool operator==(const BarSeries &other) const;
    inline bool operator!=(const BarSeries &other) const { return !(operator==(other)); }

    void add(const Bar& bar);
    void add(const QDateTime& datetime, double open, double high, double low, double close, long volume, long size);
    void add(BarType barType, long size, const QDateTime& beginTime, const QDateTime& endTime, double open, double high, double low, double close, long volume, long openInt);
    Bar ago(int n);
    void clear();
    BarSeries compress(long newBarSize);
    bool contains(const QDateTime& dateTime);
    bool contains(const Bar& bar);
    Cross crosses(const BarSeries& series, const Bar& bar);
    Cross crosses(const Indicator& indicator, const Bar& bar);
    Cross crosses(const TimeSeries& series, const QDateTime& dateTime);
    bool crossesAbove(const BarSeries& series, const Bar& bar);
    bool crossesAbove(const Indicator& indicator, const Bar& bar);
    bool crossesAbove(const TimeSeries& series, const QDateTime& dateTime);
    bool crossesBelow(const BarSeries& series, const Bar& bar);
    bool crossesBelow(const Indicator& indicator, const Bar& bar);
    bool crossesBelow(const TimeSeries& series, const QDateTime& dateTime);
    QDateTime getDateTime(int index);
    int getIndex(const QDateTime& dateTime);
    BarSeries getRange(const QDateTime& dateTime1, const QDateTime& dateTime2);
    double highestHigh();
    double highestHigh(int nBars);
    double highestHigh(const QDateTime& dateTime1, const QDateTime& dateTime2);
    double highestHigh(int index1, int index2);
    double lowestLow();
    double lowestLow(int nBars);
    double lowestLow(const QDateTime& dateTime1, const QDateTime& dateTime2);
    double lowestLow(int index1, int index2);
    void remove(const QDateTime& dateTime);
    void remove(int index);

    int count() const;

    Bar first() const;

    Bar last() const;

    QString name() const;

private:
    QSharedDataPointer<Internal::BarSeriesPrivate> d;
};

QDebug OPENTRADE_EXPORT operator << (QDebug, const BarSeries &barseries);

} // namespace OpenTrade

Q_DECLARE_SHARED(OpenTrade::BarSeries)

#endif // __OPENTRADE_BARSERIES_H__
