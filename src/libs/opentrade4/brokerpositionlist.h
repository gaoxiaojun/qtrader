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
#ifndef __OPENTRADE_BROKERPOSITIONLIST_H__
#define __OPENTRADE_BROKERPOSITIONLIST_H__

#include "opentrade_global.h"

#include <QSharedDataPointer>
#include <QDebug>


namespace OpenTrade {

namespace Internal {
class BrokerPositionListPrivate;
}

class OPENTRADE_EXPORT BrokerPositionList : public IEnumerable
{
public:

    ~BrokerPositionList();

    BrokerPositionList& operator=(const BrokerPositionList &other);
    void swap(BrokerPositionList &other) { qSwap(d, other.d); }

#ifdef Q_COMPILER_RVALUE_REFS
    inline BrokerPositionList &operator=(BrokerPositionList &&other)
    { qSwap(d, other.d); return *this; }
#endif

    bool operator==(const BrokerPositionList &other) const;
    inline bool operator!=(const BrokerPositionList &other) const { return !(operator==(other)); }

    void copyTo(const Array& array, int index);

    int count() const;

private:
    QSharedDataPointer<Internal::BrokerPositionListPrivate> d;
};

QDebug OPENTRADE_EXPORT operator << (QDebug, const BrokerPositionList &brokerpositionlist);

} // namespace OpenTrade

Q_DECLARE_SHARED(OpenTrade::BrokerPositionList)

#endif // __OPENTRADE_BROKERPOSITIONLIST_H__
