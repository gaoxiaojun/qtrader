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
#ifndef __OPENTRADE_BROKERACCOUNTLIST_H__
#define __OPENTRADE_BROKERACCOUNTLIST_H__

#include "opentrade_global.h"

#include <QSharedDataPointer>
#include <QDebug>


namespace OpenTrade {

namespace Internal {
class BrokerAccountListPrivate;
}

class OPENTRADE_EXPORT BrokerAccountList : public IEnumerable
{
public:

    ~BrokerAccountList();

    BrokerAccountList& operator=(const BrokerAccountList &other);
    void swap(BrokerAccountList &other) { qSwap(d, other.d); }

#ifdef Q_COMPILER_RVALUE_REFS
    inline BrokerAccountList &operator=(BrokerAccountList &&other)
    { qSwap(d, other.d); return *this; }
#endif

    bool operator==(const BrokerAccountList &other) const;
    inline bool operator!=(const BrokerAccountList &other) const { return !(operator==(other)); }

    void copyTo(const Array& array, int index);

    int count() const;

private:
    QSharedDataPointer<Internal::BrokerAccountListPrivate> d;
};

QDebug OPENTRADE_EXPORT operator << (QDebug, const BrokerAccountList &brokeraccountlist);

} // namespace OpenTrade

Q_DECLARE_SHARED(OpenTrade::BrokerAccountList)

#endif // __OPENTRADE_BROKERACCOUNTLIST_H__
