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
#include "timeseries.h"

#include <QSharedData>

namespace OpenTrade {

namespace Internal {

class TimeSeriesPrivate : public QSharedData
{
public:
    QColor m_color;
    int m_count;
    double m_last;
    QString m_name;
    int m_width;
};

} // namespace Internal

TimeSeries::TimeSeries()
{

}

TimeSeries::TimeSeries(const QString& name)
{

}

TimeSeries::TimeSeries(const QString& name, const QColor& color)
{

}

TimeSeries::TimeSeries(const QString& name, const QString& title)
{

}

TimeSeries::TimeSeries(const QString& name, const QString& title, const QColor& color)
{

}

TimeSeries::~TimeSeries()
{

}

TimeSeries& TimeSeries::operator=(const TimeSeries &other)
{
    d = other.d;
    return *this;
}

bool TimeSeries::operator==(const TimeSeries &other) const
{
    if(d == other.d)
      return true;

    return d->m_color == other.d->m_color &&
           d->m_count == other.d->m_count &&
           d->m_last == other.d->m_last &&
           d->m_name == other.d->m_name &&
           d->m_width == other.d->m_width;
}

void TimeSeries::add(const QDateTime& dateTime, double data)
{

}

double TimeSeries::ago(int length)
{

}

bool TimeSeries::contains(const QDateTime& dateTime)
{

}

Cross TimeSeries::crosses(double level, const Bar& bar)
{

}

Cross TimeSeries::crosses(const BarSeries& series, const Bar& bar)
{

}

Cross TimeSeries::crosses(const Indicator& indicator, const QDateTime& dateTime)
{

}

Cross TimeSeries::crosses(const TimeSeries& series, const QDateTime& dateTime)
{

}

Cross TimeSeries::crosses(const BarSeries& series, const Bar& bar, BarData barData)
{

}

bool TimeSeries::crossesAbove(double level, const Bar& bar)
{

}

bool TimeSeries::crossesAbove(const Indicator& indicator, const QDateTime& dateTime)
{

}

bool TimeSeries::crossesAbove(const TimeSeries& series, const QDateTime& dateTime)
{

}

bool TimeSeries::crossesAbove(const BarSeries& series, const Bar& bar, BarData barData)
{

}

bool TimeSeries::crossesBelow(double level, const Bar& bar)
{

}

bool TimeSeries::crossesBelow(const Indicator& indicator, const QDateTime& dateTime)
{

}

bool TimeSeries::crossesBelow(const TimeSeries& series, const QDateTime& dateTime)
{

}

bool TimeSeries::crossesBelow(const BarSeries& series, const Bar& bar, BarData barData)
{

}

double TimeSeries::getAsymmetry(const QDateTime& dateTime1, const QDateTime& dateTime2)
{

}

double TimeSeries::getAsymmetry(int index1, int index2)
{

}

double TimeSeries::getAutoCorrelation(int lag)
{

}

double TimeSeries::getAutoCovariance(int lag)
{

}

double TimeSeries::getCorrelation(const TimeSeries& timeSeries)
{

}

double TimeSeries::getCovariance(const TimeSeries& timeSeries)
{

}

QDateTime TimeSeries::getDateTime(int index)
{

}

double TimeSeries::getExcess(const QDateTime& dateTime1, const QDateTime& dateTime2)
{

}

double TimeSeries::getExcess(int index1, int index2)
{

}

int TimeSeries::getIndex(const QDateTime& dateTime)
{

}

double TimeSeries::getMax(const QDateTime& dateTime1, const QDateTime& dateTime2)
{

}

double TimeSeries::getMax(int index1, int index2)
{

}

double TimeSeries::getMean(const QDateTime& dateTime1, const QDateTime& dateTime2)
{

}

double TimeSeries::getMean(int index1, int index2)
{

}

double TimeSeries::getMedian(const QDateTime& dateTime1, const QDateTime& dateTime2)
{

}

double TimeSeries::getMedian(int index1, int index2)
{

}

double TimeSeries::getMin(const QDateTime& dateTime1, const QDateTime& dateTime2)
{

}

double TimeSeries::getMin(int index1, int index2)
{

}

double TimeSeries::getMoment(int k, const QDateTime& dateTime1, const QDateTime& dateTime2)
{

}

double TimeSeries::getMoment(int k, int index1, int index2)
{

}

double TimeSeries::getNegativeStdDev(const QDateTime& dateTime1, const QDateTime& dateTime2)
{

}

double TimeSeries::getNegativeStdDev(int index1, int index2)
{

}

double TimeSeries::getNegativeVariance(const QDateTime& dateTime1, const QDateTime& dateTime2)
{

}

double TimeSeries::getNegativeVariance(int index1, int index2)
{

}

double TimeSeries::getPositiveStdDev(const QDateTime& dateTime1, const QDateTime& dateTime2)
{

}

double TimeSeries::getPositiveStdDev(int index1, int index2)
{

}

double TimeSeries::getPositiveVariance(const QDateTime& dateTime1, const QDateTime& dateTime2)
{

}

double TimeSeries::getPositiveVariance(int index1, int index2)
{

}

double TimeSeries::getStdDev(const QDateTime& dateTime1, const QDateTime& dateTime2)
{

}

double TimeSeries::getStdDev(int index1, int index2)
{

}

double TimeSeries::getSum(const QDateTime& dateTime1, const QDateTime& dateTime2)
{

}

double TimeSeries::getSum(int index1, int index2)
{

}

double TimeSeries::getVariance(const QDateTime& dateTime1, const QDateTime& dateTime2)
{

}

double TimeSeries::getVariance(int index1, int index2)
{

}

void TimeSeries::remove(const QDateTime& dateTime)
{

}

void TimeSeries::remove(int index)
{

}

QColor TimeSeries::color() const
{
    return d->m_color;
}

void TimeSeries::setColor(const QColor& color)
{
    d->m_color = color;
}

int TimeSeries::count() const
{
    return d->m_count;
}

double TimeSeries::last() const
{
    return d->m_last;
}

QString TimeSeries::name() const
{
    return d->m_name;
}

int TimeSeries::width() const
{
    return d->m_width;
}

void TimeSeries::setWidth(int width)
{
    d->m_width = width;
}


} // namespace OpenTrade

QDebug operator<<(QDebug c, const OpenTrade::TimeSeries &timeseries)
{
    c.nospace() << "TimeSeries("
                << "Color:" << timeseries.color() 
                << "Count:" << timeseries.count() 
                << "Last:" << timeseries.last() 
                << "Name:" << timeseries.name() 
                << "Width:" << timeseries.width() 
                <<')';
    return c.space();
}
