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
#ifndef __OPENTRADE_PORTFOLIOPRICER_H__
#define __OPENTRADE_PORTFOLIOPRICER_H__

#include "opentrade_global.h"
#include "position.h"

#include <QSharedDataPointer>
#include <QDebug>


namespace OpenTrade {

namespace Internal {
class PortfolioPricerPrivate;
}

class OPENTRADE_EXPORT PortfolioPricer
{
public:

    PortfolioPricer();
    ~PortfolioPricer();

    PortfolioPricer& operator=(const PortfolioPricer &other);
    void swap(PortfolioPricer &other) { qSwap(d, other.d); }

#ifdef Q_COMPILER_RVALUE_REFS
    inline PortfolioPricer &operator=(PortfolioPricer &&other)
    { qSwap(d, other.d); return *this; }
#endif

    bool operator==(const PortfolioPricer &other) const;
    inline bool operator!=(const PortfolioPricer &other) const { return !(operator==(other)); }

    double price(const Position& position);

    static portfolioPricer() const;

private:
    QSharedDataPointer<Internal::PortfolioPricerPrivate> d;
};

QDebug OPENTRADE_EXPORT operator << (QDebug, const PortfolioPricer &portfoliopricer);

} // namespace OpenTrade

Q_DECLARE_SHARED(OpenTrade::PortfolioPricer)

#endif // __OPENTRADE_PORTFOLIOPRICER_H__
