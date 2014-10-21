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
#include "portfoliopricer.h"

#include <QSharedData>

namespace OpenTrade {

namespace Internal {

class PortfolioPricerPrivate : public QSharedData
{
public:
    static m_portfolioPricer;
};

} // namespace Internal

PortfolioPricer::PortfolioPricer()
{

}

PortfolioPricer::~PortfolioPricer()
{

}

PortfolioPricer& PortfolioPricer::operator=(const PortfolioPricer &other)
{
    d = other.d;
    return *this;
}

bool PortfolioPricer::operator==(const PortfolioPricer &other) const
{
    if(d == other.d)
      return true;

    return d->m_portfolioPricer == other.d->m_portfolioPricer;
}

double PortfolioPricer::price(const Position& position)
{

}

static PortfolioPricer::portfolioPricer() const
{
    return d->m_portfolioPricer;
}


} // namespace OpenTrade

QDebug operator<<(QDebug c, const OpenTrade::PortfolioPricer &portfoliopricer)
{
    c.nospace() << "PortfolioPricer("
                << "PortfolioPricer:" << portfoliopricer.portfolioPricer() 
                <<')';
    return c.space();
}
