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
#ifndef __OPENTRADE_BROKERPOSITIONFIELDLIST_H__
#define __OPENTRADE_BROKERPOSITIONFIELDLIST_H__

#include "opentrade_global.h"

#include <QSharedDataPointer>
#include <QDebug>


namespace OpenTrade {

namespace Internal {
class BrokerPositionFieldListPrivate;
}

class OPENTRADE_EXPORT BrokerPositionFieldList : public IEnumerable
{
public:

    ~BrokerPositionFieldList();

    BrokerPositionFieldList& operator=(const BrokerPositionFieldList &other);
    void swap(BrokerPositionFieldList &other) { qSwap(d, other.d); }

#ifdef Q_COMPILER_RVALUE_REFS
    inline BrokerPositionFieldList &operator=(BrokerPositionFieldList &&other)
    { qSwap(d, other.d); return *this; }
#endif

    bool operator==(const BrokerPositionFieldList &other) const;
    inline bool operator!=(const BrokerPositionFieldList &other) const { return !(operator==(other)); }

    void copyTo(const Array& array, int index);

    int count() const;

private:
    QSharedDataPointer<Internal::BrokerPositionFieldListPrivate> d;
};

QDebug OPENTRADE_EXPORT operator << (QDebug, const BrokerPositionFieldList &brokerpositionfieldlist);

} // namespace OpenTrade

Q_DECLARE_SHARED(OpenTrade::BrokerPositionFieldList)

#endif // __OPENTRADE_BROKERPOSITIONFIELDLIST_H__
