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
#ifndef __OPENTRADE_OPENQUANT_H__
#define __OPENTRADE_OPENQUANT_H__

#include "opentrade_global.h"

#include <QSharedDataPointer>
#include <QDebug>


namespace OpenTrade {

namespace Internal {
class OpenQuantPrivate;
}

class OPENTRADE_EXPORT OpenQuant
{
public:

    OpenQuant();
    ~OpenQuant();

    OpenQuant& operator=(const OpenQuant &other);
    void swap(OpenQuant &other) { qSwap(d, other.d); }

#ifdef Q_COMPILER_RVALUE_REFS
    inline OpenQuant &operator=(OpenQuant &&other)
    { qSwap(d, other.d); return *this; }
#endif

    bool operator==(const OpenQuant &other) const;
    inline bool operator!=(const OpenQuant &other) const { return !(operator==(other)); }


    static barSeriesList() const;

    static bool() const;
    void setBool(const static& bool);

    static instrumentList() const;

    static orderList() const;

private:
    QSharedDataPointer<Internal::OpenQuantPrivate> d;
};

QDebug OPENTRADE_EXPORT operator << (QDebug, const OpenQuant &openquant);

} // namespace OpenTrade

Q_DECLARE_SHARED(OpenTrade::OpenQuant)

#endif // __OPENTRADE_OPENQUANT_H__
