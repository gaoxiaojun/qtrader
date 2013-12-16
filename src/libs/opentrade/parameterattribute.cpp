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
#include "parameterattribute.h"

#include <QSharedData>

namespace OpenTrade {

namespace Internal {

class ParameterAttributePrivate : public QSharedData
{
public:
    QString m_category;
    QString m_description;
};

} // namespace Internal

ParameterAttribute::ParameterAttribute()
{

}

ParameterAttribute::ParameterAttribute(const QString& description)
{

}

ParameterAttribute::ParameterAttribute(const QString& description, const QString& category)
{

}

ParameterAttribute::~ParameterAttribute()
{

}

ParameterAttribute& ParameterAttribute::operator=(const ParameterAttribute &other)
{
    d = other.d;
    return *this;
}

bool ParameterAttribute::operator==(const ParameterAttribute &other) const
{
    if(d == other.d)
      return true;

    return d->m_category == other.d->m_category &&
           d->m_description == other.d->m_description;
}

QString ParameterAttribute::category() const
{
    return d->m_category;
}

QString ParameterAttribute::description() const
{
    return d->m_description;
}


} // namespace OpenTrade

QDebug operator<<(QDebug c, const OpenTrade::ParameterAttribute &parameterattribute)
{
    c.nospace() << "ParameterAttribute("
                << "Category:" << parameterattribute.category() 
                << "Description:" << parameterattribute.description() 
                <<')';
    return c.space();
}
