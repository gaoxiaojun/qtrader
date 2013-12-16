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
#include "quoteseries.h"

#include <QSharedData>

namespace OpenTrade {

namespace Internal {

class QuoteSeriesPrivate : public QSharedData
{
public:
    int m_count;
    Quote m_last;
};

} // namespace Internal

QuoteSeries::QuoteSeries()
{

}

QuoteSeries::~QuoteSeries()
{

}

QuoteSeries& QuoteSeries::operator=(const QuoteSeries &other)
{
    d = other.d;
    return *this;
}

bool QuoteSeries::operator==(const QuoteSeries &other) const
{
    if(d == other.d)
      return true;

    return d->m_count == other.d->m_count &&
           d->m_last == other.d->m_last;
}

void QuoteSeries::add(const Quote& quote)
{

}

BarSeries QuoteSeries::compressBars(QuoteData input, BarType barType, long barSize)
{

}

int QuoteSeries::count() const
{
    return d->m_count;
}

Quote QuoteSeries::last() const
{
    return d->m_last;
}


} // namespace OpenTrade

QDebug operator<<(QDebug c, const OpenTrade::QuoteSeries &quoteseries)
{
    c.nospace() << "QuoteSeries("
                << "Count:" << quoteseries.count() 
                << "Last:" << quoteseries.last() 
                <<')';
    return c.space();
}
