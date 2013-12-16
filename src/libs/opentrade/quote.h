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
#ifndef __OPENTRADE_QUOTE_H__
#define __OPENTRADE_QUOTE_H__

#include "opentrade_global.h"

#include <QSharedDataPointer>
#include <QDebug>
#include <QDateTime>


namespace OpenTrade {

namespace Internal {
class QuotePrivate;
}

class OPENTRADE_EXPORT Quote
{
public:

    Quote(const QDateTime& dateTime, double bid, int bidSize, double ask, int askSize);
    ~Quote();

    Quote& operator=(const Quote &other);
    void swap(Quote &other) { qSwap(d, other.d); }

#ifdef Q_COMPILER_RVALUE_REFS
    inline Quote &operator=(Quote &&other)
    { qSwap(d, other.d); return *this; }
#endif

    bool operator==(const Quote &other) const;
    inline bool operator!=(const Quote &other) const { return !(operator==(other)); }


    double ask() const;

    int askSize() const;

    double bid() const;

    int bidSize() const;

    QDateTime dateTime() const;

    int providerId() const;

private:
    QSharedDataPointer<Internal::QuotePrivate> d;
};

QDebug OPENTRADE_EXPORT operator << (QDebug, const Quote &quote);

} // namespace OpenTrade

Q_DECLARE_SHARED(OpenTrade::Quote)

#endif // __OPENTRADE_QUOTE_H__
