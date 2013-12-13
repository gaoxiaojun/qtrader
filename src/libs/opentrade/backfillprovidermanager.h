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
#include "ibackfillprovider.h"

namespace OpenTrade {

class HistoricalProviderManager : public QObject
{
    Q_OBJECT
public:
    static HistoricalProviderManager *instance();

    explicit HistoricalProviderManager(QObject *parent = 0);
    ~HistoricalProviderManager();

    static QList<IBackfillProvider *> getProviders();

    void initialize();
    void extensionsInitalized();

private slots:
    void objectAdded(QObject *obj);
    void aboutToRemoveObject(QObject *obj);

private slots:
    void historicalDataCancelled(const BackfillRequest& request );
    void historicalDataCompleted(const BackfillRequest& request );
    void HistoricalDataError(const BackfillRequest& request, QString message );

    void newHistoricalBar(const BackfillRequest& request, const QDateTime& datetime,
                           double open, double high, double low, double close, long volume );
    void newHistoricalQuote(const BackfillRequest& request, const QDateTime& datetime,
                             double bid, int bidSize, double ask, int askSize );
    void newHistoricalTrade(const BackfillRequest& request, const QDateTime& datetime, double price, int size );

private:
    void connectToProvider(IBackfillProvider *provider);
    void disconnectToProvider(IBackfillProvider *provider);

    QList<IBackfillProvider *> m_providers;

};

} // namespace OpenTrade
#endif // HistoricalProviderManager_H
