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
#ifndef __OPENTRADE_BROKERORDERFIELD_H__
#define __OPENTRADE_BROKERORDERFIELD_H__

#include "opentrade_global.h"

#include <QSharedDataPointer>
#include <QDebug>
#include <QString>


namespace OpenTrade {

namespace Internal {
class BrokerOrderFieldPrivate;
}

class OPENTRADE_EXPORT BrokerOrderField
{
public:

    ~BrokerOrderField();

    BrokerOrderField& operator=(const BrokerOrderField &other);
    void swap(BrokerOrderField &other) { qSwap(d, other.d); }

#ifdef Q_COMPILER_RVALUE_REFS
    inline BrokerOrderField &operator=(BrokerOrderField &&other)
    { qSwap(d, other.d); return *this; }
#endif

    bool operator==(const BrokerOrderField &other) const;
    inline bool operator!=(const BrokerOrderField &other) const { return !(operator==(other)); }


    QString name() const;

    QString value() const;

private:
    QSharedDataPointer<Internal::BrokerOrderFieldPrivate> d;
};

QDebug OPENTRADE_EXPORT operator << (QDebug, const BrokerOrderField &brokerorderfield);

} // namespace OpenTrade

Q_DECLARE_SHARED(OpenTrade::BrokerOrderField)

#endif // __OPENTRADE_BROKERORDERFIELD_H__
