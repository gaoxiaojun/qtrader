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
#include "optimizationparameterattribute.h"

#include <QSharedData>

namespace OpenTrade {

namespace Internal {

class OptimizationParameterAttributePrivate : public QSharedData
{
public:
    double m_start;
    double m_step;
    double m_stop;
};

} // namespace Internal

OptimizationParameterAttribute::OptimizationParameterAttribute(double start, double stop, double step)
{

}

OptimizationParameterAttribute::~OptimizationParameterAttribute()
{

}

OptimizationParameterAttribute& OptimizationParameterAttribute::operator=(const OptimizationParameterAttribute &other)
{
    d = other.d;
    return *this;
}

bool OptimizationParameterAttribute::operator==(const OptimizationParameterAttribute &other) const
{
    if(d == other.d)
      return true;

    return d->m_start == other.d->m_start &&
           d->m_step == other.d->m_step &&
           d->m_stop == other.d->m_stop;
}

double OptimizationParameterAttribute::start() const
{
    return d->m_start;
}

double OptimizationParameterAttribute::step() const
{
    return d->m_step;
}

double OptimizationParameterAttribute::stop() const
{
    return d->m_stop;
}


} // namespace OpenTrade

QDebug operator<<(QDebug c, const OpenTrade::OptimizationParameterAttribute &optimizationparameterattribute)
{
    c.nospace() << "OptimizationParameterAttribute("
                << "Start:" << optimizationparameterattribute.start() 
                << "Step:" << optimizationparameterattribute.step() 
                << "Stop:" << optimizationparameterattribute.stop() 
                <<')';
    return c.space();
}
