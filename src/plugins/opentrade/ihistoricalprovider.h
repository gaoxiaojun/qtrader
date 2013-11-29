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

#ifndef IHISTORICALPROVIDER_HPP
#define IHISTORICALPROVIDER_HPP

#include "opentrade_global.h"
#include "iprovider.h"

#include <QObject>
#include <QString>
#include <QDateTime>

namespace OpenTrade {

class HistoricalDataRequest;

class OPENTRADE_EXPORT IHistoricalProvider: public IProvider
{
    Q_OBJECT

public:
    explicit IHistoricalProvider(QObject *parent): IProvider(parent) {}
    virtual ~IHistoricalProvider() {}

    virtual void RequestHistoricalData(const HistoricalDataRequest& request ) = 0;
    virtual void CancelHistoricalData(const HistoricalDataRequest& request ) = 0;

signals:
    void historicalDataCancelled(const HistoricalDataRequest& request );
    void historicalDataCompleted(const HistoricalDataRequest& request );
    void HistoricalDataError(const HistoricalDataRequest& request, const QString& message );

    void newHistoricalBar(const HistoricalDataRequest& request, const QDateTime& datetime,
                           double open, double high, double low, double close, long volume );
    void newHistoricalQuote(const HistoricalDataRequest& request, const QDateTime& datetime,
                             double bid, int bidSize, double ask, int askSize );
    void newHistoricalTrade(const HistoricalDataRequest& request, const QDateTime& datetime, double price, int size );
};

} // namespace OpenTrade

#endif // IHISTORICALPROVIDER_HPP
