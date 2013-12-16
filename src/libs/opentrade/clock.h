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
#ifndef __OPENTRADE_CLOCK_H__
#define __OPENTRADE_CLOCK_H__

#include "opentrade_global.h"

#include <QSharedDataPointer>
#include <QDebug>


namespace OpenTrade {

namespace Internal {
class ClockPrivate;
}

class OPENTRADE_EXPORT Clock
{
public:

    Clock();
    ~Clock();

    Clock& operator=(const Clock &other);
    void swap(Clock &other) { qSwap(d, other.d); }

#ifdef Q_COMPILER_RVALUE_REFS
    inline Clock &operator=(Clock &&other)
    { qSwap(d, other.d); return *this; }
#endif

    bool operator==(const Clock &other) const;
    inline bool operator!=(const Clock &other) const { return !(operator==(other)); }


    static dateTime() const;

private:
    QSharedDataPointer<Internal::ClockPrivate> d;
};

QDebug OPENTRADE_EXPORT operator << (QDebug, const Clock &clock);

} // namespace OpenTrade

Q_DECLARE_SHARED(OpenTrade::Clock)

#endif // __OPENTRADE_CLOCK_H__
