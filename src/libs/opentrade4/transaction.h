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
#ifndef __OPENTRADE_TRANSACTION_H__
#define __OPENTRADE_TRANSACTION_H__

#include "opentrade_global.h"
#include "instrument.h"

#include <QSharedDataPointer>
#include <QDebug>
#include <QDateTime>
#include <QString>


namespace OpenTrade {

namespace Internal {
class TransactionPrivate;
}

class OPENTRADE_EXPORT Transaction
{
public:

    ~Transaction();

    Transaction& operator=(const Transaction &other);
    void swap(Transaction &other) { qSwap(d, other.d); }

#ifdef Q_COMPILER_RVALUE_REFS
    inline Transaction &operator=(Transaction &&other)
    { qSwap(d, other.d); return *this; }
#endif

    bool operator==(const Transaction &other) const;
    inline bool operator!=(const Transaction &other) const { return !(operator==(other)); }


    double cost() const;

    QDateTime dateTime() const;

    Instrument instrument() const;

    double pnL() const;

    double price() const;

    double qty() const;

    TransactionSide side() const;

    QString text() const;

private:
    QSharedDataPointer<Internal::TransactionPrivate> d;
};

QDebug OPENTRADE_EXPORT operator << (QDebug, const Transaction &transaction);

} // namespace OpenTrade

Q_DECLARE_SHARED(OpenTrade::Transaction)

#endif // __OPENTRADE_TRANSACTION_H__
