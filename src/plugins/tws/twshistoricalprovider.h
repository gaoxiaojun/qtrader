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

#ifndef TWSHISTORICALPROVIDER_H
#define TWSHISTORICALPROVIDER_H

#include "twscontroller.h"

#include <coreplugin/providermanager/ihistoricalprovider.h>

#include <QString>

namespace TWS {

class TwsHistoricalProvider : public OpenTrade::IHistoricalProvider
{
public:
    explicit TwsHistoricalProvider(QObject *parent);

    ~TwsHistoricalProvider();

    // IProvider
    OpenTrade::ProviderInfo* info() const;

    bool isConnected() const;

    void connect();
    void disonnect();
    void shutdown();

    // IHistoricalProvider
    void RequestHistoricalData(const OpenTrade::HistoricalDataRequest& request );
    void CancelHistoricalData(const OpenTrade::HistoricalDataRequest& request );

public slots:
    void OnTwsConnected();
    void OnTwsDisConnected();
    void OnTwsError(const QString& message);
    void OnTwsError(int errorCode, const QString& message);

private:
    TwsController* m_client;
    OpenTrade::ProviderInfo* m_info;
};

} // namespace TWS

#endif // TWSHISTORICALPROVIDER_H
