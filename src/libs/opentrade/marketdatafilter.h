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
#ifndef __OPENTRADE_MARKETDATAFILTER_H__
#define __OPENTRADE_MARKETDATAFILTER_H__

#include "opentrade_global.h"

#include <QSharedDataPointer>
#include <QDebug>


namespace OpenTrade {

namespace Internal {
class MarketDataFilterPrivate;
}

class OPENTRADE_EXPORT MarketDataFilter
{
public:

    MarketDataFilter();
    ~MarketDataFilter();

    MarketDataFilter& operator=(const MarketDataFilter &other);
    void swap(MarketDataFilter &other) { qSwap(d, other.d); }

#ifdef Q_COMPILER_RVALUE_REFS
    inline MarketDataFilter &operator=(MarketDataFilter &&other)
    { qSwap(d, other.d); return *this; }
#endif

    bool operator==(const MarketDataFilter &other) const;
    inline bool operator!=(const MarketDataFilter &other) const { return !(operator==(other)); }


    virtual bar() const;

    virtual bar() const;

    virtual quote() const;

    virtual trade() const;

private:
    QSharedDataPointer<Internal::MarketDataFilterPrivate> d;
};

QDebug OPENTRADE_EXPORT operator << (QDebug, const MarketDataFilter &marketdatafilter);

} // namespace OpenTrade

Q_DECLARE_SHARED(OpenTrade::MarketDataFilter)

#endif // __OPENTRADE_MARKETDATAFILTER_H__
