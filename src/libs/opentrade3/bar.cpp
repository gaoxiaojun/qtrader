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
#include "bar_p.h"

#include "barmanager.h"

using namespace OpenTrade;

Bar::Bar() :d(new Internal::BarPrivate())
{
}

Bar::Bar(double open, double high, double low, double close, double volume, double openint)
    : d(new Internal::BarPrivate(open, high, low, close, volume, openint))
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

/*QDateTime Bar::begin() const
{
    Q_ASSERT(d->m_series);

    //return d-->begin();
}*/

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

double Bar::tickVol() const
{
    return d->m_tickVol;
}

bool Bar::isValid () const
{
    return d->isValid ();
}

double Bar::average() const
{
    return (d->m_high + d->m_low + d->m_close + d->m_high) / 4;
}

double Bar::typical() const
{
    return (d->m_high + d->m_low + d->m_close) / 3;
}

double Bar::median() const
{
    return (d->m_high + d->m_low) / 2;
}

double Bar::weighted() const
{
    return (d->m_high + d->m_low + 2* d->m_close) / 4;
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
    return d->m_open == other.d->m_open &&
            d->m_high == other.d->m_high &&
            d->m_low == other.d->m_low &&
            d->m_close == other.d->m_close &&
            d->m_volume == other.d->m_volume;
}

QDebug operator<<(QDebug c, const OpenTrade::Bar &bar)
{
    c.nospace() << "Bar("
                //<< "Time:" << bar.datetime()
                << "Open:" << bar.open()
                << "High:" << bar.high()
                << "Low:" << bar.low()
                << "Close:" << bar.close()
                << "Volume:" << bar.volume()
                <<')';
    return c.space();
}
