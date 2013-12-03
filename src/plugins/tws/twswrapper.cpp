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

#include "twswrapper.h"
#include <coreplugin/messagemanager.h>

#include <QDebug>
#include <QDateTime>


using namespace TWS;
using namespace TWS::Internal;

TwsWrapper::TwsWrapper(TwsClient* client) :
    m_client(client)
{
}

TwsWrapper::~TwsWrapper()
{

}

QString TwsWrapper::tickTypeString(TickType field)
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

void TwsWrapper::tickPrice( TickerId tickerId, TickType field, double price, int canAutoExecute)
{
    qDebug() << "[tickPrice]" << tickerId << " " << tickTypeString(field) <<"=" << price << " " << canAutoExecute;
}

void TwsWrapper::tickSize( TickerId tickerId, TickType field, int size)
{
    qDebug() << "[tickSize]" << tickerId << " " << tickTypeString (field) << "=" << size;
}

void TwsWrapper::tickOptionComputation( TickerId tickerId, TickType tickType, double impliedVol, double delta,
    double optPrice, double pvDividend, double gamma, double vega, double theta, double undPrice)
{
    qDebug() << "[tickOptionComputation]" << tickerId << " " << tickTypeString(tickType) <<
                ":vol ";
}

void TwsWrapper::tickGeneric(TickerId tickerId, TickType tickType, double value)
{
    qDebug() << "[tickGeneric]" << tickerId << " " << tickTypeString(tickType) << " " << value;
}

void TwsWrapper::tickString(TickerId tickerId, TickType tickType, const IBString& value)
{
    qDebug() << "[tickString]" << tickerId << " " << tickTypeString (tickType) << " " << QString::fromStdString (value);
}

void TwsWrapper::tickEFP(TickerId tickerId, TickType tickType, double basisPoints, const IBString& formattedBasisPoints,
    double totalDividends, int holdDays, const IBString& futureExpiry, double dividendImpact, double dividendsToExpiry)
{
    qDebug() << "[tickEFP]";
}

void TwsWrapper::orderStatus( OrderId orderId, const IBString &status, int filled,
    int remaining, double avgFillPrice, int permId, int parentId,
    double lastFillPrice, int clientId, const IBString& whyHeld)
{
    qDebug() << "[orderStatus]" << orderId << " status=" << QString::fromStdString (status) << " filled" << filled;
}

void TwsWrapper::openOrder( OrderId orderId, const Contract& contract, const Order&, const OrderState&)
{
    qDebug() << "[openOrder]" << orderId << " symbol" << QString::fromStdString (contract.symbol);
}

void TwsWrapper::openOrderEnd()
{
    qDebug() << "[openOrderEnd]";
}

void TwsWrapper::winError( const IBString &str, int lastError)
{
    qDebug() << "[winError]" << QString::fromStdString (str) << " error]" << lastError;
}

void TwsWrapper::connectionClosed()
{
    qDebug() << "[connectionClosed]";
}

void TwsWrapper::updateAccountValue(const IBString& key, const IBString& val,
const IBString& currency, const IBString& accountName)
{
    qDebug() << "[updateAccountValue]" << " {" << QString::fromStdString (key) << "  " << QString::fromStdString (val) << "} currency" << QString::fromStdString (currency)
                << " account:" << QString::fromStdString (accountName);
}

void TwsWrapper::updatePortfolio( const Contract& contract, int position,
   double marketPrice, double marketValue, double averageCost,
   double unrealizedPNL, double realizedPNL, const IBString& accountName)
{
    qDebug() << "[updatePortfolio]";
}

void TwsWrapper::updateAccountTime(const IBString& timeStamp)
{
    qDebug() << "[updateAccountTime]";
}

void TwsWrapper::accountDownloadEnd(const IBString& accountName)
{
    qDebug() << "[accountDownloadEnd";
}

void TwsWrapper::nextValidId( OrderId orderId)
{
    qDebug() << "[nextValidId]" << orderId;
}

