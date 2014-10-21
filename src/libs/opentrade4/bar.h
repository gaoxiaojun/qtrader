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
#ifndef __OPENTRADE_BAR_H__
#define __OPENTRADE_BAR_H__

#include "opentrade_global.h"

#include <QSharedDataPointer>
#include <QDebug>
#include <QDateTime>


namespace OpenTrade {

namespace Internal {
class BarPrivate;
}

class OPENTRADE_EXPORT Bar
{
public:
    enum BarType {
        TimeBar = 0,
        TickBar = 1,
        VolumeBar = 2,
        RangeBar = 3
    };

    enum BarData {
        Close = 0,
        Open = 1,
        High = 2,
        Low = 3,
        Median = 4,
        Typical = 5,
        Weighted = 6,
        Average = 7,
        Volume = 8,
        OpenInt = 9
    };

public:
    Bar(const QDateTime& dateTime, double open, double high, double low, double close, long volume, long size);
    Bar(const Bar& bar);
    ~Bar();

    Bar& operator=(const Bar &other);
    void swap(Bar &other) { qSwap(d, other.d); }

#ifdef Q_COMPILER_RVALUE_REFS
    inline Bar &operator=(Bar &&other)
    { qSwap(d, other.d); return *this; }
#endif

    bool operator==(const Bar &other) const;
    inline bool operator!=(const Bar &other) const { return !(operator==(other)); }

    double operator[](BarData data) const;

    double average() const;

    QDateTime beginTime() const;

    double close() const;

    QDateTime dateTime() const;

    qint64 duration() const;

    QDateTime endTime() const;

    double high() const;

    bool isComplete() const;

    double low() const;

    double median() const;

    double open() const;

    double openInt() const;

    int size() const;

    BarType type() const;

    double typical() const;

    double volume() const;

    double weighted() const;

private:
    QSharedDataPointer<Internal::BarPrivate> d;
};

QDebug OPENTRADE_EXPORT operator << (QDebug, const Bar &bar);

} // namespace OpenTrade

Q_DECLARE_SHARED(OpenTrade::Bar)

#endif // __OPENTRADE_BAR_H__
