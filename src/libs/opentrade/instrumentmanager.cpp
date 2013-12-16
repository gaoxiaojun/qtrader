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
#include "instrumentmanager.h"

#include <QSharedData>

namespace OpenTrade {

namespace Internal {

class InstrumentManagerPrivate : public QSharedData
{
public:
    static m_instrumentList;
};

} // namespace Internal

InstrumentManager::~InstrumentManager()
{

}

InstrumentManager& InstrumentManager::operator=(const InstrumentManager &other)
{
    d = other.d;
    return *this;
}

bool InstrumentManager::operator==(const InstrumentManager &other) const
{
    if(d == other.d)
      return true;

    return d->m_instrumentList == other.d->m_instrumentList;
}

void InstrumentManager::remove(const QString& symbol)
{

}

void InstrumentManager::remove(const Instrument& instrument)
{

}

static InstrumentManager::instrumentList() const
{
    return d->m_instrumentList;
}


} // namespace OpenTrade

QDebug operator<<(QDebug c, const OpenTrade::InstrumentManager &instrumentmanager)
{
    c.nospace() << "InstrumentManager("
                << "InstrumentList:" << instrumentmanager.instrumentList() 
                <<')';
    return c.space();
}
