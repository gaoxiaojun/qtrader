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

#ifndef TWSWRAPPER_H
#define TWSWRAPPER_H

#include "twssocket.h"
#include "twscontroller.h"

#include "shared/EWrapper.h"
#include "shared/EClient.h"
#include "shared/CommissionReport.h"
#include "shared/CommonDefs.h"
#include "shared/Contract.h"
#include "shared/EClientSocketBase.h"
#include "shared/Execution.h"
#include "shared/IBString.h"
#include "shared/Order.h"
#include "shared/OrderState.h"
#include "shared/ScannerSubscription.h"
#include "shared/TagValue.h"
#include "shared/TwsSocketClientErrors.h"

#include <QObject>
#include <QString>
#include <QMutex>
#include <QAtomicInt>
#include <QMap>
#include <QThread>
#include <QMetaObject>
#include <QStringList>


namespace TWS {

class TwsController;

namespace Internal {

class subscribeInfo;

class TwsClient : public QObject, public EWrapper
{
    Q_OBJECT
public:
    //TwsClient(TwsController* client, const QString& host, unsigned int port);
    explicit TwsClient(TwsController* client);
    ~TwsClient();

    static QString tickTypeString(TickType field);

public:

    QString host();
    unsigned int port();
    Q_INVOKABLE void setHostAndPort(const QString& host, unsigned int port);

public:
    // util
    TickerId tickId();
    void convertInstrumentToContract(const OpenTrade::Instrument& inst, Contract *contract);
    void removeInfo(Internal::subscribeInfo *info);
    // market data
    void subscribe(const OpenTrade::Instrument& instrument);
    void unsubscribe(const OpenTrade::Instrument& instrument);

public:
    Q_INVOKABLE void connect();
    Q_INVOKABLE void disconnect();
    Q_INVOKABLE void reconnect();

public:
    bool isConnected();
signals:
    void serverLost ();
    void serverRestore ();
    void serverRestoreWithData ();
    void serverLostWithAutoRestore();
    void mktConnected();
    void mktDisconnected();
    void hisConnected();
    void hisDisconnected();
private:
    friend class TwsSocket;
    void tickPrice( TickerId tickerId, TickType field, double price, int canAutoExecute);
    void tickSize( TickerId tickerId, TickType field, int size);
    void tickOptionComputation( TickerId tickerId, TickType tickType, double impliedVol, double delta,
        double optPrice, double pvDividend, double gamma, double vega, double theta, double undPrice);
    void tickGeneric(TickerId tickerId, TickType tickType, double value);
    void tickString(TickerId tickerId, TickType tickType, const IBString& value);
    void tickEFP(TickerId tickerId, TickType tickType, double basisPoints, const IBString& formattedBasisPoints,
        double totalDividends, int holdDays, const IBString& futureExpiry, double dividendImpact, double dividendsToExpiry);
    void orderStatus( OrderId orderId, const IBString &status, int filled,
        int remaining, double avgFillPrice, int permId, int parentId,
        double lastFillPrice, int clientId, const IBString& whyHeld);
    void openOrder( OrderId orderId, const Contract&, const Order&, const OrderState&);
    void openOrderEnd();
    void winError( const IBString &str, int lastError);
    void connectionClosed();
    void updateAccountValue(const IBString& key, const IBString& val,
    const IBString& currency, const IBString& accountName);
    void updatePortfolio( const Contract& contract, int position,
       double marketPrice, double marketValue, double averageCost,
       double unrealizedPNL, double realizedPNL, const IBString& accountName);
    void updateAccountTime(const IBString& timeStamp);
    void accountDownloadEnd(const IBString& accountName);
    void nextValidId( OrderId orderId);
    void contractDetails( int reqId, const ContractDetails& contractDetails);
    void bondContractDetails( int reqId, const ContractDetails& contractDetails);
    void contractDetailsEnd( int reqId);
    void execDetails( int reqId, const Contract& contract, const Execution& execution);
    void execDetailsEnd( int reqId);
    void error(const int id, const int errorCode, const IBString errorString);
    void updateMktDepth(TickerId id, int position, int operation, int side,
       double price, int size);
    void updateMktDepthL2(TickerId id, int position, IBString marketMaker, int operation,
       int side, double price, int size);
    void updateNewsBulletin(int msgId, int msgType, const IBString& newsMessage, const IBString& originExch);
    void managedAccounts( const IBString& accountsList);
    void receiveFA(faDataType pFaDataType, const IBString& cxml);
    void historicalData(TickerId reqId, const IBString& date, double open, double high,
        double low, double close, int volume, int barCount, double WAP, int hasGaps);
    void scannerParameters(const IBString &xml);
    void scannerData(int reqId, int rank, const ContractDetails &contractDetails,
        const IBString &distance, const IBString &benchmark, const IBString &projection,
        const IBString &legsStr);
    void scannerDataEnd(int reqId);
    void realtimeBar(TickerId reqId, long time, double open, double high, double low, double close,
        long volume, double wap, int count);
    void currentTime(long time);
    void fundamentalData(TickerId reqId, const IBString& data);
    void deltaNeutralValidation(int reqId, const UnderComp& underComp);
    void tickSnapshotEnd( int reqId);
    void marketDataType( TickerId reqId, int marketDataType);
    void commissionReport( const CommissionReport &commissionReport);
    void position( const IBString& account, const Contract& contract, int position);
    void positionEnd();
    void accountSummary( int reqId, const IBString& account, const IBString& tag, const IBString& value, const IBString& curency);
    void accountSummaryEnd( int reqId);

public:
    unsigned int serverVersion();
    QString connectionTime();
private:
    TwsController* m_controller;
    TwsSocket  m_socket;
    QAtomicInt m_tickId;
    QAtomicInt m_clientId;
    QMap<OpenTrade::Instrument*, subscribeInfo*> m_subscribes;
    QString m_host;
    unsigned int m_port;
    QMutex m_mutex;
    QString m_account;
    QStringList m_FaAccountList;
};

} // namespace Internal
} // namespace TWS

#endif // TWSWRAPPER_H
