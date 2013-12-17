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
#include "openquant.h"

#include <QSharedData>

namespace OpenTrade {

namespace Internal {

class OpenQuantPrivate : public QSharedData
{
public:
    static m_barSeriesList;
    static m_bool;
    static m_instrumentList;
    static m_orderList;
};

} // namespace Internal

OpenQuant::OpenQuant()
{

}

OpenQuant::~OpenQuant()
{

}

OpenQuant& OpenQuant::operator=(const OpenQuant &other)
{
    d = other.d;
    return *this;
}

bool OpenQuant::operator==(const OpenQuant &other) const
{
    if(d == other.d)
      return true;

    return d->m_barSeriesList == other.d->m_barSeriesList &&
           d->m_bool == other.d->m_bool &&
           d->m_instrumentList == other.d->m_instrumentList &&
           d->m_orderList == other.d->m_orderList;
}

static OpenQuant::barSeriesList() const
{
    return d->m_barSeriesList;
}

static OpenQuant::bool() const
{
    return d->m_bool;
}

void OpenQuant::setBool(const static& bool)
{
    d->m_bool = bool;
}

static OpenQuant::instrumentList() const
{
    return d->m_instrumentList;
}

static OpenQuant::orderList() const
{
    return d->m_orderList;
}


} // namespace OpenTrade

QDebug operator<<(QDebug c, const OpenTrade::OpenQuant &openquant)
{
    c.nospace() << "OpenQuant("
                << "BarSeriesList:" << openquant.barSeriesList() 
                << "bool:" << openquant.bool() 
                << "InstrumentList:" << openquant.instrumentList() 
                << "OrderList:" << openquant.orderList() 
                <<')';
    return c.space();
}
