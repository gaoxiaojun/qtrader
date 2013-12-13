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
#include "twscontroller.h"

#include <opentrade/account.h>
#include <opentrade/accountmanager.h>

#include <coreplugin/messagemanager.h>

#include <QMutexLocker>
#include <QDebug>
#include <QDateTime>
#include <QMetaObject>
#include <QApplication>

/*
 *  需要记录的内容:
 * 1. 订阅关系,当链接丢失时,恢复订阅关系
 * 2. 保存
 *
 *
 *
 */
namespace TWS {

namespace Internal {
// save subscribeInfo for unsubscribe
class subscribeInfo {
public:
  int marketData_id;
  int realtimeBar_bid_id;
  int realtimeBar_ask_id;
  int marketdepth_id;
};

TwsClient::TwsClient(TwsController* controller) :
    QObject(0), m_controller(controller),
    m_socket(this, static_cast<EWrapper *>(this)),
    m_tickId(1)
{
}

TwsClient::~TwsClient()
{
    // not delete, qt will automatic delete m_socket
    //delete m_socket;

   /* QList<Internal::subscribeInfo*> values = m_subscribes.values();
    for (int i = 0; i < values.size(); ++i) {
        removeInfo(values.at(i));
    }
    m_subscribes.clear();*/
}

QString TwsClient::tickTypeString(TickType field)
{
    switch( field) {
             case BID_SIZE:                    return "bidSize";
             case BID:                         return "bidPrice";
             case ASK:                         return "askPrice";
             case ASK_SIZE:                    return "askSize";
             case LAST:                        return "lastPrice";
             case LAST_SIZE:                   return "lastSize";
             case HIGH:                        return "high";
             case LOW:                         return "low";
             case VOLUME:                      return "volume";
             case CLOSE:                       return "close";
             case BID_OPTION_COMPUTATION:      return "bidOptComp";
             case ASK_OPTION_COMPUTATION:      return "askOptComp";
             case LAST_OPTION_COMPUTATION:     return "lastOptComp";
             case MODEL_OPTION:                return "modelOptComp";
             case OPEN:                        return "open";
             case LOW_13_WEEK:                 return "13WeekLow";
             case HIGH_13_WEEK:                return "13WeekHigh";
             case LOW_26_WEEK:                 return "26WeekLow";
             case HIGH_26_WEEK:                return "26WeekHigh";
             case LOW_52_WEEK:                 return "52WeekLow";
             case HIGH_52_WEEK:                return "52WeekHigh";
             case AVG_VOLUME:                  return "AvgVolume";
             case OPEN_INTEREST:               return "OpenInterest";
             case OPTION_HISTORICAL_VOL:       return "OptionHistoricalVolatility";
             case OPTION_IMPLIED_VOL:          return "OptionImpliedVolatility";
             case OPTION_BID_EXCH:             return "OptionBidExchStr";
             case OPTION_ASK_EXCH:             return "OptionAskExchStr";
             case OPTION_CALL_OPEN_INTEREST:   return "OptionCallOpenInterest";
             case OPTION_PUT_OPEN_INTEREST:    return "OptionPutOpenInterest";
             case OPTION_CALL_VOLUME:          return "OptionCallVolume";
             case OPTION_PUT_VOLUME:           return "OptionPutVolume";
             case INDEX_FUTURE_PREMIUM:        return "IndexFuturePremium";
             case BID_EXCH:                    return "bidExch";
             case ASK_EXCH:                    return "askExch";
             case AUCTION_VOLUME:              return "auctionVolume";
             case AUCTION_PRICE:               return "auctionPrice";
             case AUCTION_IMBALANCE:           return "auctionImbalance";
             case MARK_PRICE:                  return "markPrice";
             case BID_EFP_COMPUTATION:         return "bidEFP";
             case ASK_EFP_COMPUTATION:         return "askEFP";
             case LAST_EFP_COMPUTATION:        return "lastEFP";
             case OPEN_EFP_COMPUTATION:        return "openEFP";
             case HIGH_EFP_COMPUTATION:        return "highEFP";
             case LOW_EFP_COMPUTATION:         return "lowEFP";
             case CLOSE_EFP_COMPUTATION:       return "closeEFP";
             case LAST_TIMESTAMP:              return "lastTimestamp";
             case SHORTABLE:                   return "shortable";
             case FUNDAMENTAL_RATIOS:          return "fundamentals";
             case RT_VOLUME:                   return "RTVolume";
             case HALTED:                      return "halted";
             case BID_YIELD:                   return "bidYield";
             case ASK_YIELD:                   return "askYield";
             case LAST_YIELD:                  return "lastYield";
             case CUST_OPTION_COMPUTATION:     return "custOptComp";
             case TRADE_COUNT:                 return "trades";
             case TRADE_RATE:                  return "trades/min";
             case VOLUME_RATE:                 return "volume/min";
             case LAST_RTH_TRADE:              return "lastRTHTrade";
             default:                          return "unknown";
         }
}

void TwsClient::tickPrice( TickerId tickerId, TickType field, double price, int canAutoExecute)
{
    qDebug() << "[tickPrice]" << tickerId << " " << tickTypeString(field) <<"=" << price << " " << canAutoExecute;
}

void TwsClient::tickSize( TickerId tickerId, TickType field, int size)
{
    qDebug() << "[tickSize]" << tickerId << " " << tickTypeString (field) << "=" << size;
}

void TwsClient::tickOptionComputation( TickerId tickerId, TickType tickType, double impliedVol, double delta,
    double optPrice, double pvDividend, double gamma, double vega, double theta, double undPrice)
{
    qDebug() << "[tickOptionComputation]" << tickerId << " " << tickTypeString(tickType) <<
                ":vol " << impliedVol << delta << optPrice << pvDividend << gamma << vega << theta << undPrice;
}

void TwsClient::tickGeneric(TickerId tickerId, TickType tickType, double value)
{
    QApplication::beep ();
    qDebug() << "[tickGeneric]" << tickerId << " " << tickTypeString(tickType) << " " << value;
}

void TwsClient::tickString(TickerId tickerId, TickType tickType, const IBString& value)
{
    QApplication::beep ();
    qDebug() << "[tickString]" << tickerId << " " << tickTypeString (tickType) << " " << QString::fromStdString (value);
}

void TwsClient::tickEFP(TickerId tickerId, TickType tickType, double basisPoints, const IBString& formattedBasisPoints,
    double totalDividends, int holdDays, const IBString& futureExpiry, double dividendImpact, double dividendsToExpiry)
{
    qDebug() << "[tickEFP]" << tickerId << tickTypeString(tickType) << basisPoints << QString::fromStdString (formattedBasisPoints)
                << totalDividends << holdDays << QString::fromStdString (futureExpiry) << dividendImpact << dividendsToExpiry;
}

void TwsClient::orderStatus( OrderId orderId, const IBString &status, int filled,
    int remaining, double avgFillPrice, int permId, int parentId,
    double lastFillPrice, int clientId, const IBString& whyHeld)
{
    qDebug() << "[orderStatus]" << orderId << " status=" << QString::fromStdString (status) << " filled" << filled
                << remaining << avgFillPrice << permId << parentId << lastFillPrice << clientId
                << QString::fromStdString (whyHeld);
}

void TwsClient::openOrder( OrderId orderId, const Contract& contract, const Order&, const OrderState&)
{
    qDebug() << "[openOrder]" << orderId << " symbol" << QString::fromStdString (contract.symbol);
}

void TwsClient::openOrderEnd()
{
    qDebug() << "[openOrderEnd]";
}

void TwsClient::winError( const IBString &str, int lastError)
{
    qDebug() << "[winError]" << QString::fromStdString (str) << " error]" << lastError;
}

void TwsClient::connectionClosed()
{
    qDebug() << "[connectionClosed]";
}

void TwsClient::updateAccountValue(const IBString& key, const IBString& val,
const IBString& currency, const IBString& accountName)
{
    qDebug() << "[updateAccountValue]" << " {" << QString::fromStdString (key) << "  " << QString::fromStdString (val) << "} currency" << QString::fromStdString (currency)
                << " account:" << QString::fromStdString (accountName);

    QString acctName = QString::fromStdString (accountName);

    OpenTrade::Account * account = OpenTrade::AccountManager::instance ()->value (acctName);

    if (!account) {
        account = OpenTrade::AccountManager::instance()->createAccount (acctName);
        m_account = acctName;
    }

    account->setField (QString::fromStdString (key), QVariant(QString::fromStdString (val)));
}

void TwsClient::updatePortfolio( const Contract& contract, int position,
   double marketPrice, double marketValue, double averageCost,
   double unrealizedPNL, double realizedPNL, const IBString& accountName)
{
    Q_UNUSED(contract)
    qDebug() << "[updatePortfolio]" << position << marketPrice << marketValue << averageCost
                << unrealizedPNL << realizedPNL << QString::fromStdString (accountName);
}

void TwsClient::updateAccountTime(const IBString& timeStamp)
{
    qDebug() << "[updateAccountTime]" << QString::fromStdString (timeStamp);
    QDateTime last = QDateTime::fromString (QString::fromStdString (timeStamp),
                                            "hh:mm");
    last.setDate (QDateTime::currentDateTime ().date ());
    qDebug() << "last:" << last;
    OpenTrade::AccountManager::instance()->value (m_account)->setLastUpdateTime (last);
}

void TwsClient::accountDownloadEnd(const IBString& accountName)
{
    qDebug() << "[accountDownloadEnd" << QString::fromStdString (accountName);
}

void TwsClient::nextValidId( OrderId orderId)
{
    qDebug() << "[nextValidId]" << orderId;
}

void TwsClient::contractDetails( int reqId, const ContractDetails& contractDetails)
{
    Q_UNUSED(contractDetails)
    qDebug() << "[contractDetails]" << reqId;
}

void TwsClient::bondContractDetails( int reqId, const ContractDetails& contractDetails)
{
     Q_UNUSED(contractDetails)
    qDebug() << "[bondContractDetails]" << reqId;
}

void TwsClient::contractDetailsEnd( int reqId)
{
    qDebug() << "[contractDetailsEnd]" << reqId;
}

void TwsClient::execDetails( int reqId, const Contract& contract, const Execution& execution)
{
     Q_UNUSED(contract)
     Q_UNUSED(execution)
    qDebug() << "[execDetails]" << reqId;
}

void TwsClient::execDetailsEnd( int reqId)
{
    qDebug() << "[execDetailsEnd]" << reqId;
}

/*
 * https://www.interactivebrokers.com/en/software/api/apiguide/tables/api_message_codes.htm
 */
void TwsClient::error(const int id, const int errorCode, const IBString errorString)
{

   switch(errorCode) {
    case 1100:
        emit serverLost ();
        break;
    case 1101:
        emit serverRestore ();
        break;
    case 1102:
        emit serverRestoreWithData ();
        break;
    case 2103:
        emit mktDisconnected ();
        break;
    case 2104:
        emit mktConnected ();
        break;
    case 2105:
        emit hisDisconnected ();
        break;
    case 2106:
        emit hisConnected ();
        break;
    case 2110:
        emit serverLostWithAutoRestore();
        break;
    default:
       qDebug() << "id:" << id << "code:" << errorCode << "error:" << QString::fromStdString (errorString);
       break;
   }
}

void TwsClient::updateMktDepth(TickerId id, int position, int operation, int side,
   double price, int size)
{
    QApplication::beep();
    qDebug() << id << position << operation << side << price << size;
}

/*  This function only applies to customers who have subscribed to LII market data
 * (NYSE’s Open Book and NASDAQ’s Total View market data subscriptions).
*/
void TwsClient::updateMktDepthL2(TickerId id, int position, IBString marketMaker, int operation,
   int side, double price, int size)
{
    Q_UNUSED(id)
    Q_UNUSED(position)
    Q_UNUSED(marketMaker)
    Q_UNUSED(operation)
    Q_UNUSED(side)
    Q_UNUSED(price)
    Q_UNUSED(size)
    //qDebug() << "[updateMktDepthL2]" << id << position << QString::fromStdString (marketMaker) << operation
    //            << side << price << size;
}

void TwsClient::updateNewsBulletin(int msgId, int msgType, const IBString& newsMessage, const IBString& originExch)
{
    qDebug() << "[updateNewsBulletin]" << msgId << msgType << QString::fromStdString (newsMessage)
                << QString::fromStdString (originExch);
}

void TwsClient::managedAccounts( const IBString& accountsList)
{
    qDebug() << "[managedAccounts]" << QString::fromStdString (accountsList);
}

void TwsClient::receiveFA(faDataType pFaDataType, const IBString& cxml)
{
    Q_UNUSED(pFaDataType)
    qDebug() << "[receiveFA]" << QString::fromStdString (cxml);
}

void TwsClient::historicalData(TickerId reqId, const IBString& date, double open, double high,
    double low, double close, int volume, int barCount, double WAP, int hasGaps)
{
    qDebug() << "[historicalData]" << reqId << QString::fromStdString (date) << open
                << high << low << close << volume << barCount << WAP << hasGaps;
}

void TwsClient::scannerParameters(const IBString &xml)
{
    qDebug() << "[scannerParameters]" << QString::fromStdString (xml);
}

void TwsClient::scannerData(int reqId, int rank, const ContractDetails &contractDetails,
    const IBString &distance, const IBString &benchmark, const IBString &projection,
    const IBString &legsStr)
{
    Q_UNUSED(contractDetails)
    qDebug() << "[scannerData]" << reqId << rank << QString::fromStdString (distance)
                << QString::fromStdString (benchmark) << QString::fromStdString (projection)
                   << QString::fromStdString (legsStr);
}

void TwsClient::scannerDataEnd(int reqId)
{
    qDebug() << "[scannerDataEnd]" << reqId;
}

void TwsClient::realtimeBar(TickerId reqId, long time, double open, double high, double low, double close,
    long volume, double wap, int count)
{
    qDebug() << "[realtimeBar]" << reqId << " time:" << time << "O:" << open << "H:" << high << "L:" << low
             << "C:" << close << "V:" << volume << "W:" << wap << "Count:" << count;
}

void TwsClient::currentTime(long time)
{
    QDateTime dt;
    dt.setTime_t(time);
    qDebug() << "[currentTime]" << dt;
}

void TwsClient::fundamentalData(TickerId reqId, const IBString& data)
{
    qDebug() << "[fundamentalData]" << reqId << QString::fromStdString (data);
}

void TwsClient::deltaNeutralValidation(int reqId, const UnderComp& underComp)
{
    Q_UNUSED(underComp)
    qDebug() << "[deltaNeutralValidation]" << reqId;
}

void TwsClient::tickSnapshotEnd( int reqId)
{
    qDebug() << "[tickSnapshotEnd]" << reqId;
}

void TwsClient::marketDataType( TickerId reqId, int marketDataType)
{
    qDebug() << "[marketDataType]" << reqId << marketDataType;
}

void TwsClient::commissionReport( const CommissionReport &commissionReport)
{
    Q_UNUSED(commissionReport)
    qDebug() << "[commissionReport]";
}

void TwsClient::position( const IBString& account, const Contract& contract, int position)
{
    Q_UNUSED(contract)
    qDebug() << "[position]" << QString::fromStdString (account) << QString::fromStdString (contract.symbol) << position;
}

void TwsClient::positionEnd()
{
    qDebug() << "[positionEnd]";
}

void TwsClient::accountSummary( int reqId, const IBString& account, const IBString& tag, const IBString& value,
                                const IBString& currency)
{
    qDebug() << "[accountSummary]" << reqId << QString::fromStdString (account) << QString::fromStdString (tag)
                << QString::fromStdString (value) << QString::fromStdString (currency);
}

void TwsClient::accountSummaryEnd( int reqId)
{
    qDebug() << "[accountSummaryEnd]" << reqId;
}

void TwsClient::connect()
{
    if (QThread::currentThread () != this->thread ()) {
        QMetaObject::invokeMethod (this, "connect", Qt::QueuedConnection);
    }
    else {
        qDebug() << "Try connect...";
        m_socket.eConnect (m_host.toLatin1 ().data (), m_port, m_clientId.fetchAndAddOrdered (1));
        if (isConnected()) {
            m_socket.reqAccountUpdates (true, "");
            m_socket.reqAllOpenOrders ();
            m_socket.reqCurrentTime ();
            m_socket.reqIds (1);
            m_socket.reqNewsBulletins (true);
            m_socket.reqPositions ();
        }
    }
}


void TwsClient::disconnect()
{
    if (QThread::currentThread () != this->thread ()) {
        QMetaObject::invokeMethod (this, "disconnect", Qt::QueuedConnection);
    }
    else
        m_socket.eDisconnect ();
}

void TwsClient::reconnect()
{
    qDebug() << "reConnect";
    disconnect();
    connect();
}

bool TwsClient::isConnected ()
{
    return m_socket.isConnected ();
}

QString TwsClient::host()
{
    QMutexLocker locker(&m_mutex);
    return m_host;
}

unsigned int TwsClient::port()
{
    QMutexLocker locker(&m_mutex);
    return m_port;
}

void TwsClient::setHostAndPort(const QString& host, unsigned int port)
{
    if (QThread::currentThread () != this->thread ()) {
        QMetaObject::invokeMethod (this, "setHostAndPort", Qt::QueuedConnection,
                                   Q_ARG(QString, host),
                                   Q_ARG(unsigned int, port));
    }else {
        if ((port != m_port) || (QString::compare (m_host, host.trimmed (), Qt::CaseInsensitive) != 0))
        {
            {
                QMutexLocker locker(&m_mutex);
                m_host = host.trimmed ();
                m_port = port;
                qDebug() << "host:" << m_host << " port:" << m_port;
            }
            if(isConnected()) {
                reconnect();
            }
        }
    }
}

unsigned int TwsClient::serverVersion()
{
    return m_socket.serverVersion ();
}

QString TwsClient::connectionTime()
{
    return QString::fromStdString (m_socket.TwsConnectionTime ());
}


void TwsClient::convertInstrumentToContract(const OpenTrade::Instrument& inst, Contract *contract)
{
    switch(inst.type()) {
    case OpenTrade::Instrument::Forex:
            contract->localSymbol = inst.symbol().toStdString();
            qDebug() << "localSymbol" << QString::fromStdString (contract->localSymbol);
            contract->secType = "CASH";
            contract->exchange = "IDEALPRO";
        break;
    case OpenTrade::Instrument::Stock:
            contract->secType = "STK";
            contract->symbol = inst.symbol().toStdString();
            contract->exchange = inst.exchange().toStdString();
            contract->currency = inst.currency().toStdString();
    case OpenTrade::Instrument::Index:
            contract->secType = "IND";
            contract->symbol = inst.symbol().toStdString();
            contract->exchange = inst.exchange().toStdString();
            contract->currency = inst.currency().toStdString();

    default:
        qWarning() << "Not support instrument type";
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
        genericTicks = "";
        break;
    default:
        genericTicks = "233,165";
        break;
    }


    Internal::subscribeInfo *info = new Internal::subscribeInfo();
    info->marketData_id = tickId();
    info->realtimeBar_bid_id = tickId();
    info->realtimeBar_ask_id = tickId();
    info->marketdepth_id = tickId();
    m_subscribes.insert(inst, info);

    m_socket.reqMktData(info->marketData_id, contract, genericTicks, false);

    m_socket.reqRealTimeBars (info->realtimeBar_bid_id, contract, 5, "BID", false);
    m_socket.reqRealTimeBars (info->realtimeBar_ask_id, contract, 5, "ASK", false);

    m_socket.reqMktDepth (info->marketdepth_id, contract, 10);
}

void TwsClient::removeInfo(Internal::subscribeInfo *info)
{
    if (m_socket.isConnected ()) {
        m_socket.cancelMktData (info->marketData_id);
        m_socket.cancelRealTimeBars (info->realtimeBar_bid_id);
        m_socket.cancelRealTimeBars (info->realtimeBar_ask_id);
        m_socket.cancelMktDepth (info->marketdepth_id);
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
} // namespace Internal

} // namespace TWS
