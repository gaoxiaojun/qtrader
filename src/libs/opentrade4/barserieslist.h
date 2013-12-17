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
#ifndef __OPENTRADE_BARSERIESLIST_H__
#define __OPENTRADE_BARSERIESLIST_H__

#include "opentrade_global.h"

#include <QSharedDataPointer>
#include <QDebug>


namespace OpenTrade {

namespace Internal {
class BarSeriesListPrivate;
}

class OPENTRADE_EXPORT BarSeriesList
{
public:

    BarSeriesList();
    ~BarSeriesList();

    BarSeriesList& operator=(const BarSeriesList &other);
    void swap(BarSeriesList &other) { qSwap(d, other.d); }

#ifdef Q_COMPILER_RVALUE_REFS
    inline BarSeriesList &operator=(BarSeriesList &&other)
    { qSwap(d, other.d); return *this; }
#endif

    bool operator==(const BarSeriesList &other) const;
    inline bool operator!=(const BarSeriesList &other) const { return !(operator==(other)); }


private:
    QSharedDataPointer<Internal::BarSeriesListPrivate> d;
};

QDebug OPENTRADE_EXPORT operator << (QDebug, const BarSeriesList &barserieslist);

} // namespace OpenTrade

Q_DECLARE_SHARED(OpenTrade::BarSeriesList)

#endif // __OPENTRADE_BARSERIESLIST_H__
