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
#ifndef __OPENTRADE_HISTORICALDATAREQUEST_H__
#define __OPENTRADE_HISTORICALDATAREQUEST_H__

#include "opentrade_global.h"
#include "instrument.h"

#include <QSharedDataPointer>
#include <QDebug>
#include <QDateTime>


namespace OpenTrade {

namespace Internal {
class HistoricalDataRequestPrivate;
}

class OPENTRADE_EXPORT HistoricalDataRequest
{
public:

    ~HistoricalDataRequest();

    HistoricalDataRequest& operator=(const HistoricalDataRequest &other);
    void swap(HistoricalDataRequest &other) { qSwap(d, other.d); }

#ifdef Q_COMPILER_RVALUE_REFS
    inline HistoricalDataRequest &operator=(HistoricalDataRequest &&other)
    { qSwap(d, other.d); return *this; }
#endif

    bool operator==(const HistoricalDataRequest &other) const;
    inline bool operator!=(const HistoricalDataRequest &other) const { return !(operator==(other)); }


    long barSize() const;

    QDateTime beginDate() const;

    DataType dataType() const;

    QDateTime endDate() const;

    Instrument instrument() const;

private:
    QSharedDataPointer<Internal::HistoricalDataRequestPrivate> d;
};

QDebug OPENTRADE_EXPORT operator << (QDebug, const HistoricalDataRequest &historicaldatarequest);

} // namespace OpenTrade

Q_DECLARE_SHARED(OpenTrade::HistoricalDataRequest)

#endif // __OPENTRADE_HISTORICALDATAREQUEST_H__
