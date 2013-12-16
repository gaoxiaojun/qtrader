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
#ifndef __OPENTRADE_ALTIDGROUPLIST_H__
#define __OPENTRADE_ALTIDGROUPLIST_H__

#include "opentrade_global.h"
#include "altidgroup.h"

#include <QSharedDataPointer>
#include <QDebug>
#include <QString>


namespace OpenTrade {

namespace Internal {
class AltIDGroupListPrivate;
}

class OPENTRADE_EXPORT AltIDGroupList
{
public:

    ~AltIDGroupList();

    AltIDGroupList& operator=(const AltIDGroupList &other);
    void swap(AltIDGroupList &other) { qSwap(d, other.d); }

#ifdef Q_COMPILER_RVALUE_REFS
    inline AltIDGroupList &operator=(AltIDGroupList &&other)
    { qSwap(d, other.d); return *this; }
#endif

    bool operator==(const AltIDGroupList &other) const;
    inline bool operator!=(const AltIDGroupList &other) const { return !(operator==(other)); }

    AltIDGroup add(const QString& altSource);
    bool contains(const QString& altSource);
    void remove(const QString& altSource);

    int count() const;

private:
    QSharedDataPointer<Internal::AltIDGroupListPrivate> d;
};

QDebug OPENTRADE_EXPORT operator << (QDebug, const AltIDGroupList &altidgrouplist);

} // namespace OpenTrade

Q_DECLARE_SHARED(OpenTrade::AltIDGroupList)

#endif // __OPENTRADE_ALTIDGROUPLIST_H__
