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
#ifndef __OPENTRADE_TRANSACTIONLIST_H__
#define __OPENTRADE_TRANSACTIONLIST_H__

#include "opentrade_global.h"

#include <QSharedDataPointer>
#include <QDebug>


namespace OpenTrade {

namespace Internal {
class TransactionListPrivate;
}

class OPENTRADE_EXPORT TransactionList
{
public:

    ~TransactionList();

    TransactionList& operator=(const TransactionList &other);
    void swap(TransactionList &other) { qSwap(d, other.d); }

#ifdef Q_COMPILER_RVALUE_REFS
    inline TransactionList &operator=(TransactionList &&other)
    { qSwap(d, other.d); return *this; }
#endif

    bool operator==(const TransactionList &other) const;
    inline bool operator!=(const TransactionList &other) const { return !(operator==(other)); }


    int count() const;

private:
    QSharedDataPointer<Internal::TransactionListPrivate> d;
};

QDebug OPENTRADE_EXPORT operator << (QDebug, const TransactionList &transactionlist);

} // namespace OpenTrade

Q_DECLARE_SHARED(OpenTrade::TransactionList)

#endif // __OPENTRADE_TRANSACTIONLIST_H__
