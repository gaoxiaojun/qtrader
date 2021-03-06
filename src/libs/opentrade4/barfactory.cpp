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
#include "barfactory.h"

#include <QSharedData>

namespace OpenTrade {

namespace Internal {

class BarFactoryPrivate : public QSharedData
{
public:
    BarFactoryInput m_input;
};

} // namespace Internal

BarFactory::~BarFactory()
{

}

BarFactory& BarFactory::operator=(const BarFactory &other)
{
    d = other.d;
    return *this;
}

bool BarFactory::operator==(const BarFactory &other) const
{
    if(d == other.d)
      return true;

    return d->m_input == other.d->m_input;
}

void BarFactory::reset()
{

}

BarFactoryInput BarFactory::input() const
{
    return d->m_input;
}


} // namespace OpenTrade

QDebug operator<<(QDebug c, const OpenTrade::BarFactory &barfactory)
{
    c.nospace() << "BarFactory("
                << "input:" << barfactory.input() 
                <<')';
    return c.space();
}
