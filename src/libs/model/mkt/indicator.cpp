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
#include "indicator.h"

#include <QSharedData>

namespace OpenTrade {

namespace Internal {

class IndicatorPrivate : public QSharedData
{
public:
    QColor m_color;
    virtual m_int;
    QString m_description;
    virtual m_dateTime;
    virtual m_double;
    virtual m_double;
    virtual m_double;
    virtual m_double;
    virtual m_double;
    virtual m_double;
    virtual m_dateTime;
    QString m_name;
    int m_width;
};

} // namespace Internal

Indicator::Indicator()
{

}

Indicator::~Indicator()
{

}

Indicator& Indicator::operator=(const Indicator &other)
{
    d = other.d;
    return *this;
}

bool Indicator::operator==(const Indicator &other) const
{
    if(d == other.d)
      return true;

    return d->m_color == other.d->m_color &&
           d->m_int == other.d->m_int &&
           d->m_description == other.d->m_description &&
           d->m_dateTime == other.d->m_dateTime &&
           d->m_double == other.d->m_double &&
           d->m_double == other.d->m_double &&
           d->m_double == other.d->m_double &&
           d->m_double == other.d->m_double &&
           d->m_double == other.d->m_double &&
           d->m_double == other.d->m_double &&
           d->m_dateTime == other.d->m_dateTime &&
           d->m_name == other.d->m_name &&
           d->m_width == other.d->m_width;
}

double Indicator::ago(int n)
{

}

bool Indicator::contains(const QDateTime& dateTime)
{

}

bool Indicator::contains(const Bar& bar)
{

}

Cross Indicator::crosses(double level, const Bar& bar)
{

}

Cross Indicator::crosses(const BarSeries& series, const Bar& bar)
{

}

Cross Indicator::crosses(const Indicator& indicator, const Bar& bar)
{

}

Cross Indicator::crosses(const TimeSeries& series, const QDateTime& dateTime)
{

}

Cross Indicator::crosses(const BarSeries& series, const Bar& bar, BarData barData)
{

}

bool Indicator::crossesAbove(double level, const Bar& bar)
{

}

bool Indicator::crossesAbove(const BarSeries& series, const Bar& bar)
{

}

bool Indicator::crossesAbove(const Indicator& indicator, const Bar& bar)
{

}

bool Indicator::crossesAbove(const TimeSeries& series, const QDateTime& dateTime)
{

}

bool Indicator::crossesAbove(const BarSeries& series, const Bar& bar, BarData barData)
{

}

bool Indicator::crossesBelow(double level, const Bar& bar)
{

}

bool Indicator::crossesBelow(const BarSeries& series, const Bar& bar)
{

}

bool Indicator::crossesBelow(const Indicator& indicator, const Bar& bar)
{

}

bool Indicator::crossesBelow(const TimeSeries& series, const QDateTime& dateTime)
{

}

bool Indicator::crossesBelow(const BarSeries& series, const Bar& bar, BarData barData)
{

}

double Indicator::getAsymmetry(const QDateTime& dateTime1, const QDateTime& dateTime2)
{

}

double Indicator::getAsymmetry(int index1, int index2)
{

}

double Indicator::getAutoCorrelation(int lag)
{

}

double Indicator::getAutoCovariance(int lag)
{

}

double Indicator::getCorrelation(const TimeSeries& timeSeries)
{

}

double Indicator::getCovariance(const TimeSeries& timeSeries)
{

}

QDateTime Indicator::getDateTime(int index)
{

}

double Indicator::getExcess(const QDateTime& dateTime1, const QDateTime& dateTime2)
{

}

double Indicator::getExcess(int index1, int index2)
{

}

int Indicator::getIndex(const QDateTime& dateTime)
{

}

double Indicator::getMax(const QDateTime& dateTime1, const QDateTime& dateTime2)
{

}

double Indicator::getMax(int index1, int index2)
{

}

double Indicator::getMedian(const QDateTime& dateTime1, const QDateTime& dateTime2)
{

}

double Indicator::getMedian(int index1, int index2)
{

}

double Indicator::getMean(const QDateTime& dateTime1, const QDateTime& dateTime2)
{

}

double Indicator::getMean(int index1, int index2)
{

}

double Indicator::getMin(const QDateTime& dateTime1, const QDateTime& dateTime2)
{

}

double Indicator::getMin(int index1, int index2)
{

}

double Indicator::getMoment(int k, const QDateTime& dateTime1, const QDateTime& dateTime2)
{

}

double Indicator::getMoment(int k, int index1, int index2)
{

}

double Indicator::getNegativeStdDev(const QDateTime& dateTime1, const QDateTime& dateTime2)
{

}

double Indicator::getNegativeStdDev(int index1, int index2)
{

}

double Indicator::getNegativeVariance(const QDateTime& dateTime1, const QDateTime& dateTime2)
{

}

double Indicator::getNegativeVariance(int index1, int index2)
{

}

double Indicator::getPositiveStdDev(const QDateTime& dateTime1, const QDateTime& dateTime2)
{

}

double Indicator::getPositiveStdDev(int index1, int index2)
{

}

double Indicator::getPositiveVariance(const QDateTime& dateTime1, const QDateTime& dateTime2)
{

}

double Indicator::getPositiveVariance(int index1, int index2)
{

}

double Indicator::getStdDev(const QDateTime& dateTime1, const QDateTime& dateTime2)
{

}

double Indicator::getStdDev(int index1, int index2)
{

}

double Indicator::getSum(const QDateTime& dateTime1, const QDateTime& dateTime2)
{

}

double Indicator::getSum(int index1, int index2)
{

}

double Indicator::getVariance(const QDateTime& dateTime1, const QDateTime& dateTime2)
{

}

double Indicator::getVariance(int index1, int index2)
{

}

QColor Indicator::color() const
{
    return d->m_color;
}

void Indicator::setColor(const QColor& color)
{
    d->m_color = color;
}

virtual Indicator::int() const
{
    return d->m_int;
}

QString Indicator::description() const
{
    return d->m_description;
}

void Indicator::setDescription(const QString& description)
{
    d->m_description = description;
}

virtual Indicator::dateTime() const
{
    return d->m_dateTime;
}

virtual Indicator::double() const
{
    return d->m_double;
}

virtual Indicator::double() const
{
    return d->m_double;
}

virtual Indicator::double() const
{
    return d->m_double;
}

virtual Indicator::double() const
{
    return d->m_double;
}

virtual Indicator::double() const
{
    return d->m_double;
}

virtual Indicator::double() const
{
    return d->m_double;
}

virtual Indicator::dateTime() const
{
    return d->m_dateTime;
}

QString Indicator::name() const
{
    return d->m_name;
}

void Indicator::setName(const QString& name)
{
    d->m_name = name;
}

int Indicator::width() const
{
    return d->m_width;
}

void Indicator::setWidth(int width)
{
    d->m_width = width;
}


} // namespace OpenTrade

QDebug operator<<(QDebug c, const OpenTrade::Indicator &indicator)
{
    c.nospace() << "Indicator("
                << "Color:" << indicator.color() 
                << "int:" << indicator.int() 
                << "Description:" << indicator.description() 
                << "DateTime:" << indicator.dateTime() 
                << "double:" << indicator.double() 
                << "double:" << indicator.double() 
                << "double:" << indicator.double() 
                << "double:" << indicator.double() 
                << "double:" << indicator.double() 
                << "double:" << indicator.double() 
                << "DateTime:" << indicator.dateTime() 
                << "Name:" << indicator.name() 
                << "Width:" << indicator.width() 
                <<')';
    return c.space();
}
