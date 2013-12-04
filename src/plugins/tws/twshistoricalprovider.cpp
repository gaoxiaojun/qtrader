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

#include "twshistoricalprovider.h"
#include "twsproviderinfo.h"
#include "twsclient.h"

namespace TWS {

TwsHistoricalProvider::TwsHistoricalProvider(QObject *parent) :
        OpenTrade::IHistoricalProvider(parent)
{
    //Q_ASSERT(m_client != 0);

    TwsProviderInfo* info = new TwsProviderInfo();
    info->m_id = 102;
    info->m_description = "";
    info->m_name = "";
    info->m_compatVersion = "";
    info->m_copyright = "";
    info->m_license = "";
    info->m_vendor = "";
    info->m_version = "";
    info->m_url = "";

    m_info = info;

    //connect(TwsClient::instance (), SIGNAL(twsConnected()),  this, SLOT(onTwsConnected()));
}

TwsHistoricalProvider::~TwsHistoricalProvider()
{
    delete m_info;
}

void TwsHistoricalProvider::RequestHistoricalData(const OpenTrade::HistoricalDataRequest& request )
{

}

void TwsHistoricalProvider::CancelHistoricalData(const OpenTrade::HistoricalDataRequest& request )
{

}

bool TwsHistoricalProvider::isConnected() const
{
    return m_client->isConnected();
}

void TwsHistoricalProvider::connect()
{

}

void TwsHistoricalProvider::disonnect()
{

}

void TwsHistoricalProvider::shutdown()
{

}

OpenTrade::ProviderInfo* TwsHistoricalProvider::info() const
{
    return m_info;
}

} // namespace TWS
