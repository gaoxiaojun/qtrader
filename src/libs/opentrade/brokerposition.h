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
#ifndef __OPENTRADE_BROKERPOSITION_H__
#define __OPENTRADE_BROKERPOSITION_H__

#include "opentrade_global.h"
#include "brokerpositionfieldlist.h"

#include <QSharedDataPointer>
#include <QDebug>
#include <QString>
#include <QDateTime>


namespace OpenTrade {

namespace Internal {
class BrokerPositionPrivate;
}

class OPENTRADE_EXPORT BrokerPosition
{
public:

    ~BrokerPosition();

    BrokerPosition& operator=(const BrokerPosition &other);
    void swap(BrokerPosition &other) { qSwap(d, other.d); }

#ifdef Q_COMPILER_RVALUE_REFS
    inline BrokerPosition &operator=(BrokerPosition &&other)
    { qSwap(d, other.d); return *this; }
#endif

    bool operator==(const BrokerPosition &other) const;
    inline bool operator!=(const BrokerPosition &other) const { return !(operator==(other)); }

    void addCustomField(const QString& name, const QString& value);

    QString currency() const;
    void setCurrency(const QString& currency);

    QString exchange() const;
    void setExchange(const QString& exchange);

    BrokerPositionFieldList fields() const;

    InstrumentType instrumentType() const;
    void setInstrumentType(InstrumentType instrumenttype);

    double longQty() const;
    void setLongQty(double longqty);

    QDateTime maturity() const;
    void setMaturity(const QDateTime& maturity);

    PutCall putCall() const;
    void setPutCall(PutCall putcall);

    double qty() const;
    void setQty(double qty);

    double shortQty() const;
    void setShortQty(double shortqty);

    double strike() const;
    void setStrike(double strike);

    QString symbol() const;
    void setSymbol(const QString& symbol);

private:
    QSharedDataPointer<Internal::BrokerPositionPrivate> d;
};

QDebug OPENTRADE_EXPORT operator << (QDebug, const BrokerPosition &brokerposition);

} // namespace OpenTrade

Q_DECLARE_SHARED(OpenTrade::BrokerPosition)

#endif // __OPENTRADE_BROKERPOSITION_H__
