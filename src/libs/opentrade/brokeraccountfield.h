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
#ifndef __OPENTRADE_BROKERACCOUNTFIELD_H__
#define __OPENTRADE_BROKERACCOUNTFIELD_H__

#include "opentrade_global.h"

#include <QSharedDataPointer>
#include <QDebug>
#include <QString>


namespace OpenTrade {

namespace Internal {
class BrokerAccountFieldPrivate;
}

class OPENTRADE_EXPORT BrokerAccountField
{
public:

    ~BrokerAccountField();

    BrokerAccountField& operator=(const BrokerAccountField &other);
    void swap(BrokerAccountField &other) { qSwap(d, other.d); }

#ifdef Q_COMPILER_RVALUE_REFS
    inline BrokerAccountField &operator=(BrokerAccountField &&other)
    { qSwap(d, other.d); return *this; }
#endif

    bool operator==(const BrokerAccountField &other) const;
    inline bool operator!=(const BrokerAccountField &other) const { return !(operator==(other)); }


    QString currency() const;

    QString name() const;

    QString value() const;

private:
    QSharedDataPointer<Internal::BrokerAccountFieldPrivate> d;
};

QDebug OPENTRADE_EXPORT operator << (QDebug, const BrokerAccountField &brokeraccountfield);

} // namespace OpenTrade

Q_DECLARE_SHARED(OpenTrade::BrokerAccountField)

#endif // __OPENTRADE_BROKERACCOUNTFIELD_H__
