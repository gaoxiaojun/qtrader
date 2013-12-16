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
#ifndef __OPENTRADE_TRADE_H__
#define __OPENTRADE_TRADE_H__

#include "opentrade_global.h"

#include <QSharedDataPointer>
#include <QDebug>
#include <QDateTime>


namespace OpenTrade {

namespace Internal {
class TradePrivate;
}

class OPENTRADE_EXPORT Trade
{
public:

    Trade(const QDateTime& dateTime, double price, int size);
    ~Trade();

    Trade& operator=(const Trade &other);
    void swap(Trade &other) { qSwap(d, other.d); }

#ifdef Q_COMPILER_RVALUE_REFS
    inline Trade &operator=(Trade &&other)
    { qSwap(d, other.d); return *this; }
#endif

    bool operator==(const Trade &other) const;
    inline bool operator!=(const Trade &other) const { return !(operator==(other)); }


    QDateTime dateTime() const;

    double price() const;

    int providerId() const;

    int size() const;

private:
    QSharedDataPointer<Internal::TradePrivate> d;
};

QDebug OPENTRADE_EXPORT operator << (QDebug, const Trade &trade);

} // namespace OpenTrade

Q_DECLARE_SHARED(OpenTrade::Trade)

#endif // __OPENTRADE_TRADE_H__
