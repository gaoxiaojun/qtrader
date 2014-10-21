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

TwsMarketDataProvier::TwsMarketDataProvier(QObject *parent, TwsController *controller) :
    OpenTrade::IMarketDataProvider(parent),
    m_controller(controller),
    m_mkt_connected(false)
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

    //QObject::connect(m_controller, SIGNAL(mktConnected()), this, SLOT(mktConnected()));
    //QObject::connect (m_controller, SIGNAL(mktDisconnected()), this, SLOT(mktDisconnected()));
}

TwsMarketDataProvier::~TwsMarketDataProvier()
{
}

void TwsMarketDataProvier::subscribe(const OpenTrade::Instrument& instrument)
{
    Q_UNUSED(instrument)
}

void TwsMarketDataProvier::unsubscribe(const OpenTrade::Instrument& instrument)
{
Q_UNUSED(instrument)
}


bool TwsMarketDataProvier::isConnected() const
{
    return m_controller->isConnected() && m_mkt_connected;
}

void TwsMarketDataProvier::connect()
{
    m_mkt_connected = false;
    m_controller->connect ();
}

void TwsMarketDataProvier::disonnect()
{
    m_controller->disconnect ();
    m_mkt_connected = false;
}

void TwsMarketDataProvier::shutdown()
{
    m_mkt_connected = false;
}

OpenTrade::ProviderInfo* TwsMarketDataProvier::info() const
{
    return m_info;
}

void TwsMarketDataProvier::mktConnected ()
{
    qDebug() << "MktData connected";
    m_mkt_connected = true;

    emit connected();
}

void TwsMarketDataProvier::mktDisconnected ()
{
    qDebug() << "MktData disconnected";
    m_mkt_connected = false;

    emit disconnected();
}
