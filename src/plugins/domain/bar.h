/****************************************************************************
**
** Copyright (C) 2013 Xiaojun Gao
** Contact: http://www.dailypips.org/legal
**
** This file is part of QTrader.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Digia gives you certain additional
** rights.  These rights are described in the Digia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
****************************************************************************/

#ifndef __BAR_H__
#define __BAR_H__

#include <QDateTime>

namespace Domain {

class Bar
{
public:
    enum BarType
    {
        Time   = 0,
        Tick   = 1,
        Volume = 2,
        Range  = 3
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

    Bar (const QDateTime& dt, , long size, double open, double high, double low, double close,
        double volume = 0, double openInt = 0);

    Bar (const Bar& other);
    Bar& operator=(const Bar& other);
#ifdef Q_COMPILER_RVALUE_REFS
    inline Bar &operator=(QImage &&other)
    { qSwap(d, other.d); return *this; }
#endif
    ~Bar();


    int size();
    BarType type();

    double open();
    double high();
    double low();
    double close();
    double volume();
    double openInt();

    QDateTime beginTime();
    QDateTime DateTime();
    QTimeSpan duration();
    virtual QDateTime EndTime();

    bool IsComplete();

    double average();   //平均值
    double typical();   //典型值
    double median();    //
    double weighted();

    double operator [] (BarData barData);

private:
    Q_DECLARE_PRIVATE(Bar)
};

} // namespace Domain

#endif // __BAR_H__
