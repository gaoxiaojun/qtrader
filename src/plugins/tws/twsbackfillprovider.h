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

#include <opentrade/ibackfillprovider.h>

#include <QString>

namespace TWS {

class TwsBackfillProvider : public OpenTrade::IBackfillProvider
{
    Q_OBJECT
public:
    explicit TwsBackfillProvider(QObject *parent, TwsController *controller);

    ~TwsBackfillProvider();

    // IProvider
    OpenTrade::ProviderInfo* info() const;

    bool isConnected() const;

    void connect();
    void disonnect();
    void shutdown();

    // IHistoricalProvider
    void RequestHistoricalData(const OpenTrade::BackfillRequest& request );
    void CancelHistoricalData(const OpenTrade::BackfillRequest& request );

private slots:
    void hisConnected();
    void hisDisconnected();

private:
    TwsController* m_controller;
    OpenTrade::ProviderInfo* m_info;
    bool m_hisconnect;
};

} // namespace TWS

#endif // TWSHISTORICALPROVIDER_H
