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
#ifndef __OPENTRADE_BARFACTORY_H__
#define __OPENTRADE_BARFACTORY_H__

#include "opentrade_global.h"

#include <QSharedDataPointer>
#include <QDebug>


namespace OpenTrade {

namespace Internal {
class BarFactoryPrivate;
}

class OPENTRADE_EXPORT BarFactory
{
public:

    ~BarFactory();

    BarFactory& operator=(const BarFactory &other);
    void swap(BarFactory &other) { qSwap(d, other.d); }

#ifdef Q_COMPILER_RVALUE_REFS
    inline BarFactory &operator=(BarFactory &&other)
    { qSwap(d, other.d); return *this; }
#endif

    bool operator==(const BarFactory &other) const;
    inline bool operator!=(const BarFactory &other) const { return !(operator==(other)); }

    void reset();

    BarFactoryInput input() const;

private:
    QSharedDataPointer<Internal::BarFactoryPrivate> d;
};

QDebug OPENTRADE_EXPORT operator << (QDebug, const BarFactory &barfactory);

} // namespace OpenTrade

Q_DECLARE_SHARED(OpenTrade::BarFactory)

#endif // __OPENTRADE_BARFACTORY_H__
