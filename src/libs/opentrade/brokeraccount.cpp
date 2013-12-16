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
#include "brokeraccount.h"

#include <QSharedData>

namespace OpenTrade {

namespace Internal {

class BrokerAccountPrivate : public QSharedData
{
public:
    double m_buyingPower;
    QString m_name;
    BrokerOrderList m_orders;
    BrokerPositionList m_positions;
    BrokerAccountFieldList m_fields;
};

} // namespace Internal

BrokerAccount::~BrokerAccount()
{

}

BrokerAccount& BrokerAccount::operator=(const BrokerAccount &other)
{
    d = other.d;
    return *this;
}

bool BrokerAccount::operator==(const BrokerAccount &other) const
{
    if(d == other.d)
      return true;

    return d->m_buyingPower == other.d->m_buyingPower &&
           d->m_name == other.d->m_name &&
           d->m_orders == other.d->m_orders &&
           d->m_positions == other.d->m_positions &&
           d->m_fields == other.d->m_fields;
}

void BrokerAccount::addField(const QString& name, const QString& currency, const QString& value)
{

}

void BrokerAccount::addField(const QString& name, const QString& value)
{

}

BrokerOrder BrokerAccount::addOrder()
{

}

BrokerPosition BrokerAccount::addPosition()
{

}

double BrokerAccount::buyingPower() const
{
    return d->m_buyingPower;
}

void BrokerAccount::setBuyingPower(double buyingpower)
{
    d->m_buyingPower = buyingpower;
}

QString BrokerAccount::name() const
{
    return d->m_name;
}

BrokerOrderList BrokerAccount::orders() const
{
    return d->m_orders;
}

BrokerPositionList BrokerAccount::positions() const
{
    return d->m_positions;
}

BrokerAccountFieldList BrokerAccount::fields() const
{
    return d->m_fields;
}


} // namespace OpenTrade

QDebug operator<<(QDebug c, const OpenTrade::BrokerAccount &brokeraccount)
{
    c.nospace() << "BrokerAccount("
                << "BuyingPower:" << brokeraccount.buyingPower() 
                << "Name:" << brokeraccount.name() 
                << "Orders:" << brokeraccount.orders() 
                << "Positions:" << brokeraccount.positions() 
                << "Fields:" << brokeraccount.fields() 
                <<')';
    return c.space();
}
