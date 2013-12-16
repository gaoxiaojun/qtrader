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
#include "engine_parameter.h"

#include <QSharedData>

namespace OpenTrade {

namespace Internal {

class Engine_ParameterPrivate : public QSharedData
{
public:
    QString m_name;
    Type m_type;
    QVariant m_value;
};

} // namespace Internal

Engine_Parameter::~Engine_Parameter()
{

}

Engine_Parameter& Engine_Parameter::operator=(const Engine_Parameter &other)
{
    d = other.d;
    return *this;
}

bool Engine_Parameter::operator==(const Engine_Parameter &other) const
{
    if(d == other.d)
      return true;

    return d->m_name == other.d->m_name &&
           d->m_type == other.d->m_type &&
           d->m_value == other.d->m_value;
}

void Engine_Parameter::parameter(const QString& name, const QVariant& value, const Type& type)
{

}

QString Engine_Parameter::name() const
{
    return d->m_name;
}

void Engine_Parameter::setName(const QString& name)
{
    d->m_name = name;
}

Type Engine_Parameter::type() const
{
    return d->m_type;
}

void Engine_Parameter::setType(const Type& type)
{
    d->m_type = type;
}

QVariant Engine_Parameter::value() const
{
    return d->m_value;
}

void Engine_Parameter::setValue(const QVariant& value)
{
    d->m_value = value;
}


} // namespace OpenTrade

QDebug operator<<(QDebug c, const OpenTrade::Engine_Parameter &engine_parameter)
{
    c.nospace() << "Engine_Parameter("
                << "Name:" << engine_parameter.name() 
                << "Type:" << engine_parameter.type() 
                << "Value:" << engine_parameter.value() 
                <<')';
    return c.space();
}
