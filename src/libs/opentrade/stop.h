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
#ifndef __OPENTRADE_STOP_H__
#define __OPENTRADE_STOP_H__

#include "opentrade_global.h"
#include "instrument.h"

#include <QSharedDataPointer>
#include <QDebug>
#include <QDateTime>


namespace OpenTrade {

namespace Internal {
class StopPrivate;
}

class OPENTRADE_EXPORT Stop
{
public:

    ~Stop();

    Stop& operator=(const Stop &other);
    void swap(Stop &other) { qSwap(d, other.d); }

#ifdef Q_COMPILER_RVALUE_REFS
    inline Stop &operator=(Stop &&other)
    { qSwap(d, other.d); return *this; }
#endif

    bool operator==(const Stop &other) const;
    inline bool operator!=(const Stop &other) const { return !(operator==(other)); }

    void cancel();
    void disconnect();
    void setBarFilter(long barSize);
    void setBarFilter(long barSize, BarType barType);

    QDateTime completionTime() const;

    QDateTime creationTime() const;

    double fillPrice() const;

    Instrument instrument() const;

    double level() const;

    StopMode mode() const;

    StopStatus status() const;

    bool traceOnBar() const;
    void setTraceOnBar(const bool& traceonbar);

    bool traceOnQuote() const;
    void setTraceOnQuote(const bool& traceonquote);

    bool traceOnTrade() const;
    void setTraceOnTrade(const bool& traceontrade);

    StopType type() const;

private:
    QSharedDataPointer<Internal::StopPrivate> d;
};

QDebug OPENTRADE_EXPORT operator << (QDebug, const Stop &stop);

} // namespace OpenTrade

Q_DECLARE_SHARED(OpenTrade::Stop)

#endif // __OPENTRADE_STOP_H__
