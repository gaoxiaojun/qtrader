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
#include "trade.h"

#include <QSharedData>

namespace OpenTrade {

namespace Internal {

class TradePrivate : public QSharedData
{
public:
    QDateTime m_dateTime;
    double m_price;
    int m_providerId;
    int m_size;
};

} // namespace Internal

Trade::Trade(const QDateTime& dateTime, double price, int size)
{

}

Trade::~Trade()
{

}

Trade& Trade::operator=(const Trade &other)
{
    d = other.d;
    return *this;
}

bool Trade::operator==(const Trade &other) const
{
    if(d == other.d)
      return true;

    return d->m_dateTime == other.d->m_dateTime &&
           d->m_price == other.d->m_price &&
           d->m_providerId == other.d->m_providerId &&
           d->m_size == other.d->m_size;
}

QDateTime Trade::dateTime() const
{
    return d->m_dateTime;
}

double Trade::price() const
{
    return d->m_price;
}

int Trade::providerId() const
{
    return d->m_providerId;
}

int Trade::size() const
{
    return d->m_size;
}


} // namespace OpenTrade

QDebug operator<<(QDebug c, const OpenTrade::Trade &trade)
{
    c.nospace() << "Trade("
                << "DateTime:" << trade.dateTime() 
                << "Price:" << trade.price() 
                << "ProviderId:" << trade.providerId() 
                << "Size:" << trade.size() 
                <<')';
    return c.space();
}
