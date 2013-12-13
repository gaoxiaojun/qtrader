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

Bar::Bar(double open, double high, double low, double close, double volume)
    : d(new Internal::BarPrivate(open, high, low, close, volume))
{
}

Bar::~Bar()
{
    delete d;
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
