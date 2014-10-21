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
#ifndef __OPENTRADE_IBEX_H__
#define __OPENTRADE_IBEX_H__

#include "opentrade_global.h"

#include <QSharedDataPointer>
#include <QDebug>
#include <QString>


namespace OpenTrade {

namespace Internal {
class IBExPrivate;
}

class OPENTRADE_EXPORT IBEx
{
public:

    ~IBEx();

    IBEx& operator=(const IBEx &other);
    void swap(IBEx &other) { qSwap(d, other.d); }

#ifdef Q_COMPILER_RVALUE_REFS
    inline IBEx &operator=(IBEx &&other)
    { qSwap(d, other.d); return *this; }
#endif

    bool operator==(const IBEx &other) const;
    inline bool operator!=(const IBEx &other) const { return !(operator==(other)); }


    double displaySize() const;
    void setDisplaySize(double displaysize);

    QString faGroup() const;
    void setFaGroup(const QString& fagroup);

    IBFaMethod faMethod() const;
    void setFaMethod(IBFaMethod famethod);

    double faPercentage() const;
    void setFaPercentage(double fapercentage);

    QString faProfile() const;
    void setFaProfile(const QString& faprofile);

    bool hidden() const;
    void setHidden(bool hidden);

private:
    QSharedDataPointer<Internal::IBExPrivate> d;
};

QDebug OPENTRADE_EXPORT operator << (QDebug, const IBEx &ibex);

} // namespace OpenTrade

Q_DECLARE_SHARED(OpenTrade::IBEx)

#endif // __OPENTRADE_IBEX_H__
