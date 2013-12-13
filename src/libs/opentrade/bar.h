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
#include <qglobal.h>

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
    Bar(double open, double high, double low, double close, double volume);
    ~Bar();

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

private:
    Internal::BarPrivate *d;
    friend class BarSeries;
};

} // namespace OpenTrade

Q_DECLARE_TYPEINFO(OpenTrade::Bar, Q_MOVABLE_TYPE);

#endif // BAR_H
