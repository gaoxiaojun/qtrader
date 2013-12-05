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

#ifndef __BAR_H__
#define __BAR_H__

#include "core_global.h"

#include <QSharedDataPointer>
#include <QMetaType>
#include <QList>
#include <QDateTime>
#include <QDebug>

namespace OpenTrade {

namespace Internal {
  class BarPrivate;
}

class CORE_EXPORT Bar
{
public:
    enum BarType
    {
        NoneBar   = 0,
        TimeBar   = 1,
        TickBar   = 2,
        VolumeBar = 3,
        RangeBar  = 4
    };

    enum BidAsk
    {
        Bid = 0,
        Ask = 1
    };

    enum BarData
    {
        Close    = 0,
        Open     = 1,
        Hight    = 2,
        Low      = 3,
        Median   = 4,
        Typical  = 5,
        Weighted = 6,
        Average  = 7,
        Volume   = 8,
        OpenInt  = 9
    };

    //Bar();
    Bar (const QDateTime& begin, const QDateTime& current, int size,
         Bar::BarType type, double open, double high, double low, double close,
         double volume = 0, double openInt = 0, unsigned int providerId = 0);
    Bar (const Bar& other);
    Bar& operator=(const Bar& other);
    ~Bar();

    void swap(Bar &other) { qSwap(d, other.d); }
#ifdef Q_COMPILER_RVALUE_REFS
    inline Bar &operator=(Bar &&other)
    { qSwap(d, other.d); return *this; }
#endif
    bool operator==(const Bar &other) const;
    inline bool operator!=(const Bar &other) const { return !(operator==(other)); }


    int size() const;
    BarType type() const;

    double open() const;
    double high() const;
    double low() const;
    double close() const;
    double volume() const;
    double openInt() const;
    unsigned int providerId() const;

    QDateTime begin() const;
    QDateTime end() const;
    QDateTime current() const;

    /*void setBegin(const QDateTime& begin);
    void setCurrent(const QDateTime& current);
    void setSize(int size);
    void setType(BarType type);
    void setOpen(double open);
    void setHigh(double high);
    void setLow(double low);
    void setClose(double close);
    void setVolume(double volume);
    void setOpenInt(double openInt);
    void setProviderId(unsigned int providerId);*/

    bool IsComplete() const;

    double average() const;   //平均值
    double typical() const;   //典型值
    double median() const;    //
    double weighted() const;

    double operator [] (BarData barData) const;

private:
    QSharedDataPointer<Internal::BarPrivate> d;
    friend class Internal::BarPrivate;
};

} // namespace OpenTrade

Q_DECLARE_SHARED(OpenTrade::Bar)

QDebug CORE_EXPORT operator<<(QDebug, const OpenTrade::Bar &bar);
//Q_DECLARE_METATYPE(OpenTrade::Bar *)

#endif // __BAR_H__
