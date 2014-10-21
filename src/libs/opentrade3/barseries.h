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

#ifndef BARSERIES_H
#define BARSERIES_H

#include "opentrade_global.h"

#include <qglobal.h>
#include <QDateTime>

namespace OpenTrade {

class Instrument;
class Bar;

namespace Internal {
  class BarSeriesPrivate;
}

/* BarSeries is a collection of Bar objects ordered in time
 * BarSeries property:
 *  begin:      begin DateTime for BarSeries
 *  interval:   interval between bars, unit is msec
 *  count:      how many bars in the BarSeries
 */

class OPENTRADE_EXPORT BarSeries: public QObject
{
public:
    BarSeries(QObject* parent, const Instrument& inst, qint64 interval);
    ~BarSeries();

    //
    const QDateTime& begin() const;
    qint64 interval() const;
    int count() const;
    const Instrument& instrument() const;

    const Bar& at(int i) const;
    void add(const QDateTime& begin, const Bar& bar);
    void add(const QDateTime& begin, double open, double high, double low, double close, double volume);

    //void updateLast(const QDateTime& begin, double open, double high, double low, double close, double volume);

private:
    Internal::BarSeriesPrivate *d;
};

} // namespace OpenTrade

#endif // BARSERIES_H
