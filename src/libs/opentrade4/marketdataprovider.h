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
#ifndef __OPENTRADE_MARKETDATAPROVIDER_H__
#define __OPENTRADE_MARKETDATAPROVIDER_H__

#include "opentrade_global.h"
#include "barfactory.h"
#include "marketdatafilter.h"

#include <QSharedDataPointer>
#include <QDebug>


namespace OpenTrade {

namespace Internal {
class MarketDataProviderPrivate;
}

class OPENTRADE_EXPORT MarketDataProvider
{
public:

    ~MarketDataProvider();

    MarketDataProvider& operator=(const MarketDataProvider &other);
    void swap(MarketDataProvider &other) { qSwap(d, other.d); }

#ifdef Q_COMPILER_RVALUE_REFS
    inline MarketDataProvider &operator=(MarketDataProvider &&other)
    { qSwap(d, other.d); return *this; }
#endif

    bool operator==(const MarketDataProvider &other) const;
    inline bool operator!=(const MarketDataProvider &other) const { return !(operator==(other)); }

    void connect();
    void disconnect();

    BarFactory barFactory() const;
    void setBarFactory(const BarFactory& barfactory);

    MarketDataFilter filter() const;
    void setFilter(const MarketDataFilter& filter);

private:
    QSharedDataPointer<Internal::MarketDataProviderPrivate> d;
};

QDebug OPENTRADE_EXPORT operator << (QDebug, const MarketDataProvider &marketdataprovider);

} // namespace OpenTrade

Q_DECLARE_SHARED(OpenTrade::MarketDataProvider)

#endif // __OPENTRADE_MARKETDATAPROVIDER_H__
