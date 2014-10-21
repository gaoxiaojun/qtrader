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

#include "barmanager.h"

#include "bar.h"
#include "barseries.h"
#include "instrument.h"

#include <QHash>

namespace OpenTrade  {

static BarManager* m_instance = 0;

namespace Internal {

class BarManagerPrivate {
public:
    BarManagerPrivate() {}
    inline QString key(const Instrument& inst, qint64 interval) const
    {
        return inst.symbol() + interval;
    }

    inline QString key(BarSeries *series) const
    {
        return key(series->instrument(), series->interval());
    }

public:
    QHash<QString, BarSeries *> m_seriesList;
};

} // namespace Internal

BarManager::BarManager(QObject *parent) :
    QObject(parent), d(new Internal::BarManagerPrivate())
{
    m_instance = this;
}

BarManager::~BarManager()
{
    if(m_instance) {
        foreach(BarSeries *p, d->m_seriesList)
            delete p;
        d->m_seriesList.clear();
        delete d;
    }
    m_instance = 0;
}

BarManager* BarManager::instance()
{
    return m_instance;
}

void BarManager::addBarSeries(BarSeries* series)
{
    Q_ASSERT(m_instance != 0);
    Q_ASSERT(m_instance->containers(series));
    QString key = m_instance->d->key (series);
    m_instance->d->m_seriesList.insert (key, series);
}

bool BarManager::containers(const Instrument& inst, qint64 interval)
{
    Q_ASSERT(m_instance != 0);
    QString key = m_instance->d->key (inst, interval);
    return m_instance->d->m_seriesList.contains (key);
}

bool BarManager::containers(BarSeries* series)
{
    Q_ASSERT(m_instance != 0);
    QString key = m_instance->d->key (series);
    return m_instance->d->m_seriesList.contains(key);
}

BarSeries* BarManager::createBarSeries(const Instrument& inst, qint64 interval)
{
    Q_ASSERT(m_instance != 0);
    QString key = m_instance->d->key (inst, interval);
    Q_ASSERT(m_instance->d->m_seriesList.contains (key));
    BarSeries* bs = new BarSeries(0, inst, interval);
    m_instance->addBarSeries (bs);
    return bs;
}

BarSeries* BarManager::getBarSeries(const Instrument&inst, qint64 interval)
{
    Q_ASSERT(m_instance != 0);
    QString key = m_instance->d->key (inst, interval);
    if (m_instance->d->m_seriesList.contains (key))
       return m_instance->d->m_seriesList.value (key);
    else
       return m_instance->createBarSeries (inst, interval);
}

BarSeries* BarManager::addBar(const Instrument& inst, qint64 interval, const QDateTime& begin,
                   double open, double high, double low, double close, double volume)
{
    BarSeries* series = getBarSeries (inst, interval);
    series->add (begin, open, high, low, close, volume);
    return series;
}

} // namespace OpenTrade
