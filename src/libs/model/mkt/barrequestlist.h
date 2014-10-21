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
#ifndef __OPENTRADE_BARREQUESTLIST_H__
#define __OPENTRADE_BARREQUESTLIST_H__

#include "opentrade_global.h"
#include "barrequest.h"

#include <QSharedDataPointer>
#include <QDebug>


namespace OpenTrade {

namespace Internal {
class BarRequestListPrivate;
}

class OPENTRADE_EXPORT BarRequestList
{
public:

    BarRequestList();
    ~BarRequestList();

    BarRequestList& operator=(const BarRequestList &other);
    void swap(BarRequestList &other) { qSwap(d, other.d); }

#ifdef Q_COMPILER_RVALUE_REFS
    inline BarRequestList &operator=(BarRequestList &&other)
    { qSwap(d, other.d); return *this; }
#endif

    bool operator==(const BarRequestList &other) const;
    inline bool operator!=(const BarRequestList &other) const { return !(operator==(other)); }

    void add(const BarRequest& barRequest);
    BarRequest add(BarType barType, long barSize, bool isBarFacroryRequest);
    bool contains(const BarRequest& barRequest);
    bool contains(BarType barType, long barSize);
    bool contains(BarType barType, long barSize, bool isBuiltFromTrades);
    void remove(const BarRequest& barRequest);
    void remove(BarType barType, long barSize);

    int count() const;

private:
    QSharedDataPointer<Internal::BarRequestListPrivate> d;
};

QDebug OPENTRADE_EXPORT operator << (QDebug, const BarRequestList &barrequestlist);

} // namespace OpenTrade

Q_DECLARE_SHARED(OpenTrade::BarRequestList)

#endif // __OPENTRADE_BARREQUESTLIST_H__
