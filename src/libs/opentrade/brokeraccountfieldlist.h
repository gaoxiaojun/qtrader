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
#ifndef __OPENTRADE_BROKERACCOUNTFIELDLIST_H__
#define __OPENTRADE_BROKERACCOUNTFIELDLIST_H__

#include "opentrade_global.h"
#include "brokeraccountfield.h"

#include <QSharedDataPointer>
#include <QDebug>
#include <QString>


namespace OpenTrade {

namespace Internal {
class BrokerAccountFieldListPrivate;
}

class OPENTRADE_EXPORT BrokerAccountFieldList : public IEnumerable
{
public:

    ~BrokerAccountFieldList();

    BrokerAccountFieldList& operator=(const BrokerAccountFieldList &other);
    void swap(BrokerAccountFieldList &other) { qSwap(d, other.d); }

#ifdef Q_COMPILER_RVALUE_REFS
    inline BrokerAccountFieldList &operator=(BrokerAccountFieldList &&other)
    { qSwap(d, other.d); return *this; }
#endif

    bool operator==(const BrokerAccountFieldList &other) const;
    inline bool operator!=(const BrokerAccountFieldList &other) const { return !(operator==(other)); }

    bool contains(const QString& name);
    bool contains(const QString& name, const QString& currency);
    void copyTo(const Array& array, int index);
    BrokerAccountField getAllByName(const QString& name);

    int count() const;

private:
    QSharedDataPointer<Internal::BrokerAccountFieldListPrivate> d;
};

QDebug OPENTRADE_EXPORT operator << (QDebug, const BrokerAccountFieldList &brokeraccountfieldlist);

} // namespace OpenTrade

Q_DECLARE_SHARED(OpenTrade::BrokerAccountFieldList)

#endif // __OPENTRADE_BROKERACCOUNTFIELDLIST_H__
