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
#ifndef __OPENTRADE_BROKERINFO_H__
#define __OPENTRADE_BROKERINFO_H__

#include "opentrade_global.h"
#include "brokeraccount.h"
#include "brokeraccountlist.h"

#include <QSharedDataPointer>
#include <QDebug>
#include <QString>


namespace OpenTrade {

namespace Internal {
class BrokerInfoPrivate;
}

class OPENTRADE_EXPORT BrokerInfo
{
public:

    BrokerInfo();
    ~BrokerInfo();

    BrokerInfo& operator=(const BrokerInfo &other);
    void swap(BrokerInfo &other) { qSwap(d, other.d); }

#ifdef Q_COMPILER_RVALUE_REFS
    inline BrokerInfo &operator=(BrokerInfo &&other)
    { qSwap(d, other.d); return *this; }
#endif

    bool operator==(const BrokerInfo &other) const;
    inline bool operator!=(const BrokerInfo &other) const { return !(operator==(other)); }

    BrokerAccount addAccount(const QString& name);

    BrokerAccountList accounts() const;

private:
    QSharedDataPointer<Internal::BrokerInfoPrivate> d;
};

QDebug OPENTRADE_EXPORT operator << (QDebug, const BrokerInfo &brokerinfo);

} // namespace OpenTrade

Q_DECLARE_SHARED(OpenTrade::BrokerInfo)

#endif // __OPENTRADE_BROKERINFO_H__
