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
#include "brokerpositionfield.h"

#include <QSharedData>

namespace OpenTrade {

namespace Internal {

class BrokerPositionFieldPrivate : public QSharedData
{
public:
    QString m_name;
    QString m_value;
};

} // namespace Internal

BrokerPositionField::~BrokerPositionField()
{

}

BrokerPositionField& BrokerPositionField::operator=(const BrokerPositionField &other)
{
    d = other.d;
    return *this;
}

bool BrokerPositionField::operator==(const BrokerPositionField &other) const
{
    if(d == other.d)
      return true;

    return d->m_name == other.d->m_name &&
           d->m_value == other.d->m_value;
}

QString BrokerPositionField::name() const
{
    return d->m_name;
}

QString BrokerPositionField::value() const
{
    return d->m_value;
}


} // namespace OpenTrade

QDebug operator<<(QDebug c, const OpenTrade::BrokerPositionField &brokerpositionfield)
{
    c.nospace() << "BrokerPositionField("
                << "Name:" << brokerpositionfield.name() 
                << "Value:" << brokerpositionfield.value() 
                <<')';
    return c.space();
}
