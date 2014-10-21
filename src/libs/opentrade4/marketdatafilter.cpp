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
#include "marketdatafilter.h"

#include <QSharedData>

namespace OpenTrade {

namespace Internal {

class MarketDataFilterPrivate : public QSharedData
{
public:
    virtual m_bar;
    virtual m_bar;
    virtual m_quote;
    virtual m_trade;
};

} // namespace Internal

MarketDataFilter::MarketDataFilter()
{

}

MarketDataFilter::~MarketDataFilter()
{

}

MarketDataFilter& MarketDataFilter::operator=(const MarketDataFilter &other)
{
    d = other.d;
    return *this;
}

bool MarketDataFilter::operator==(const MarketDataFilter &other) const
{
    if(d == other.d)
      return true;

    return d->m_bar == other.d->m_bar &&
           d->m_bar == other.d->m_bar &&
           d->m_quote == other.d->m_quote &&
           d->m_trade == other.d->m_trade;
}

virtual MarketDataFilter::bar() const
{
    return d->m_bar;
}

virtual MarketDataFilter::bar() const
{
    return d->m_bar;
}

virtual MarketDataFilter::quote() const
{
    return d->m_quote;
}

virtual MarketDataFilter::trade() const
{
    return d->m_trade;
}


} // namespace OpenTrade

QDebug operator<<(QDebug c, const OpenTrade::MarketDataFilter &marketdatafilter)
{
    c.nospace() << "MarketDataFilter("
                << "Bar:" << marketdatafilter.bar() 
                << "Bar:" << marketdatafilter.bar() 
                << "Quote:" << marketdatafilter.quote() 
                << "Trade:" << marketdatafilter.trade() 
                <<')';
    return c.space();
}
