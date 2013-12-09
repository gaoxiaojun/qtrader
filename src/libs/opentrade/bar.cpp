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

namespace OpenTradeModel {

namespace Internal {
class BarPrivate {
public:
    BarPrivate(const QDateTime& begin, double open, double high, double low, double close, double volume)
        :m_begin(begin), m_open(open), m_high(high), m_low(low), m_close(close), m_volume(volume)
    {}

public:
    QDateTime m_begin;
    double m_open;
    double m_high;
    double m_low;
    double m_close;
    double m_volume;
};

} // namespace Internal

Bar::Bar(const QDateTime& begin, double open, double high, double low, double close, double volume)
    : d(new Internal::BarPrivate(begin, open, high, low, close, volume))
{
}

Bar::~Bar()
{
    delete d;
}

QDateTime Bar::begin() const
{
    return d->m_begin;
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

} // namespace OpenTradeModel
