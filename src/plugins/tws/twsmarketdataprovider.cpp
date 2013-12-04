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

#include "twsmarketdataprovider.h"

using namespace TWS;

TwsMarketDataProvier::TwsMarketDataProvier(QObject *parent, TwsClient *client) :
    OpenTrade::IMarketDataProvider(parent), m_client(client)
{
    TwsProviderInfo* info = new TwsProviderInfo();
    info->m_id = 100;
    info->m_description = "";
    info->m_name = "";
    info->m_compatVersion = "";
    info->m_copyright = "";
    info->m_license = "";
    info->m_vendor = "";
    info->m_version = "";
    info->m_url = "";

    m_info = info;
}

TwsMarketDataProvier::~TwsMarketDataProvier()
{
}

void TwsMarketDataProvier::subscribe(const OpenTrade::Instrument& instrument)
{
    //m_client->
}

void TwsMarketDataProvier::unsubscribe(const OpenTrade::Instrument& instrument)
{

}


bool TwsMarketDataProvier::isConnected() const
{
    return m_client->isConnected();
}

void TwsMarketDataProvier::connect()
{
    m_client->connect ();
}

void TwsMarketDataProvier::disonnect()
{
    m_client->disconnect ();
}

void TwsMarketDataProvier::shutdown()
{

}

OpenTrade::ProviderInfo* TwsMarketDataProvier::info() const
{
    return m_info;
}
