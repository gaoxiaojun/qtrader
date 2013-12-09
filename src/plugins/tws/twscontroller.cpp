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

#include "twscontroller.h"

#include "twsclient.h"

namespace TWS {

namespace Internal {
} // namespace Internal


const QString TWS_DEFAULT_HOST = "127.0.0.1";
const unsigned int TWS_DEFAULT_PORT = 7496;

TwsController *m_instance = 0;

TwsController *TwsController::instance()
{
    return m_instance;
}

TwsController::TwsController(QObject *parent) :
    QObject(parent)
{
    m_client = new Internal::TwsClient(this);
    m_client->moveToThread (&m_thread);
    m_thread.start();
    m_instance = this;
}

TwsController::~TwsController()
{
    m_thread.quit();
    m_thread.wait();
    delete m_client;
}

void TwsController::connect()
{
    m_client->connect();
}

void TwsController::disconnect()
{
    m_client->disconnect ();
}

/*void TwsController::convertInstrumentToContract(const OpenTrade::Instrument& inst, Contract *contract)
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

TickerId TwsController::tickId()
{
    return m_tickId.fetchAndAddOrdered(1);
}*/

void TwsController::subscribe(const OpenTrade::Instrument &instrument)
{
    /*OpenTrade::Instrument* inst = const_cast<OpenTrade::Instrument*>(&instrument);
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
    m_client->reqMktData(info->marketData_id, contract, "", false);

    m_client->reqRealTimeBars (info->realtimeBar_bid_id, contract, 5, "BID", false);
    m_client->reqRealTimeBars (info->realtimeBar_ask_id, contract, 5, "ASK", false);*/
}

/*void TwsController::removeInfo(Internal::subscribeInfo *info)
{
    if (m_client->isConnected ()) {
        m_client->cancelMktData (info->marketData_id);
        m_client->cancelRealTimeBars (info->realtimeBar_bid_id);
        m_client->cancelRealTimeBars (info->realtimeBar_ask_id);
    }
    delete info;
}*/

void TwsController::unsubscribe(const OpenTrade::Instrument& instrument)
{
    /*OpenTrade::Instrument* inst = const_cast<OpenTrade::Instrument*>(&instrument);
    Internal::subscribeInfo *info = m_subscribes.value(inst);
    if(info) {
        removeInfo(info);
        m_subscribes.remove(inst);
    }*/
}

bool TwsController::isConnected () const
{
    return m_client->isConnected ();
}

unsigned int TwsController::serverVersion()
{
    return m_client->serverVersion ();
}

QString TwsController::connectionTime()
{
    return m_client->connectionTime ();
}

void TwsController::setHostAndPort(const QString &host, unsigned int port)
{
    m_client->setHostAndPort (host, port);
}

QString TwsController::host() const
{
    return m_client->host ();
}

unsigned int TwsController::port () const
{
    return m_client->port ();
}
// TODO: maybe bug in readSettings
void TwsController::readSettings (QSettings* settings)
{
    settings->beginGroup(QLatin1String("Tws"));
    QString host = settings->value(QLatin1String("Host"), TWS_DEFAULT_HOST).toString ();
    unsigned int port = settings->value(QLatin1String("Port"), TWS_DEFAULT_PORT).toInt ();
    m_client->setHostAndPort (host, port);
    settings->endGroup();
}

void TwsController::writeSettings (QSettings* settings)
{
    qDebug() << "Write Configure";
    settings->beginGroup(QLatin1String("Tws"));
    settings->setValue (QLatin1String("Host"), m_client->host ());
    settings->setValue (QLatin1String("Port"), m_client->port ());
    settings->endGroup();
}

} // namespace TWS
