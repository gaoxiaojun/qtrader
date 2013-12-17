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
#ifndef __OPENTRADE_INSTRUMENTLIST_H__
#define __OPENTRADE_INSTRUMENTLIST_H__

#include "opentrade_global.h"

#include <QSharedDataPointer>
#include <QDebug>


namespace OpenTrade {

namespace Internal {
class InstrumentListPrivate;
}

class OPENTRADE_EXPORT InstrumentList
{
public:

    InstrumentList();
    ~InstrumentList();

    InstrumentList& operator=(const InstrumentList &other);
    void swap(InstrumentList &other) { qSwap(d, other.d); }

#ifdef Q_COMPILER_RVALUE_REFS
    inline InstrumentList &operator=(InstrumentList &&other)
    { qSwap(d, other.d); return *this; }
#endif

    bool operator==(const InstrumentList &other) const;
    inline bool operator!=(const InstrumentList &other) const { return !(operator==(other)); }


    int count() const;

private:
    QSharedDataPointer<Internal::InstrumentListPrivate> d;
};

QDebug OPENTRADE_EXPORT operator << (QDebug, const InstrumentList &instrumentlist);

} // namespace OpenTrade

Q_DECLARE_SHARED(OpenTrade::InstrumentList)

#endif // __OPENTRADE_INSTRUMENTLIST_H__
