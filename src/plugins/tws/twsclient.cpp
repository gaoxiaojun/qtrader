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

const int TWS_DEFAULT_PORT = 7496;
const char* TWS_DEFAULT_HOST = "127.0.0.1";

TwsClient *m_instance = 0;

TwsClient *TwsClient::instance()
{
    return m_instance;
}

TwsClient::TwsClient(QObject *parent) :
    QObject(parent), m_tickId(1), m_clientId(1),
    m_host(TWS_DEFAULT_HOST), m_port(TWS_DEFAULT_PORT)
{
    m_wrapper = new Internal::TwsWrapper(this);
    m_socket = new EQtClientSocket(m_wrapper);
    m_socket->moveToThread (&m_thread);
    m_thread.start();
    m_instance = this;
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

bool TwsClient::connect()
{
    return m_socket->eConnect(m_host.toLatin1 ().data (), m_port, m_clientId.fetchAndAddOrdered(1));
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
    m_socket->reqMktData(info->marketData_id, contract, "", false);

    m_socket->reqRealTimeBars (info->realtimeBar_bid_id, contract, 5, "BID", false);
    m_socket->reqRealTimeBars (info->realtimeBar_ask_id, contract, 5, "ASK", false);
}

void TwsClient::removeInfo(Internal::subscribeInfo *info)
{
    if (m_socket->isConnected ()) {
        m_socket->cancelMktData (info->marketData_id);
        m_socket->cancelRealTimeBars (info->realtimeBar_bid_id);
        m_socket->cancelRealTimeBars (info->realtimeBar_ask_id);
    }
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
    return m_socket->isConnected ();
}

void TwsClient::setHost(const QString &host)
{
    m_host = host;
}

void TwsClient::setPort(unsigned int port)
{
    m_port = port;
}

QString TwsClient::host() const
{
    return m_host;
}

unsigned int TwsClient::port () const
{
    return m_port;
}

void TwsClient::readSettings (QSettings* settings)
{
    settings->beginGroup(QLatin1String("Tws"));
    m_host = settings->value(QLatin1String("Host"), TWS_DEFAULT_HOST).toString ();
    m_port = settings->value(QLatin1String("Port"), TWS_DEFAULT_PORT).toInt ();
    settings->endGroup();
}

void TwsClient::writeSettings (QSettings* settings)
{
    settings->beginGroup(QLatin1String("Tws"));
    settings->setValue (QLatin1String("Host"), m_host);
    settings->setValue (QLatin1String("Port"), m_port);
    settings->endGroup();
}

} // namespace TWS
