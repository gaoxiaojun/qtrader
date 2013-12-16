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
#ifndef __OPENTRADE_BROKERACCOUNT_H__
#define __OPENTRADE_BROKERACCOUNT_H__

#include "opentrade_global.h"
#include "brokerorder.h"
#include "brokerposition.h"
#include "brokerorderlist.h"
#include "brokerpositionlist.h"
#include "brokeraccountfieldlist.h"

#include <QSharedDataPointer>
#include <QDebug>
#include <QString>


namespace OpenTrade {

namespace Internal {
class BrokerAccountPrivate;
}

class OPENTRADE_EXPORT BrokerAccount
{
public:

    ~BrokerAccount();

    BrokerAccount& operator=(const BrokerAccount &other);
    void swap(BrokerAccount &other) { qSwap(d, other.d); }

#ifdef Q_COMPILER_RVALUE_REFS
    inline BrokerAccount &operator=(BrokerAccount &&other)
    { qSwap(d, other.d); return *this; }
#endif

    bool operator==(const BrokerAccount &other) const;
    inline bool operator!=(const BrokerAccount &other) const { return !(operator==(other)); }

    void addField(const QString& name, const QString& currency, const QString& value);
    void addField(const QString& name, const QString& value);
    BrokerOrder addOrder();
    BrokerPosition addPosition();

    double buyingPower() const;
    void setBuyingPower(double buyingpower);

    QString name() const;

    BrokerOrderList orders() const;

    BrokerPositionList positions() const;

    BrokerAccountFieldList fields() const;

private:
    QSharedDataPointer<Internal::BrokerAccountPrivate> d;
};

QDebug OPENTRADE_EXPORT operator << (QDebug, const BrokerAccount &brokeraccount);

} // namespace OpenTrade

Q_DECLARE_SHARED(OpenTrade::BrokerAccount)

#endif // __OPENTRADE_BROKERACCOUNT_H__
