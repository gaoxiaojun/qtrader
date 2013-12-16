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
#ifndef __OPENTRADE_APPEARANCE_H__
#define __OPENTRADE_APPEARANCE_H__

#include "opentrade_global.h"

#include <QSharedDataPointer>
#include <QDebug>


namespace OpenTrade {

namespace Internal {
class AppearancePrivate;
}

class OPENTRADE_EXPORT Appearance
{
public:

    ~Appearance();

    Appearance& operator=(const Appearance &other);
    void swap(Appearance &other) { qSwap(d, other.d); }

#ifdef Q_COMPILER_RVALUE_REFS
    inline Appearance &operator=(Appearance &&other)
    { qSwap(d, other.d); return *this; }
#endif

    bool operator==(const Appearance &other) const;
    inline bool operator!=(const Appearance &other) const { return !(operator==(other)); }


    static font() const;
    void setFont(const static& font);

private:
    QSharedDataPointer<Internal::AppearancePrivate> d;
};

QDebug OPENTRADE_EXPORT operator << (QDebug, const Appearance &appearance);

} // namespace OpenTrade

Q_DECLARE_SHARED(OpenTrade::Appearance)

#endif // __OPENTRADE_APPEARANCE_H__
