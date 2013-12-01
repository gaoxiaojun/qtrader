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
#include <QDebug>

using namespace TWS;
using namespace TWS::Internal;

TwsWrapper::TwsWrapper(TwsClient* client) :
    m_client(client)
{
}

TwsWrapper::~TwsWrapper()
{

}

void TwsWrapper::tickPrice( TickerId tickerId, TickType field, double price, int canAutoExecute)
{

}

void TwsWrapper::tickSize( TickerId tickerId, TickType field, int size)
{

}

void TwsWrapper::tickOptionComputation( TickerId tickerId, TickType tickType, double impliedVol, double delta,
    double optPrice, double pvDividend, double gamma, double vega, double theta, double undPrice)
{

}

void TwsWrapper::tickGeneric(TickerId tickerId, TickType tickType, double value)
{

}

void TwsWrapper::tickString(TickerId tickerId, TickType tickType, const IBString& value)
{

}

void TwsWrapper::tickEFP(TickerId tickerId, TickType tickType, double basisPoints, const IBString& formattedBasisPoints,
    double totalDividends, int holdDays, const IBString& futureExpiry, double dividendImpact, double dividendsToExpiry)
{

}

void TwsWrapper::orderStatus( OrderId orderId, const IBString &status, int filled,
    int remaining, double avgFillPrice, int permId, int parentId,
    double lastFillPrice, int clientId, const IBString& whyHeld)
{

}

void TwsWrapper::openOrder( OrderId orderId, const Contract&, const Order&, const OrderState&)
{

}

void TwsWrapper::openOrderEnd()
{

}

void TwsWrapper::winError( const IBString &str, int lastError)
{

}

void TwsWrapper::connectionClosed()
{

}

void TwsWrapper::updateAccountValue(const IBString& key, const IBString& val,
const IBString& currency, const IBString& accountName)
{

}

void TwsWrapper::updatePortfolio( const Contract& contract, int position,
   double marketPrice, double marketValue, double averageCost,
   double unrealizedPNL, double realizedPNL, const IBString& accountName)
{

}

void TwsWrapper::updateAccountTime(const IBString& timeStamp)
{

}

void TwsWrapper::accountDownloadEnd(const IBString& accountName)
{

}

void TwsWrapper::nextValidId( OrderId orderId)
{

}

void TwsWrapper::contractDetails( int reqId, const ContractDetails& contractDetails)
{

}

void TwsWrapper::bondContractDetails( int reqId, const ContractDetails& contractDetails)
{

}

void TwsWrapper::contractDetailsEnd( int reqId)
{

}

void TwsWrapper::execDetails( int reqId, const Contract& contract, const Execution& execution)
{

}

void TwsWrapper::execDetailsEnd( int reqId)
{

}

void TwsWrapper::error(const int id, const int errorCode, const IBString errorString)
{
  qDebug() << "wrap error id:" << id << " errorCode:" << errorCode <<" errorString:" << QString::fromStdString(errorString); 
}

void TwsWrapper::updateMktDepth(TickerId id, int position, int operation, int side,
   double price, int size)
{

}

void TwsWrapper::updateMktDepthL2(TickerId id, int position, IBString marketMaker, int operation,
   int side, double price, int size)
{

}

void TwsWrapper::updateNewsBulletin(int msgId, int msgType, const IBString& newsMessage, const IBString& originExch)
{

}

void TwsWrapper::managedAccounts( const IBString& accountsList)
{

}

void TwsWrapper::receiveFA(faDataType pFaDataType, const IBString& cxml)
{

}

void TwsWrapper::historicalData(TickerId reqId, const IBString& date, double open, double high,
    double low, double close, int volume, int barCount, double WAP, int hasGaps)
{

}

void TwsWrapper::scannerParameters(const IBString &xml)
{

}

void TwsWrapper::scannerData(int reqId, int rank, const ContractDetails &contractDetails,
    const IBString &distance, const IBString &benchmark, const IBString &projection,
    const IBString &legsStr)
{

}

void TwsWrapper::scannerDataEnd(int reqId)
{

}

void TwsWrapper::realtimeBar(TickerId reqId, long time, double open, double high, double low, double close,
    long volume, double wap, int count)
{

}

void TwsWrapper::currentTime(long time)
{

}

void TwsWrapper::fundamentalData(TickerId reqId, const IBString& data)
{

}

void TwsWrapper::deltaNeutralValidation(int reqId, const UnderComp& underComp)
{

}

void TwsWrapper::tickSnapshotEnd( int reqId)
{

}

void TwsWrapper::marketDataType( TickerId reqId, int marketDataType)
{

}

void TwsWrapper::commissionReport( const CommissionReport &commissionReport)
{

}

void TwsWrapper::position( const IBString& account, const Contract& contract, int position)
{

}

void TwsWrapper::positionEnd()
{

}

void TwsWrapper::accountSummary( int reqId, const IBString& account, const IBString& tag, const IBString& value, const IBString& curency)
{

}

void TwsWrapper::accountSummaryEnd( int reqId)
{

}
