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
#ifndef __OPENTRADE_OPTIMIZATIONPARAMETERATTRIBUTE_H__
#define __OPENTRADE_OPTIMIZATIONPARAMETERATTRIBUTE_H__

#include "opentrade_global.h"

#include <QSharedDataPointer>
#include <QDebug>


namespace OpenTrade {

namespace Internal {
class OptimizationParameterAttributePrivate;
}

class OPENTRADE_EXPORT OptimizationParameterAttribute
{
public:

    OptimizationParameterAttribute(double start, double stop, double step);
    ~OptimizationParameterAttribute();

    OptimizationParameterAttribute& operator=(const OptimizationParameterAttribute &other);
    void swap(OptimizationParameterAttribute &other) { qSwap(d, other.d); }

#ifdef Q_COMPILER_RVALUE_REFS
    inline OptimizationParameterAttribute &operator=(OptimizationParameterAttribute &&other)
    { qSwap(d, other.d); return *this; }
#endif

    bool operator==(const OptimizationParameterAttribute &other) const;
    inline bool operator!=(const OptimizationParameterAttribute &other) const { return !(operator==(other)); }


    double start() const;

    double step() const;

    double stop() const;

private:
    QSharedDataPointer<Internal::OptimizationParameterAttributePrivate> d;
};

QDebug OPENTRADE_EXPORT operator << (QDebug, const OptimizationParameterAttribute &optimizationparameterattribute);

} // namespace OpenTrade

Q_DECLARE_SHARED(OpenTrade::OptimizationParameterAttribute)

#endif // __OPENTRADE_OPTIMIZATIONPARAMETERATTRIBUTE_H__
