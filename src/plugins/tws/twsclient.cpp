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
    int realtimeBar_id;
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
    m_socket = new EPosixClientSocket(m_wrapper);
}

TwsClient::~TwsClient()
{
    QList<Internal::subscribeInfo*> values = m_subscribes.values();
    for (int i = 0; i < values.size(); ++i) {
        removeInfo(values.at(i));
    }
    m_subscribes.clear();
    delete m_socket;
    delete m_wrapper;
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
        genericTicks = "233,165";
        break;
    default:
        genericTicks = "233,165";
        break;
    }

    Internal::subscribeInfo *info = new Internal::subscribeInfo();
    info->marketData_id = tickId();
    info->realtimeBar_id = tickId();
    m_subscribes.insert(inst, info);
    m_socket->reqMktData(info->marketData_id, contract, genericTicks, false);

    // realtime bar
    IBString whatToShow;
    switch(instrument.type ()) {
    case OpenTrade::Instrument::Forex:
        whatToShow = "BID_ASK";
        break;
    default:
        genericTicks = "BID_ASK";
        break;
    }
    m_socket->reqRealTimeBars (info->realtimeBar_id, contract, 5, whatToShow, false);
}

void TwsClient::removeInfo(Internal::subscribeInfo *info)
{
    m_socket->cancelMktData (info->marketData_id);
    m_socket->cancelRealTimeBars (info->realtimeBar_id);
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

} // namespace TWS
