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

#include <QDateTime>
#include <QVector>

namespace OpenTradeModel {

namespace Internal {
  class BarPrivate;
  class BarSeriesPrivate;
}

class Bar
{
public:
    Bar(const QDateTime& begin, double open, double high, double low, double close, double volume);
    ~Bar();
    QDateTime begin() const;
    double open() const;
    double high() const;
    double low() const;
    double close() const;
    double volume() const;

private:
    Internal::BarPrivate *d;
};


class BarSeries
{
public:
    BarSeries();
    ~BarSeries();

    int count() const;
    const Bar& at(int i) const;
    void append(const Bar& bar);

private:
    Internal::BarSeriesPrivate *d;
};

} // namespace OpenTradeModel

#endif // BAR_H
