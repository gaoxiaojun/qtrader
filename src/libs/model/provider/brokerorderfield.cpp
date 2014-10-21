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
#include "brokerorderfield.h"

#include <QSharedData>

namespace OpenTrade {

namespace Internal {

class BrokerOrderFieldPrivate : public QSharedData
{
public:
    QString m_name;
    QString m_value;
};

} // namespace Internal

BrokerOrderField::~BrokerOrderField()
{

}

BrokerOrderField& BrokerOrderField::operator=(const BrokerOrderField &other)
{
    d = other.d;
    return *this;
}

bool BrokerOrderField::operator==(const BrokerOrderField &other) const
{
    if(d == other.d)
      return true;

    return d->m_name == other.d->m_name &&
           d->m_value == other.d->m_value;
}

QString BrokerOrderField::name() const
{
    return d->m_name;
}

QString BrokerOrderField::value() const
{
    return d->m_value;
}


} // namespace OpenTrade

QDebug operator<<(QDebug c, const OpenTrade::BrokerOrderField &brokerorderfield)
{
    c.nospace() << "BrokerOrderField("
                << "Name:" << brokerorderfield.name() 
                << "Value:" << brokerorderfield.value() 
                <<')';
    return c.space();
}
