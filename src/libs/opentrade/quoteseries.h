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
#ifndef __OPENTRADE_QUOTESERIES_H__
#define __OPENTRADE_QUOTESERIES_H__

#include "opentrade_global.h"
#include "quote.h"
#include "barseries.h"

#include <QSharedDataPointer>
#include <QDebug>
#include <QuoteData>


namespace OpenTrade {

namespace Internal {
class QuoteSeriesPrivate;
}

class OPENTRADE_EXPORT QuoteSeries
{
public:

    QuoteSeries();
    ~QuoteSeries();

    QuoteSeries& operator=(const QuoteSeries &other);
    void swap(QuoteSeries &other) { qSwap(d, other.d); }

#ifdef Q_COMPILER_RVALUE_REFS
    inline QuoteSeries &operator=(QuoteSeries &&other)
    { qSwap(d, other.d); return *this; }
#endif

    bool operator==(const QuoteSeries &other) const;
    inline bool operator!=(const QuoteSeries &other) const { return !(operator==(other)); }

    void add(const Quote& quote);
    BarSeries compressBars(QuoteData input, BarType barType, long barSize);

    int count() const;

    Quote last() const;

private:
    QSharedDataPointer<Internal::QuoteSeriesPrivate> d;
};

QDebug OPENTRADE_EXPORT operator << (QDebug, const QuoteSeries &quoteseries);

} // namespace OpenTrade

Q_DECLARE_SHARED(OpenTrade::QuoteSeries)

#endif // __OPENTRADE_QUOTESERIES_H__
