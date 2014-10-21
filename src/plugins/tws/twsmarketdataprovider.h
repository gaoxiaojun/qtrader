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

#ifndef TWSMARKETDATAPROVIER_H
#define TWSMARKETDATAPROVIER_H

#include "twscontroller.h"
#include "twsproviderinfo.h"

#include <opentrade/imarketdataprovider.h>
#include <opentrade/instrument.h>

namespace TWS {

class TwsMarketDataProvier : public OpenTrade::IMarketDataProvider
{
    Q_OBJECT

public:
    TwsMarketDataProvier(QObject *parent, TwsController *controller);
    ~TwsMarketDataProvier();

    // IProvider
    OpenTrade::ProviderInfo* info() const;
    bool isConnected() const;

    void connect();
    void disonnect();
    void shutdown();

    // IMarketDataProvider
    void subscribe(const OpenTrade::Instrument& instrument);
    void unsubscribe(const OpenTrade::Instrument& instrument);
    QString errorString();

private slots:
    void mktConnected ();
    void mktDisconnected ();

private:
    TwsController* m_controller;
    QString m_error;
    TwsProviderInfo *m_info;
    bool m_mkt_connected;
};

} // namespace TWS

#endif // TWSMARKETDATAPROVIER_H
