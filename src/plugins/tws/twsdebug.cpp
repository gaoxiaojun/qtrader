#include "twsdebug.h"

TwsDebug::TwsDebug(QObject *parent) :
    QObject(parent)
{

}

/*void TwsDebug::attachToClient(QTwsClient *client)
{
    //connect(client, SIGNAL(twsRealtimeBar(long,long,double,double,double,double,long,double,int)), this, SLOT(OnTwsRealtimeBar(long,long,double,double,double,double,long,double,int)));
    connect(client, &QTwsClient::twsRealtimeBar, this, &TwsDebug::OnTwsRealtimeBar);
}*/

void TwsDebug::twsDisconnected(){}
void TwsDebug::twsConnected(){}
//void TwsDebug::twsStateChanged(QTwsClient::twsClientState){}
void TwsDebug::tickPrice( TickerId tickerId, TickType field, double price, int canAutoExecute){}
void TwsDebug::tickSize( TickerId tickerId, TickType field, int size){}
void TwsDebug::tickOptionComputation( TickerId tickerId, TickType tickType, double impliedVol, double delta, double optPrice, double pvDividend, double gamma, double vega, double theta, double undPrice){}
void TwsDebug::tickGeneric(TickerId tickerId, TickType tickType, double value){}
void TwsDebug::tickString(TickerId tickerId, TickType tickType, const QString& value){}
void TwsDebug::tickEFP(TickerId tickerId, TickType tickType, double basisPoints, const QString& formattedBasisPoints, double totalDividends, int holdDays, const QString& futureExpiry, double dividendImpact, double dividendsToExpiry){}
void TwsDebug::orderStatus( OrderId orderId, const QString &status, int filled, int remaining, double avgFillPrice, int permId, int parentId, double lastFillPrice, int clientId, const QString& whyHeld){}
void TwsDebug::openOrder( OrderId orderId, const Contract&, const Order&, const OrderState&){}
void TwsDebug::openOrderEnd(){}
void TwsDebug::winError( const QString &str, int lastError){}
void TwsDebug::connectionClosed(){}
void TwsDebug::updateAccountValue(const QString& key, const QString& val, const QString& currency, const QString& accountName){}
void TwsDebug::updatePortfolio( const Contract& contract, int position, double marketPrice, double marketValue, double averageCost, double unrealizedPNL, double realizedPNL, const QString& accountName){}
void TwsDebug::updateAccountTime(const QString& timeStamp){}
void TwsDebug::accountDownloadEnd(const QString& accountName){}
void TwsDebug::nextValidId( OrderId orderId){}
void TwsDebug::contractDetails( int reqId, const ContractDetails& contractDetails){}
void TwsDebug::bondContractDetails( int reqId, const ContractDetails& contractDetails){}
void TwsDebug::contractDetailsEnd( int reqId){}
void TwsDebug::execDetails( int reqId, const Contract& contract, const Execution& execution){}
void TwsDebug::execDetailsEnd( int reqId){}
void TwsDebug::twsError(const int id, const int errorCode, const QString& errorString){}
void TwsDebug::updateMktDepth(TickerId id, int position, int operation, int side, double price, int size){}
void TwsDebug::updateMktDepthL2(TickerId id, int position, QString marketMaker, int operation, int side, double price, int size){}
void TwsDebug::updateNewsBulletin(int msgId, int msgType, const QString& newsMessage, const QString& originExch){}
void TwsDebug::managedAccounts( const QString& accountsList){}
void TwsDebug::receiveFA(faDataType pFaDataType, const QString& cxml){}
void TwsDebug::historicalData(TickerId reqId, const QString& date, double open, double high, double low, double close, int volume, int barCount, double WAP, int hasGaps){}
void TwsDebug::scannerParameters(const QString &xml){}
void TwsDebug::scannerData(int reqId, int rank, const ContractDetails &contractDetails, const QString &distance, const QString &benchmark, const QString &projection, const QString &legsStr){}
void TwsDebug::scannerDataEnd(int reqId){}
void TwsDebug::OnTwsRealtimeBar(TickerId reqId, long time, double open, double high, double low, double close, long volume, double wap, int count)
{
    qDebug() << " debug id:" << reqId << "time:" << QDateTime::fromTime_t(time) << "O:" << open << "H:" << high << "L:" << low << "C:" << close << "V:" << volume << "W:" << wap << "count:" << count;
}

void TwsDebug::currentTime(long time){}
void TwsDebug::fundamentalData(TickerId reqId, const QString& data){}
void TwsDebug::deltaNeutralValidation(int reqId, const UnderComp& underComp){}
void TwsDebug::tickSnapshotEnd( int reqId){}
void TwsDebug::twsMarketDataType( TickerId reqId, int marketDataType){}
void TwsDebug::twsCommissionReport( const CommissionReport &commissionReport){}
void TwsDebug::twsPosition( const QString& account, const Contract& contract, int position){}
void TwsDebug::positionEnd(){}
void TwsDebug::accountSummary( int reqId, const QString& account, const QString& tag, const QString& value, const QString& curency){}
void TwsDebug::accountSummaryEnd( int reqId){}
