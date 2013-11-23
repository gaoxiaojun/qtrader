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

#ifndef IHISTORICALPROVIDER_HPP
#define IHISTORICALPROVIDER_HPP

#include "domain_global.h"
#include "iprovider.h"

namespace Domain {

class HistoricalDataRequest;

class DOMAIN_EXPORT IHistoricalProvider: public IProvider
{
    Q_OBJECT

public:
    explicit IHistoricalProvider(QObject *parent): IProvider(parent) {}
    virtual ~IHistoricalProvider() {}

    virtual void RequestHistoricalData(const HistoricalDataRequest& request ) = 0;
    virtual void CancelHistoricalData(const HistoricalDataRequest& request ) = 0;

signals:
    void historicalDataCancelled( HistoricalDataRequest request );
    void historicalDataCompleted( HistoricalDataRequest request );
    void HistoricalDataError( HistoricalDataRequest request, string message );

    void newHistoricalBar( HistoricalDataRequest request, const QDateTime& datetime,
                           double open, double high, double low, double close, long volume );
    void newHistoricalQuote( HistoricalDataRequest request, const QDateTime& datetime,
                             double bid, int bidSize, double ask, int askSize );
    void newHistoricalTrade( HistoricalDataRequest request, const QDateTime& datetime, double price, int size );
};

} // namespace Domain

#endif // IHISTORICALPROVIDER_HPP
