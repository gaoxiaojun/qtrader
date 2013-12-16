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
#include "barseries.h"

#include <QSharedData>

namespace OpenTrade {

namespace Internal {

class BarSeriesPrivate : public QSharedData
{
public:
    int m_count;
    Bar m_first;
    Bar m_last;
    QString m_name;
};

} // namespace Internal

BarSeries::BarSeries()
{

}

BarSeries::BarSeries(const QString& name)
{

}

BarSeries::BarSeries(const QString& name, const QString& title)
{

}

BarSeries::~BarSeries()
{

}

BarSeries& BarSeries::operator=(const BarSeries &other)
{
    d = other.d;
    return *this;
}

bool BarSeries::operator==(const BarSeries &other) const
{
    if(d == other.d)
      return true;

    return d->m_count == other.d->m_count &&
           d->m_first == other.d->m_first &&
           d->m_last == other.d->m_last &&
           d->m_name == other.d->m_name;
}

void BarSeries::add(const Bar& bar)
{

}

void BarSeries::add(const QDateTime& datetime, double open, double high, double low, double close, long volume, long size)
{

}

void BarSeries::add(BarType barType, long size, const QDateTime& beginTime, const QDateTime& endTime, double open, double high, double low, double close, long volume, long openInt)
{

}

Bar BarSeries::ago(int n)
{

}

void BarSeries::clear()
{

}

BarSeries BarSeries::compress(long newBarSize)
{

}

bool BarSeries::contains(const QDateTime& dateTime)
{

}

bool BarSeries::contains(const Bar& bar)
{

}

Cross BarSeries::crosses(const BarSeries& series, const Bar& bar)
{

}

Cross BarSeries::crosses(const Indicator& indicator, const Bar& bar)
{

}

Cross BarSeries::crosses(const TimeSeries& series, const QDateTime& dateTime)
{

}

bool BarSeries::crossesAbove(const BarSeries& series, const Bar& bar)
{

}

bool BarSeries::crossesAbove(const Indicator& indicator, const Bar& bar)
{

}

bool BarSeries::crossesAbove(const TimeSeries& series, const QDateTime& dateTime)
{

}

bool BarSeries::crossesBelow(const BarSeries& series, const Bar& bar)
{

}

bool BarSeries::crossesBelow(const Indicator& indicator, const Bar& bar)
{

}

bool BarSeries::crossesBelow(const TimeSeries& series, const QDateTime& dateTime)
{

}

QDateTime BarSeries::getDateTime(int index)
{

}

int BarSeries::getIndex(const QDateTime& dateTime)
{

}

BarSeries BarSeries::getRange(const QDateTime& dateTime1, const QDateTime& dateTime2)
{

}

double BarSeries::highestHigh()
{

}

double BarSeries::highestHigh(int nBars)
{

}

double BarSeries::highestHigh(const QDateTime& dateTime1, const QDateTime& dateTime2)
{

}

double BarSeries::highestHigh(int index1, int index2)
{

}

double BarSeries::lowestLow()
{

}

double BarSeries::lowestLow(int nBars)
{

}

double BarSeries::lowestLow(const QDateTime& dateTime1, const QDateTime& dateTime2)
{

}

double BarSeries::lowestLow(int index1, int index2)
{

}

void BarSeries::remove(const QDateTime& dateTime)
{

}

void BarSeries::remove(int index)
{

}

int BarSeries::count() const
{
    return d->m_count;
}

Bar BarSeries::first() const
{
    return d->m_first;
}

Bar BarSeries::last() const
{
    return d->m_last;
}

QString BarSeries::name() const
{
    return d->m_name;
}


} // namespace OpenTrade

QDebug operator<<(QDebug c, const OpenTrade::BarSeries &barseries)
{
    c.nospace() << "BarSeries("
                << "Count:" << barseries.count() 
                << "First:" << barseries.first() 
                << "Last:" << barseries.last() 
                << "Name:" << barseries.name() 
                <<')';
    return c.space();
}
