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
#include "brokeraccountfield.h"

#include <QSharedData>

namespace OpenTrade {

namespace Internal {

class BrokerAccountFieldPrivate : public QSharedData
{
public:
    QString m_currency;
    QString m_name;
    QString m_value;
};

} // namespace Internal

BrokerAccountField::~BrokerAccountField()
{

}

BrokerAccountField& BrokerAccountField::operator=(const BrokerAccountField &other)
{
    d = other.d;
    return *this;
}

bool BrokerAccountField::operator==(const BrokerAccountField &other) const
{
    if(d == other.d)
      return true;

    return d->m_currency == other.d->m_currency &&
           d->m_name == other.d->m_name &&
           d->m_value == other.d->m_value;
}

QString BrokerAccountField::currency() const
{
    return d->m_currency;
}

QString BrokerAccountField::name() const
{
    return d->m_name;
}

QString BrokerAccountField::value() const
{
    return d->m_value;
}


} // namespace OpenTrade

QDebug operator<<(QDebug c, const OpenTrade::BrokerAccountField &brokeraccountfield)
{
    c.nospace() << "BrokerAccountField("
                << "Currency:" << brokeraccountfield.currency() 
                << "Name:" << brokeraccountfield.name() 
                << "Value:" << brokeraccountfield.value() 
                <<')';
    return c.space();
}
