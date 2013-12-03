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

#include "twsclient.h"

#include "twswrapper.h"

namespace TWS {

namespace Internal {
  // save subscribeInfo for unsubscribe
  struct subscribeInfo {
    int marketData_id;
    int realtimeBar_bid_id;
    int realtimeBar_ask_id;
  };
} // namespace Internal

TwsClient *m_instance = 0;

TwsClient *TwsClient::instance()
{
    return m_instance;
}

TwsClient::TwsClient(QObject *parent) :
    QObject(parent), m_tickId(1)
{
    m_wrapper = new Internal::TwsWrapper(this);
    m_socket = new EQtClientSocket(m_wrapper);
    m_socket->moveToThread (&m_thread);
    m_thread.start();
}

TwsClient::~TwsClient()
{
    QList<Internal::subscribeInfo*> values = m_subscribes.values();
    for (int i = 0; i < values.size(); ++i) {
        removeInfo(values.at(i));
    }
    m_subscribes.clear();

    m_thread.quit();
    m_thread.wait();
    delete m_socket;
    delete m_wrapper;
}

bool TwsClient::connect(const QString& host, unsigned int port, int clientId)
{
    m_host = host;
    m_port = port;
    m_clientId = clientId;
    bool is_connected =  m_socket->eConnect(m_host.toLatin1 ().data (), m_port, m_clientId.fetchAndAddOrdered(1));
    if( is_connected) {
        m_socket->reqCurrentTime ();
        m_socket->reqAllOpenOrders ();
        m_socket->reqIds (1000);
        Contract c;
        c.secType = "CASH";
        c.symbol = "EUR";
        c.exchange = "IDEALPRO";
        c.currency = "USD";
        m_socket->reqMktData (tickId(), c, "165", false);
        m_socket->reqMktData (tickId(), c , "233,mdoff", false);
        m_socket->reqMktDepth (tickId(), c, 10);
        m_socket->reqNewsBulletins (true);
        m_socket->reqRealTimeBars (tickId(), c, 5, "BID", false);
        m_socket->reqRealTimeBars (tickId(), c, 5, "ASK", false);
        m_socket->reqPositions ();
    }
    return is_connected;
}

void TwsClient::disconnect()
{
    m_socket->eDisconnect ();
}

void TwsClient::convertInstrumentToContract(const OpenTrade::Instrument& inst, Contract *contract)
{
    switch(inst.type()) {
    case OpenTrade::Instrument::Forex:
            contract->secType = "CASH";
            contract->symbol = inst.symbol().toStdString();
            contract->exchange = "IDEALPRO";
            contract->currency = inst.currency().toStdString();
        break;
    case OpenTrade::Instrument::Index:
            contract->secType = "IND";
            contract->symbol = inst.symbol().toStdString();
            contract->exchange = inst.exchange().toStdString();
            contract->currency = inst.currency().toStdString();
    default:
        break;
    }
}

TickerId TwsClient::tickId()
{
    return m_tickId.fetchAndAddOrdered(1);
}

void TwsClient::subscribe(const OpenTrade::Instrument &instrument)
{
    OpenTrade::Instrument* inst = const_cast<OpenTrade::Instrument*>(&instrument);
    if(m_subscribes.contains(inst))
        return;

    Contract contract;

    convertInstrumentToContract(instrument, &contract);

    // market data
    IBString genericTicks;
    switch(instrument.type ()) {
    case OpenTrade::Instrument::Forex:
        genericTicks = "165";
        break;
    default:
        genericTicks = "233,165";
        break;
    }

    Internal::subscribeInfo *info = new Internal::subscribeInfo();
    info->marketData_id = tickId();
    info->realtimeBar_bid_id = tickId();
    info->realtimeBar_ask_id = tickId();
    m_subscribes.insert(inst, info);
    m_socket->reqMktData(info->marketData_id, contract, genericTicks, false);

    m_socket->reqRealTimeBars (info->realtimeBar_bid_id, contract, 5, "BID", false);
    m_socket->reqRealTimeBars (info->realtimeBar_ask_id, contract, 5, "ASK", false);
}

void TwsClient::removeInfo(Internal::subscribeInfo *info)
{
    m_socket->cancelMktData (info->marketData_id);
    m_socket->cancelRealTimeBars (info->realtimeBar_bid_id);
    m_socket->cancelRealTimeBars (info->realtimeBar_ask_id);
    delete info;
}

void TwsClient::unsubscribe(const OpenTrade::Instrument& instrument)
{
    OpenTrade::Instrument* inst = const_cast<OpenTrade::Instrument*>(&instrument);
    Internal::subscribeInfo *info = m_subscribes.value(inst);
    if(info) {
        removeInfo(info);
        m_subscribes.remove(inst);
    }
}

bool TwsClient::isConnected () const
{
    return true;
}

} // namespace TWS
