#ifndef TWSDEBUG_H
#define TWSDEBUG_H

#include <QObject>
#include "qtwsclient.h"

class TwsDebug : public QObject
{
    Q_OBJECT
public:
    explicit TwsDebug(QObject *parent = 0);
    //void attachToClient(QTwsClient *client);
    
signals:
    
public slots:
    void twsDisconnected();
    void twsConnected();
    //void twsStateChanged(QTwsClient::twsClientState);
    void tickPrice( TickerId tickerId, TickType field, double price, int canAutoExecute);
    void tickSize( TickerId tickerId, TickType field, int size);
    void tickOptionComputation( TickerId tickerId, TickType tickType, double impliedVol, double delta, double optPrice, double pvDividend, double gamma, double vega, double theta, double undPrice);
    void tickGeneric(TickerId tickerId, TickType tickType, double value);
    void tickString(TickerId tickerId, TickType tickType, const QString& value);
    void tickEFP(TickerId tickerId, TickType tickType, double basisPoints, const QString& formattedBasisPoints, double totalDividends, int holdDays, const QString& futureExpiry, double dividendImpact, double dividendsToExpiry);
    void orderStatus( OrderId orderId, const QString &status, int filled, int remaining, double avgFillPrice, int permId, int parentId, double lastFillPrice, int clientId, const QString& whyHeld);
    void openOrder( OrderId orderId, const Contract&, const Order&, const OrderState&);
    void openOrderEnd();
    void winError( const QString &str, int lastError);
    void connectionClosed();
    void updateAccountValue(const QString& key, const QString& val, const QString& currency, const QString& accountName);
    void updatePortfolio( const Contract& contract, int position, double marketPrice, double marketValue, double averageCost, double unrealizedPNL, double realizedPNL, const QString& accountName);
    void updateAccountTime(const QString& timeStamp);
    void accountDownloadEnd(const QString& accountName);
    void nextValidId( OrderId orderId);
    void contractDetails( int reqId, const ContractDetails& contractDetails);
    void bondContractDetails( int reqId, const ContractDetails& contractDetails);
    void contractDetailsEnd( int reqId);
    void execDetails( int reqId, const Contract& contract, const Execution& execution);
    void execDetailsEnd( int reqId);
    void twsError(const int id, const int errorCode, const QString& errorString);
    void updateMktDepth(TickerId id, int position, int operation, int side, double price, int size);
    void updateMktDepthL2(TickerId id, int position, QString marketMaker, int operation, int side, double price, int size);
    void updateNewsBulletin(int msgId, int msgType, const QString& newsMessage, const QString& originExch);
    void managedAccounts( const QString& accountsList);
    void receiveFA(faDataType pFaDataType, const QString& cxml);
    void historicalData(TickerId reqId, const QString& date, double open, double high, double low, double close, int volume, int barCount, double WAP, int hasGaps);
    void scannerParameters(const QString &xml);
    void scannerData(int reqId, int rank, const ContractDetails &contractDetails, const QString &distance, const QString &benchmark, const QString &projection, const QString &legsStr);
    void scannerDataEnd(int reqId);
    void OnTwsRealtimeBar(TickerId reqId, long time, double open, double high, double low, double close, long volume, double wap, int count);
    void currentTime(long time);
    void fundamentalData(TickerId reqId, const QString& data);
    void deltaNeutralValidation(int reqId, const UnderComp& underComp);
    void tickSnapshotEnd( int reqId);
    void twsMarketDataType( TickerId reqId, int marketDataType);
    void twsCommissionReport( const CommissionReport &commissionReport);
    void twsPosition( const QString& account, const Contract& contract, int position);
    void positionEnd();
    void accountSummary( int reqId, const QString& account, const QString& tag, const QString& value, const QString& curency);
    void accountSummaryEnd( int reqId);
};

#endif // TWSDEBUG_H
