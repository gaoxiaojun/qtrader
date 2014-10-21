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

#include "bar.h"
#include "bar_p.h"
#include "instrument.h"
#include "barmanager.h"

#include <QVector>
#include <QReadWriteLock>

namespace OpenTrade {

namespace Internal {

class BarSeriesPrivate {
public:
    BarSeriesPrivate(const Instrument& inst, qint64 interval)
        :m_instrument(inst), m_interval(interval)
    {}

    QReadWriteLock m_lock;
    Instrument m_instrument;
    qint64 m_interval;
    QDateTime m_begin;

    QVector<Bar> m_bars;
};

} // namespace Internal


BarSeries::BarSeries(QObject *parent, const Instrument& inst, qint64 interval)
    :QObject(parent), d(new Internal::BarSeriesPrivate(inst, interval))
{
}

BarSeries::~BarSeries()
{
    delete d;
}

const Bar& BarSeries::at(int i) const
{
    d->m_lock.lockForRead ();
    const Bar& bar = d->m_bars.at (i);
    d->m_lock.unlock ();
    return bar;
}

void BarSeries::add(const QDateTime& begin, const Bar& bar)
{
    d->m_lock.lockForWrite();

    if (Q_UNLIKELY(d->m_bars.isEmpty ())) {
        d->m_bars.append (bar);
        d->m_begin = begin;
    }
    else {
        int pos = (begin.toMSecsSinceEpoch() -d->m_begin.toMSecsSinceEpoch() )/ d->m_interval;

        if(pos >= 0) {
            int count = d->m_bars.size();

            if(pos > count)
                d->m_bars.insert(count, pos-count, Bar());

            d->m_bars.append (bar);
        }
        else {
            d->m_bars.insert(0, abs(pos), Bar());
            d->m_bars.replace (0, bar);
        }
    }
    d->m_lock.unlock();
}

void BarSeries::add(const QDateTime& begin, double open, double high, double low, double close, double volume)
{
    Bar bar(open, high, low, close, volume);
    bar.d->m_series = this;
    add (begin, bar);
}


int BarSeries::count() const
{
    d->m_lock.lockForRead ();
    int size = d->m_bars.size ();
    d->m_lock.unlock ();
    return size;
}

const QDateTime& BarSeries::begin() const
{
    d->m_lock.lockForRead ();
    QDateTime& result = d->m_begin;
    d->m_lock.unlock ();
    return result;
}
qint64 BarSeries::interval() const
{
    d->m_lock.lockForRead ();
    qint64 result = d->m_interval;
    d->m_lock.unlock ();
    return result;
}
const Instrument& BarSeries::instrument() const
{
    d->m_lock.lockForRead ();
    Instrument& result = d->m_instrument;
    d->m_lock.unlock ();
    return result;
}

} // namespace OpenTrade
