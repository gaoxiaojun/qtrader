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

#ifndef HistoricalProviderManager_H
#define HistoricalProviderManager_H

#include <QObject>
#include "provider/ihistoricalprovider.h"

namespace OpenTrade {


class HistoricalProviderManager : public QObject
{
    Q_OBJECT
public:
    static HistoricalProviderManager *instance();

    explicit HistoricalProviderManager(QObject *parent = 0);
    ~HistoricalProviderManager();

    static QList<IHistoricalProvider *> getProviders();

    void init();
    void extensionsInitalized();

private slots:
    void objectAdded(QObject *obj);
    void aboutToRemoveObject(QObject *obj);

private slots:
    void historicalDataCancelled(const HistoricalDataRequest& request );
    void historicalDataCompleted(const HistoricalDataRequest& request );
    void HistoricalDataError(const HistoricalDataRequest& request, QString message );

    void newHistoricalBar(const HistoricalDataRequest& request, const QDateTime& datetime,
                           double open, double high, double low, double close, long volume );
    void newHistoricalQuote(const HistoricalDataRequest& request, const QDateTime& datetime,
                             double bid, int bidSize, double ask, int askSize );
    void newHistoricalTrade(const HistoricalDataRequest& request, const QDateTime& datetime, double price, int size );

private:
    void connectToProvider(IHistoricalProvider *provider);
    void disconnectToProvider(IHistoricalProvider *provider);

    QList<IHistoricalProvider *> m_providers;

};

} // namespace OpenTrade
#endif // HistoricalProviderManager_H
