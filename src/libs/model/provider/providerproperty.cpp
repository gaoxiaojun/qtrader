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
#include "providerproperty.h"

#include <QSharedData>

namespace OpenTrade {

namespace Internal {

class ProviderPropertyPrivate : public QSharedData
{
public:
    QString m_name;
    Type m_type;
    QVariant m_value;
};

} // namespace Internal

ProviderProperty::~ProviderProperty()
{

}

ProviderProperty& ProviderProperty::operator=(const ProviderProperty &other)
{
    d = other.d;
    return *this;
}

bool ProviderProperty::operator==(const ProviderProperty &other) const
{
    if(d == other.d)
      return true;

    return d->m_name == other.d->m_name &&
           d->m_type == other.d->m_type &&
           d->m_value == other.d->m_value;
}

QString ProviderProperty::name() const
{
    return d->m_name;
}

Type ProviderProperty::type() const
{
    return d->m_type;
}

QVariant ProviderProperty::value() const
{
    return d->m_value;
}

void ProviderProperty::setValue(const QVariant& value)
{
    d->m_value = value;
}


} // namespace OpenTrade

QDebug operator<<(QDebug c, const OpenTrade::ProviderProperty &providerproperty)
{
    c.nospace() << "ProviderProperty("
                << "Name:" << providerproperty.name() 
                << "Type:" << providerproperty.type() 
                << "Value:" << providerproperty.value() 
                <<')';
    return c.space();
}
