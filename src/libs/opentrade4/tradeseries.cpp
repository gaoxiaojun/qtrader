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
#include "tradeseries.h"

#include <QSharedData>

namespace OpenTrade {

namespace Internal {

class TradeSeriesPrivate : public QSharedData
{
public:
    int m_count;
    Trade m_last;
};

} // namespace Internal

TradeSeries::TradeSeries()
{

}

TradeSeries::~TradeSeries()
{

}

TradeSeries& TradeSeries::operator=(const TradeSeries &other)
{
    d = other.d;
    return *this;
}

bool TradeSeries::operator==(const TradeSeries &other) const
{
    if(d == other.d)
      return true;

    return d->m_count == other.d->m_count &&
           d->m_last == other.d->m_last;
}

void TradeSeries::add(const Trade& trade)
{

}

BarSeries TradeSeries::compressBars(BarType barType, long barSize)
{

}

int TradeSeries::count() const
{
    return d->m_count;
}

Trade TradeSeries::last() const
{
    return d->m_last;
}


} // namespace OpenTrade

QDebug operator<<(QDebug c, const OpenTrade::TradeSeries &tradeseries)
{
    c.nospace() << "TradeSeries("
                << "Count:" << tradeseries.count() 
                << "Last:" << tradeseries.last() 
                <<')';
    return c.space();
}
