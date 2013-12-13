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

#ifndef HISTORICALDATAREQUEST_H
#define HISTORICALDATAREQUEST_H

#include "opentrade_global.h"

#include "instrument.h"

#include <QMetaType>
#include <QDateTime>

namespace OpenTrade {

namespace Internal {
  class BackfillRequestPrivate;
}

class OPENTRADE_EXPORT BackfillRequest
{
public:
    enum RequestDataType {
        Trade  = 0,
        Quote  = 1,
        Bar    = 2,
        Daily  = 3
    };

    BackfillRequest(const Instrument& inst, long barSize, RequestDataType type, const QDateTime& begin, const QDateTime& end);
    BackfillRequest (const BackfillRequest& other);
    BackfillRequest& operator=(const BackfillRequest& other);
    ~BackfillRequest();

    void swap(BackfillRequest &other) { qSwap(d, other.d); }

#ifdef Q_COMPILER_RVALUE_REFS
    inline HistoricalDataRequest &operator=(HistoricalDataRequest &&other)
    { qSwap(d, other.d); return *this; }
#endif

    bool operator==(const BackfillRequest &other) const;
    inline bool operator!=(const BackfillRequest &other) const
    { return !(operator==(other)); }

    Instrument instrument() const;
    long barSize() const;
    RequestDataType type() const;
    QDateTime begin() const;
    QDateTime end() const;

private:
    QSharedDataPointer<Internal::BackfillRequestPrivate> d;
};

} // namespace OpenTrade

Q_DECLARE_SHARED(OpenTrade::BackfillRequest)

#endif // HISTORICALDATAREQUEST_H
