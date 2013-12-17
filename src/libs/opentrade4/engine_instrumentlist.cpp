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
#include "engine_instrumentlist.h"

#include <QSharedData>

namespace OpenTrade {

namespace Internal {

class Engine_InstrumentListPrivate : public QSharedData
{
public:
    int m_count;
};

} // namespace Internal

Engine_InstrumentList::~Engine_InstrumentList()
{

}

Engine_InstrumentList& Engine_InstrumentList::operator=(const Engine_InstrumentList &other)
{
    d = other.d;
    return *this;
}

bool Engine_InstrumentList::operator==(const Engine_InstrumentList &other) const
{
    if(d == other.d)
      return true;

    return d->m_count == other.d->m_count;
}

void Engine_InstrumentList::add(const QString& symbol)
{

}

void Engine_InstrumentList::add(const Instrument& instrument)
{

}

void Engine_InstrumentList::clear()
{

}

bool Engine_InstrumentList::contains(const QString& name)
{

}

void Engine_InstrumentList::remove(const QString& symbol)
{

}

void Engine_InstrumentList::remove(const Instrument& instrument)
{

}

bool Engine_InstrumentList::tryGetValue(const QString& name, const Instrument& instrument)
{

}

int Engine_InstrumentList::count() const
{
    return d->m_count;
}


} // namespace OpenTrade

QDebug operator<<(QDebug c, const OpenTrade::Engine_InstrumentList &engine_instrumentlist)
{
    c.nospace() << "Engine_InstrumentList("
                << "Count:" << engine_instrumentlist.count() 
                <<')';
    return c.space();
}
