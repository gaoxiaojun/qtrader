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

#ifndef BAR_H
#define BAR_H

#include "opentrade_global.h"

#include <QDateTime>
#include <QVector>
#include <QDebug>

namespace OpenTrade {

class Instrument;
class BarSeries;

namespace Internal {
  class BarPrivate;
}

class OPENTRADE_EXPORT Bar
{
public:
    Bar();
    Bar(double open, double high, double low, double close, double volume = 0, double openint = 0);
    Bar(const Bar &other);
    ~Bar();

    Bar& operator=(const Bar &other);
    void swap(Bar &other) { qSwap(d, other.d); }

#ifdef Q_COMPILER_RVALUE_REFS
    inline Bar &operator=(Bar &&other)
    { qSwap(d, other.d); return *this; }
#endif

    bool operator==(const Bar &other) const;
    inline bool operator!=(const Bar &other) const { return !(operator==(other)); }

    //QDateTime begin() const;
    //QDateTime end() const;
    //QDateTime current() const;

    bool isValid() const;

    double average() const;   //平均值
    double typical() const;   //典型值
    double median() const;    //
    double weighted() const;

    double open() const;
    double high() const;
    double low() const;
    double close() const;
    double volume() const;
    double tickVol() const;
    double openInt() const; // 未平仓量

private:
    QSharedDataPointer<Internal::BarPrivate> d;
    friend class Internal::BarPrivate;
    friend class BarSeries;
};

QDebug OPENTRADE_EXPORT operator << (QDebug, const Bar &bar);


} // namespace OpenTrade

Q_DECLARE_SHARED(OpenTrade::Bar)

#endif // BAR_H
