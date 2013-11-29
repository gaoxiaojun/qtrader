/****************************************************************************
**
** Copyright (C) 2013 Xiaojun Gao
** Contact: http://www.dailypips.org/legal
**
** This file is part of QTrader.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Digia gives you certain additional
** rights.  These rights are described in the Digia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
****************************************************************************/

#include "bar.h"

namespace OpenTrade {

namespace Internal {

class BarPrivate : public QSharedData
{
public:
    BarPrivate(const QDateTime& begin, const QDateTime& current, int size,
               Bar::BarType type, double open, double high, double low, double close,
               double volume, double openInt, unsigned int providerId) :
        m_begin(begin), m_current(current), m_size(size), m_type(type),
        m_open(open), m_high(high), m_low(low), m_close(close), m_volume(volume),
        m_openInt(openInt), m_providerId(providerId)
    {}

    QDateTime m_begin;
    QDateTime m_current;
    /*
     * Bar size meaning depends on the bar type
     * - Time bars: size - number of seconds "inside" the bar, 86400 in the case of a Daily bar, 60 * 60 = 3600 in the case of a bar from 10:00 to 11:00, etc
     * - Tick bars: size - number of ticks "inside" the bar.
     * - Volume bars: size - total volume of a bar.
     * - Range bars: size - bar range (high - low) multiplied by 10000.
     */
    int m_size;
    Bar::BarType m_type;

    double m_open;
    double m_high;
    double m_low;
    double m_close;
    double m_volume;
    double m_openInt;
    unsigned int m_providerId;
};

} // namepsace Internal

/*Bar::Bar() :
    d(new Internal::BarPrivate(QDateTime(), QDateTime(), 0, NoneBar,
                               0, 0, 0, 0, 0, 0, 0))
{
}*/

Bar::Bar (const QDateTime& begin, const QDateTime& current, int size,
          Bar::BarType type, double open, double high, double low, double close,
          double volume, double openInt, unsigned int providerId) :
    d(new Internal::BarPrivate(begin, current, size, type, open, high, low, close,
                               volume, openInt, providerId))
{

}

Bar::Bar(const Bar &other) :
    d(other.d)
{
}

Bar::~Bar()
{
    d = 0;
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
    return d->m_begin == other.d->m_begin &&
            d->m_current == other.d->m_current &&
            d->m_size == other.d->m_size &&
            d->m_type == other.d->m_type &&
            d->m_open == other.d->m_open &&
            d->m_high == other.d->m_high &&
            d->m_low == other.d->m_low &&
            d->m_close == other.d->m_close &&
            d->m_volume == other.d->m_volume &&
            d->m_openInt == other.d->m_openInt &&
            d->m_providerId == other.d->m_providerId;
}

double Bar::open() const
{
    return d->m_open;
}

double Bar::high() const
{
    return d->m_high;
}

double Bar::low() const
{
    return d->m_low;
}

double Bar::close() const
{
    return d->m_close;
}

double Bar::volume() const
{
    return d->m_volume;
}

double Bar::openInt() const
{
    return d->m_openInt;
}

unsigned int Bar::providerId() const
{
    return d->m_providerId;
}

QDateTime Bar::begin() const
{
    return d->m_begin;
}

QDateTime Bar::current() const
{
    return d->m_current;
}

QDateTime Bar::end() const
{
    QDateTime endTime(d->m_begin);
    endTime.addMSecs (d->m_size);
    return endTime;
}

bool Bar::IsComplete() const
{
    return d->m_current > end();
}

double Bar::typical() const
{
    return (d->m_high + d->m_low + d->m_close) / 3;
}

double Bar::weighted() const
{
    return (d->m_high + d->m_low + 2* d->m_close) / 4;
}

double Bar::average() const
{
    return (d->m_high + d->m_low + d->m_close + d->m_high) / 4;
}

double Bar::median() const
{
    return (d->m_high + d->m_low) / 2;
}

double Bar::operator [] (Bar::BarData barData) const
{
    switch(barData) {
    case Bar::Close:
        return d->m_close;
    case Bar::Open:
        return d->m_open;
    case Bar::Hight:
        return d->m_high;
    case Bar::Low:
        return d->m_low;
    case Bar::Median:
        return median();
    case Bar::Typical:
        return typical();
    case Bar::Weighted:
        return weighted();
    case Bar::Average:
        return average();
    case Bar::Volume:
        return d->m_volume;
    case Bar::OpenInt:
        return d->m_openInt;
    }
}

} //namespace OpenTrade

QDebug operator<<(QDebug s, const OpenTrade::Bar &bar)
{
    s.nospace() << "Bar("
                << "Begin:" << bar.begin()
                << "Current:" << bar.current()
                << "End:" << bar.end()
                << "Open:" << bar.open()
                << "Close:" << bar.close()
                << "High:" << bar.high()
                << "Low:" << bar.low()
                << "Volume:" << bar.volume()
                << "OpenInt:" << bar.openInt()
                << "ProviderId:" << bar.providerId()
                <<')';
    return s.space();
}

