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

class TradePrivate: public QSharedData
{
public:
    inline TradePrivate(const QDateTime& dt, double price, double size) :
        m_stamp(dt), m_price(price), m_size(size)
    {}

    QDateTime m_stamp;
    double m_price;
    double m_size;
};

} // namespace Internal

Trade::Trade(const QDateTime& dt, double price, double size) :
    d(new Internal::TradePrivate(dt, price, size))
{
}

Trade::Trade(const Trade &other) :
    d(other.d)
{
}

Trade::~Trade()
{
    d = 0;
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
    return d->m_stamp == other.d->m_stamp &&
            d->m_price == other.d->m_price &&
            d->m_size == other.d->m_size;
}

double Trade::price() const
{
    return d->m_price;
}

double Trade::size() const
{
    return d->m_size;
}

QDateTime Trade::datetime() const
{
    return d->m_stamp;
}

} // namespace OpenTrade

QDebug operator<<(QDebug c, const OpenTrade::Trade &Trade)
{
    c.nospace() << "Trade("
                << "Time:" << Trade.datetime()
                << "Price:" << Trade.price()
                << "Size:" << Trade.size()
                <<')';
    return c.space();
}
