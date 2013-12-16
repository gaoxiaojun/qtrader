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

#ifndef TRADE_H
#define TRADE_H

#include "opentrade_global.h"

#include <QSharedDataPointer>
#include <QMetaType>
#include <QDateTime>
#include <QDebug>

namespace OpenTrade {

namespace Internal {
class TradePrivate;
}

class  OPENTRADE_EXPORT Trade
{
public:
    Trade(const QDateTime& dt, double price, double size);
    Trade(const Trade &other);
    ~Trade();

    Trade& operator=(const Trade &other);
    void swap(Trade &other) { qSwap(d, other.d); }

#ifdef Q_COMPILER_RVALUE_REFS
    inline Trade &operator=(Trade &&other)
    { qSwap(d, other.d); return *this; }
#endif

    bool operator==(const Trade &other) const;
    inline bool operator!=(const Trade &other) const { return !(operator==(other)); }

    double price() const;
    double size() const;
    QDateTime datetime() const;

private:
    QSharedDataPointer<Internal::TradePrivate> d;
    friend class Internal::TradePrivate;
};

QDebug OPENTRADE_EXPORT operator << (QDebug, const Trade &Trade);

} // namespace OpenTrade

Q_DECLARE_SHARED(OpenTrade::Trade)

#endif // TRADE_H
