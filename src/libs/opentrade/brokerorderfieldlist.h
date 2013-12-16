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
#ifndef __OPENTRADE_BROKERORDERFIELDLIST_H__
#define __OPENTRADE_BROKERORDERFIELDLIST_H__

#include "opentrade_global.h"

#include <QSharedDataPointer>
#include <QDebug>


namespace OpenTrade {

namespace Internal {
class BrokerOrderFieldListPrivate;
}

class OPENTRADE_EXPORT BrokerOrderFieldList : public IEnumerable
{
public:

    ~BrokerOrderFieldList();

    BrokerOrderFieldList& operator=(const BrokerOrderFieldList &other);
    void swap(BrokerOrderFieldList &other) { qSwap(d, other.d); }

#ifdef Q_COMPILER_RVALUE_REFS
    inline BrokerOrderFieldList &operator=(BrokerOrderFieldList &&other)
    { qSwap(d, other.d); return *this; }
#endif

    bool operator==(const BrokerOrderFieldList &other) const;
    inline bool operator!=(const BrokerOrderFieldList &other) const { return !(operator==(other)); }

    void copyTo(const Array& array, int index);

    int count() const;

private:
    QSharedDataPointer<Internal::BrokerOrderFieldListPrivate> d;
};

QDebug OPENTRADE_EXPORT operator << (QDebug, const BrokerOrderFieldList &brokerorderfieldlist);

} // namespace OpenTrade

Q_DECLARE_SHARED(OpenTrade::BrokerOrderFieldList)

#endif // __OPENTRADE_BROKERORDERFIELDLIST_H__
