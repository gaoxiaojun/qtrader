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

#ifndef __OPENTRADE_IBACKFILL_PROVIDER_H__
#define __OPENTRADE_IBACKFILL_PROVIDER_H__

#include "opentrade_global.h"
#include "iprovider.h"

#include <QString>
#include <QDateTime>

namespace OpenTrade {

class BackfillRequest;

class OPENTRADE_EXPORT IBackfillProvider: public IProvider
{
    Q_OBJECT

public:
    explicit IBackfillProvider(QObject *parent): IProvider(parent) {}
    virtual ~IBackfillProvider() {}

public:
    virtual void RequestHistoricalData(const BackfillRequest& request ) = 0;
    virtual void CancelHistoricalData(const BackfillRequest& request ) = 0;

signals:
    void historicalDataCancelled(const BackfillRequest& request );
    void historicalDataCompleted(const BackfillRequest& request );
    void HistoricalDataError(const BackfillRequest& request, const QString& message );

    void newHistoricalBar(const BackfillRequest& request, const QDateTime& datetime,
                           double open, double high, double low, double close, long volume );
    void newHistoricalQuote(const BackfillRequest& request, const QDateTime& datetime,
                             double bid, int bidSize, double ask, int askSize );
    void newHistoricalTrade(const BackfillRequest& request, const QDateTime& datetime, double price, int size );
};

} // namespace OpenTrade

#endif // __OPENTRADE_IBACKFILL_PROVIDER_H__
