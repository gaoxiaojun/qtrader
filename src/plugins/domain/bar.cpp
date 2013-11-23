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

#include "bar.h"

struct BarPrivate
{
    double Average; // {get;}
    QDateTime BeginTime;// {get;}
    double Close; // {get;}
    QDateTime DateTime;// {get;}
    QTimeSpan Duration;// {get;}
    virtual QDateTime EndTime; //{get;}
    double High; // {get;}
    bool IsComplete();// {get;}
    //double this[ BarData barData ] { get; }
    double Low;// {get;}
    double Median();// {get;}
    double Open;// {get;}
    double OpenInt;// {get;}
    int Size;// {get;}
    Bar::BarType Type;// {get;}
    double Typical;// {get;}
    double Volume;// {get;}
    double Weighted;// {get;}
};

Bar::Bar()
{
}

Bar& Bar::operator=( const Bar& other)
{
    *d = *other.d;
    return *this;
}
