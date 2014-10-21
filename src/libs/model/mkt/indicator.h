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
#ifndef __OPENTRADE_INDICATOR_H__
#define __OPENTRADE_INDICATOR_H__

#include "opentrade_global.h"
#include "bar.h"
#include "barseries.h"
#include "indicator.h"
#include "timeseries.h"

#include <QSharedDataPointer>
#include <QDebug>
#include <QDateTime>
#include <QColor>
#include <QString>


namespace OpenTrade {

namespace Internal {
class IndicatorPrivate;
}

class OPENTRADE_EXPORT Indicator
{
public:

    Indicator();
    ~Indicator();

    Indicator& operator=(const Indicator &other);
    void swap(Indicator &other) { qSwap(d, other.d); }

#ifdef Q_COMPILER_RVALUE_REFS
    inline Indicator &operator=(Indicator &&other)
    { qSwap(d, other.d); return *this; }
#endif

    bool operator==(const Indicator &other) const;
    inline bool operator!=(const Indicator &other) const { return !(operator==(other)); }

    double ago(int n);
    bool contains(const QDateTime& dateTime);
    bool contains(const Bar& bar);
    Cross crosses(double level, const Bar& bar);
    Cross crosses(const BarSeries& series, const Bar& bar);
    Cross crosses(const Indicator& indicator, const Bar& bar);
    Cross crosses(const TimeSeries& series, const QDateTime& dateTime);
    Cross crosses(const BarSeries& series, const Bar& bar, BarData barData);
    bool crossesAbove(double level, const Bar& bar);
    bool crossesAbove(const BarSeries& series, const Bar& bar);
    bool crossesAbove(const Indicator& indicator, const Bar& bar);
    bool crossesAbove(const TimeSeries& series, const QDateTime& dateTime);
    bool crossesAbove(const BarSeries& series, const Bar& bar, BarData barData);
    bool crossesBelow(double level, const Bar& bar);
    bool crossesBelow(const BarSeries& series, const Bar& bar);
    bool crossesBelow(const Indicator& indicator, const Bar& bar);
    bool crossesBelow(const TimeSeries& series, const QDateTime& dateTime);
    bool crossesBelow(const BarSeries& series, const Bar& bar, BarData barData);
    double getAsymmetry(const QDateTime& dateTime1, const QDateTime& dateTime2);
    double getAsymmetry(int index1, int index2);
    double getAutoCorrelation(int lag);
    double getAutoCovariance(int lag);
    double getCorrelation(const TimeSeries& timeSeries);
    double getCovariance(const TimeSeries& timeSeries);
    QDateTime getDateTime(int index);
    double getExcess(const QDateTime& dateTime1, const QDateTime& dateTime2);
    double getExcess(int index1, int index2);
    int getIndex(const QDateTime& dateTime);
    double getMax(const QDateTime& dateTime1, const QDateTime& dateTime2);
    double getMax(int index1, int index2);
    double getMedian(const QDateTime& dateTime1, const QDateTime& dateTime2);
    double getMedian(int index1, int index2);
    double getMean(const QDateTime& dateTime1, const QDateTime& dateTime2);
    double getMean(int index1, int index2);
    double getMin(const QDateTime& dateTime1, const QDateTime& dateTime2);
    double getMin(int index1, int index2);
    double getMoment(int k, const QDateTime& dateTime1, const QDateTime& dateTime2);
    double getMoment(int k, int index1, int index2);
    double getNegativeStdDev(const QDateTime& dateTime1, const QDateTime& dateTime2);
    double getNegativeStdDev(int index1, int index2);
    double getNegativeVariance(const QDateTime& dateTime1, const QDateTime& dateTime2);
    double getNegativeVariance(int index1, int index2);
    double getPositiveStdDev(const QDateTime& dateTime1, const QDateTime& dateTime2);
    double getPositiveStdDev(int index1, int index2);
    double getPositiveVariance(const QDateTime& dateTime1, const QDateTime& dateTime2);
    double getPositiveVariance(int index1, int index2);
    double getStdDev(const QDateTime& dateTime1, const QDateTime& dateTime2);
    double getStdDev(int index1, int index2);
    double getSum(const QDateTime& dateTime1, const QDateTime& dateTime2);
    double getSum(int index1, int index2);
    double getVariance(const QDateTime& dateTime1, const QDateTime& dateTime2);
    double getVariance(int index1, int index2);

    QColor color() const;
    void setColor(const QColor& color);

    virtual int() const;

    QString description() const;
    void setDescription(const QString& description);

    virtual dateTime() const;

    virtual double() const;

    virtual double() const;

    virtual double() const;

    virtual double() const;

    virtual double() const;

    virtual double() const;

    virtual dateTime() const;

    QString name() const;
    void setName(const QString& name);

    int width() const;
    void setWidth(int width);

private:
    QSharedDataPointer<Internal::IndicatorPrivate> d;
};

QDebug OPENTRADE_EXPORT operator << (QDebug, const Indicator &indicator);

} // namespace OpenTrade

Q_DECLARE_SHARED(OpenTrade::Indicator)

#endif // __OPENTRADE_INDICATOR_H__
