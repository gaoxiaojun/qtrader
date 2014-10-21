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
#include "marketdataprovider.h"

#include <QSharedData>

namespace OpenTrade {

namespace Internal {

class MarketDataProviderPrivate : public QSharedData
{
public:
    BarFactory m_barFactory;
    MarketDataFilter m_filter;
};

} // namespace Internal

MarketDataProvider::~MarketDataProvider()
{

}

MarketDataProvider& MarketDataProvider::operator=(const MarketDataProvider &other)
{
    d = other.d;
    return *this;
}

bool MarketDataProvider::operator==(const MarketDataProvider &other) const
{
    if(d == other.d)
      return true;

    return d->m_barFactory == other.d->m_barFactory &&
           d->m_filter == other.d->m_filter;
}

void MarketDataProvider::connect()
{

}

void MarketDataProvider::disconnect()
{

}

BarFactory MarketDataProvider::barFactory() const
{
    return d->m_barFactory;
}

void MarketDataProvider::setBarFactory(const BarFactory& barfactory)
{
    d->m_barFactory = barfactory;
}

MarketDataFilter MarketDataProvider::filter() const
{
    return d->m_filter;
}

void MarketDataProvider::setFilter(const MarketDataFilter& filter)
{
    d->m_filter = filter;
}


} // namespace OpenTrade

QDebug operator<<(QDebug c, const OpenTrade::MarketDataProvider &marketdataprovider)
{
    c.nospace() << "MarketDataProvider("
                << "BarFactory:" << marketdataprovider.barFactory() 
                << "Filter:" << marketdataprovider.filter() 
                <<')';
    return c.space();
}
