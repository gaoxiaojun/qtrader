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

#ifndef BARMANAGER_H
#define BARMANAGER_H

#include "opentrade_global.h"

#include <QObject>

namespace OpenTrade {

class Instrument;
class BarSeries;

namespace Internal {
  class BarManagerPrivate;
}

class OPENTRADE_EXPORT BarManager : public QObject
{
    Q_OBJECT
public:
    BarManager* instance();
    ~BarManager();

    static bool containers(const Instrument& inst, qint64 interval);
    static bool containers(BarSeries* series);
    static BarSeries* createBarSeries(const Instrument&inst, qint64 interval);
    /* getBarSeries: if not container BarSeries, create it and return */
    static BarSeries* getBarSeries(const Instrument&inst, qint64 interval);
    static void addBarSeries(BarSeries* barSeries);
    static BarSeries* addBar(const Instrument& inst, qint64 interval, const QDateTime& begin,
                       double open, double high, double low, double close, double volume);
signals:

public slots:

private:
    explicit BarManager(QObject *parent = 0);
    Q_DISABLE_COPY(BarManager)
    Internal::BarManagerPrivate* d;
};

} // namespace OpenTrade

#endif // BARMANAGER_H
