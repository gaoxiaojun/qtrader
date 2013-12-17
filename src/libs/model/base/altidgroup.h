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
#ifndef __OPENTRADE_ALTIDGROUP_H__
#define __OPENTRADE_ALTIDGROUP_H__

#include "opentrade_global.h"

#include <QSharedDataPointer>
#include <QDebug>
#include <QString>


namespace OpenTrade {

namespace Internal {
class AltIDGroupPrivate;
}

class OPENTRADE_EXPORT AltIDGroup
{
public:

    ~AltIDGroup();

    AltIDGroup& operator=(const AltIDGroup &other);
    void swap(AltIDGroup &other) { qSwap(d, other.d); }

#ifdef Q_COMPILER_RVALUE_REFS
    inline AltIDGroup &operator=(AltIDGroup &&other)
    { qSwap(d, other.d); return *this; }
#endif

    bool operator==(const AltIDGroup &other) const;
    inline bool operator!=(const AltIDGroup &other) const { return !(operator==(other)); }


    QString altExchange() const;
    void setAltExchange(const QString& altexchange);

    QString altSource() const;
    void setAltSource(const QString& altsource);

    QString altSymbol() const;
    void setAltSymbol(const QString& altsymbol);

private:
    QSharedDataPointer<Internal::AltIDGroupPrivate> d;
};

QDebug OPENTRADE_EXPORT operator << (QDebug, const AltIDGroup &altidgroup);

} // namespace OpenTrade

Q_DECLARE_SHARED(OpenTrade::AltIDGroup)

#endif // __OPENTRADE_ALTIDGROUP_H__