void TwsWrapper::contractDetails( int reqId, const ContractDetails& contractDetails)
{
    qDebug() << "[contractDetails]";
}

void TwsWrapper::bondContractDetails( int reqId, const ContractDetails& contractDetails)
{
    qDebug() << "[bondContractDetails]";
}

void TwsWrapper::contractDetailsEnd( int reqId)
{
    qDebug() << "[contractDetailsEnd]";
}

void TwsWrapper::execDetails( int reqId, const Contract& contract, const Execution& execution)
{
    qDebug() << "[execDetails]";
}

void TwsWrapper::execDetailsEnd( int reqId)
{
    qDebug() << "[execDetailsEnd]";
}

void TwsWrapper::error(const int id, const int errorCode, const IBString errorString)
{
  qDebug() << Q_FUNC_INFO << id << " errorCode" << errorCode <<" : " << QString::fromStdString(errorString);
}

void TwsWrapper::updateMktDepth(TickerId id, int position, int operation, int side,
   double price, int size)
{
    qDebug() << "[execDetailsEnd]";
}

void TwsWrapper::updateMktDepthL2(TickerId id, int position, IBString marketMaker, int operation,
   int side, double price, int size)
{
    qDebug() << "[updateMktDepthL2]";
}

void TwsWrapper::updateNewsBulletin(int msgId, int msgType, const IBString& newsMessage, const IBString& originExch)
{
    qDebug() << "[updateNewsBulletin]";
}

void TwsWrapper::managedAccounts( const IBString& accountsList)
{
    qDebug() << "[managedAccounts]";
}

void TwsWrapper::receiveFA(faDataType pFaDataType, const IBString& cxml)
{
    qDebug() << "[receiveFA]";
}

void TwsWrapper::historicalData(TickerId reqId, const IBString& date, double open, double high,
    double low, double close, int volume, int barCount, double WAP, int hasGaps)
{
    qDebug() << "[historicalData]";
}

void TwsWrapper::scannerParameters(const IBString &xml)
{
    qDebug() << "[scannerParameters]";
}

void TwsWrapper::scannerData(int reqId, int rank, const ContractDetails &contractDetails,
    const IBString &distance, const IBString &benchmark, const IBString &projection,
    const IBString &legsStr)
{
    qDebug() << "[scannerData]";
}

void TwsWrapper::scannerDataEnd(int reqId)
{
    qDebug() << "[scannerDataEnd]";
}

void TwsWrapper::realtimeBar(TickerId reqId, long time, double open, double high, double low, double close,
    long volume, double wap, int count)
{
    qDebug() << "[realtimeBar]" << reqId << " time:" << time << "O:" << open << "H:" << high << "L:" << low << "C:" << close << "V:" << volume;
}

void TwsWrapper::currentTime(long time)
{
    QDateTime dt;
    dt.setTime_t(time);
    qDebug() << "[currentTime]" << dt;
}

void TwsWrapper::fundamentalData(TickerId reqId, const IBString& data)
{
    qDebug() << "[fundamentalData]";
}

void TwsWrapper::deltaNeutralValidation(int reqId, const UnderComp& underComp)
{
    qDebug() << "[deltaNeutralValidation]";
}

void TwsWrapper::tickSnapshotEnd( int reqId)
{
    qDebug() << "[tickSnapshotEnd]";
}

void TwsWrapper::marketDataType( TickerId reqId, int marketDataType)
{
    qDebug() << "[marketDataType]";
}

void TwsWrapper::commissionReport( const CommissionReport &commissionReport)
{
    qDebug() << "[commissionReport]";
}

void TwsWrapper::position( const IBString& account, const Contract& contract, int position)
{
    qDebug() << "[position]";
}

void TwsWrapper::positionEnd()
{
    qDebug() << "[positionEnd]";
}

void TwsWrapper::accountSummary( int reqId, const IBString& account, const IBString& tag, const IBString& value, const IBString& curency)
{
    qDebug() << "[accountSummary]";
}

void TwsWrapper::accountSummaryEnd( int reqId)
{
    qDebug() << "[accountSummaryEnd]";
}
