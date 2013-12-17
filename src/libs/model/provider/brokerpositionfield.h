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
#ifndef __OPENTRADE_BROKERPOSITIONFIELD_H__
#define __OPENTRADE_BROKERPOSITIONFIELD_H__

#include "opentrade_global.h"

#include <QSharedDataPointer>
#include <QDebug>
#include <QString>


namespace OpenTrade {

namespace Internal {
class BrokerPositionFieldPrivate;
}

class OPENTRADE_EXPORT BrokerPositionField
{
public:

    ~BrokerPositionField();

    BrokerPositionField& operator=(const BrokerPositionField &other);
    void swap(BrokerPositionField &other) { qSwap(d, other.d); }

#ifdef Q_COMPILER_RVALUE_REFS
    inline BrokerPositionField &operator=(BrokerPositionField &&other)
    { qSwap(d, other.d); return *this; }
#endif

    bool operator==(const BrokerPositionField &other) const;
    inline bool operator!=(const BrokerPositionField &other) const { return !(operator==(other)); }


    QString name() const;

    QString value() const;

private:
    QSharedDataPointer<Internal::BrokerPositionFieldPrivate> d;
};

QDebug OPENTRADE_EXPORT operator << (QDebug, const BrokerPositionField &brokerpositionfield);

} // namespace OpenTrade

Q_DECLARE_SHARED(OpenTrade::BrokerPositionField)

#endif // __OPENTRADE_BROKERPOSITIONFIELD_H__
