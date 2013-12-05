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

#ifndef __QUOTE_H__
#define __QUOTE_H__

#include "core_global.h"

#include <QSharedDataPointer>
#include <QMetaType>
#include <QList>
#include <QDateTime>
#include <QDebug>

namespace OpenTrade {

namespace Internal {
class QuotePrivate;
}

class  CORE_EXPORT Quote
{
public:
    Quote(const QDateTime& dt, double bid, double bidSize, double ask, double askSize, unsigned providerId = 0);
    Quote(const Quote &other);
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
    double askSize() const;
    double bid() const;
    double bidSize() const;
    QDateTime datetime() const;
    unsigned int providerId() const;

    /*void setAsk(double ask);
    void setBid(double bid);
    void setAskSize(double askSize);
    void setBidSize(double bidSize);
    void setDateTime(const QDateTime& dt);
    void setProviderId(unsigned int id);*/

private:
    QSharedDataPointer<Internal::QuotePrivate> d;
    friend class Internal::QuotePrivate;
};

QDebug CORE_EXPORT operator << (QDebug, const Quote &quote);

} // namespace OpenTrade

Q_DECLARE_SHARED(OpenTrade::Quote)


#endif // __QUOTE_H__