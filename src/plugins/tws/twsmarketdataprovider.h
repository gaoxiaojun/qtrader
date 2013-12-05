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

#include "twsclient.h"
#include "twsproviderinfo.h"

#include <coreplugin/provider/imarketdataprovider.h>
#include <coreplugin/model/instrument.h>

namespace TWS {

class TwsMarketDataProvier : public OpenTrade::IMarketDataProvider
{
    Q_OBJECT

public:
    TwsMarketDataProvier(QObject *parent, TwsClient *client);
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

private:
    TwsClient* m_client;
    QString m_error;
    TwsProviderInfo *m_info;
};

} // namespace TWS

#endif // TWSMARKETDATAPROVIER_H
