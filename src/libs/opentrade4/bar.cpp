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
#include "bar.h"

#include <QSharedData>

namespace OpenTrade {

namespace Internal {

class BarPrivate : public QSharedData
{
public:
    QDateTime m_beginTime;
    double m_close;
    QDateTime m_dateTime;
    qint64 m_duration;
    QDateTime m_endTime;
    double m_high;
    bool m_isComplete;
    double m_low;
    double m_median;
    double m_open;
    double m_openInt;
    int m_size;
    Bar::BarType m_type;
    double m_volume;
};

} // namespace Internal

Bar::Bar(const QDateTime& dateTime, double open, double high, double low, double close, long volume, long size)
    :d(new BarPrivate)
{
    d->m_dateTime = dateTime;
    d->m_open = open;
    d->m_close = close;
    d->m_high = high;
    d->m_low = low;
    d->m_volume = volume;
    d->m_size = size;
}

Bar::Bar(const Bar& bar)
{

}

Bar::~Bar()
{

}

Bar& Bar::operator=(const Bar &other)
{
    d = other.d;
    return *this;
}

bool Bar::operator==(const Bar &other) const
{
    if(d == other.d)
      return true;

    return d->m_average == other.d->m_average &&
           d->m_beginTime == other.d->m_beginTime &&
           d->m_close == other.d->m_close &&
           d->m_dateTime == other.d->m_dateTime &&
           d->m_duration == other.d->m_duration &&
           d->m_endTime == other.d->m_endTime &&
           d->m_high == other.d->m_high &&
           d->m_isComplete == other.d->m_isComplete &&
           d->m_low == other.d->m_low &&
           d->m_median == other.d->m_median &&
           d->m_open == other.d->m_open &&
           d->m_openInt == other.d->m_openInt &&
           d->m_size == other.d->m_size &&
           d->m_type == other.d->m_type &&
           d->m_typical == other.d->m_typical &&
           d->m_volume == other.d->m_volume &&
           d->m_weighted == other.d->m_weighted;
}

double Bar::average() const
{
    return (d->m_open + d->m_high + d->m_low + d->m_close) / 4.0;
}

QDateTime Bar::beginTime() const
{
    return d->m_beginTime;
}

double Bar::close() const
{
    return d->m_close;
}

QDateTime Bar::dateTime() const
{
    return d->m_dateTime;
}

qint64 Bar::duration() const
{
    return d->m_duration;
}

QDateTime Bar::endTime() const
{
    return d->m_endTime;
}

double Bar::high() const
{
    return d->m_high;
}

bool Bar::isComplete() const
{
    return d->m_isComplete;
}

double Bar::low() const
{
    return d->m_low;
}

double Bar::median() const
{
    return d->m_median;
}

double Bar::open() const
{
    return d->m_open;
}

double Bar::openInt() const
{
    return d->m_openInt;
}

int Bar::size() const
{
    return d->m_size;
}

Bar::BarType Bar::type() const
{
    return d->m_type;
}

double Bar::typical() const
{
    return (d->m_high + d->m_low + d->m_close) / 3.0;
}

double Bar::volume() const
{
    return d->m_volume;
}

double Bar::weighted() const
{
    return (d->m_high + d->m_low + 2.0 * d->m_close) / 4.0;
}

double Bar::operator[](BarData data) const
{
    switch (data) {
    case Close:
        return d->m_close;
    case Open:
        return d->m_open;
    case High:
        return d->m_high;
    case Low:
        return d->m_low;
    case Median:
        return median();
    case Typical:
        return typical();
    case Weighted:
        return weighted();
    case Volume:
        return d->m_volume;
    case OpenInt:
        return d->m_openInt;
    }
}

} // namespace OpenTrade

QDebug operator<<(QDebug c, const OpenTrade::Bar &bar)
{
    c.nospace() << "Bar("
                << "Average:" << bar.average() 
                << "BeginTime:" << bar.beginTime() 
                << "Close:" << bar.close() 
                << "DateTime:" << bar.dateTime() 
                << "Duration:" << bar.duration() 
                << "EndTime:" << bar.endTime() 
                << "High:" << bar.high() 
                << "IsComplete:" << bar.isComplete() 
                << "Low:" << bar.low() 
                << "Median:" << bar.median() 
                << "Open:" << bar.open() 
                << "OpenInt:" << bar.openInt() 
                << "Size:" << bar.size() 
                << "Type:" << bar.type() 
                << "Typical:" << bar.typical() 
                << "Volume:" << bar.volume() 
                << "Weighted:" << bar.weighted() 
                <<')';
    return c.space();
}
