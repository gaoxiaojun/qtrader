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

#ifndef TWSCLIENT_H
#define TWSCLIENT_H

#include "EQtClientSocket.h"
#include <coreplugin/model/instrument.h>
#include <coreplugin/model/order.h>

#include <QObject>
#include <QAtomicInt>
#include <QMap>
#include <QThread>
#include <QSettings>

namespace TWS {

namespace Internal {
  class TwsWrapper;
  class subscribeInfo;
}

class TwsClient : public QObject
{
    Q_OBJECT

public:
    explicit TwsClient(QObject *parent = 0);
    ~TwsClient();
    static TwsClient *instance();

public:
    bool connect();
    void disconnect();
    bool isConnected() const;

    void setHost(const QString& host);
    void setPort(unsigned int port);
    QString host() const;
    unsigned int port() const;

    // market data
    void subscribe(const OpenTrade::Instrument& instrument);
    void unsubscribe(const OpenTrade::Instrument& instrument);

    // order execution
    void send(const OpenTrade::Order& order);
    void cancel(const OpenTrade::Order& order);
    void replace(const OpenTrade::Order& order, double newQty, double newPrice, double newStopPrice);

    // historical

public:
    void readSettings(QSettings* settings);
    void writeSettings(QSettings* settings);
signals:
    void connected();
    void disconnected();

private:
    TickerId tickId();
    void convertInstrumentToContract(const OpenTrade::Instrument& inst, Contract* contract);
    void removeInfo(Internal::subscribeInfo *info);
private:
    Internal::TwsWrapper* m_wrapper;
    EQtClientSocket *m_socket;
    QAtomicInt m_tickId;
    QAtomicInt m_clientId;
    QMap<OpenTrade::Instrument*, Internal::subscribeInfo*> m_subscribes;
    QThread m_thread;
    QString m_host;
    unsigned int m_port;

};

} // namespace TWS

#endif // TWSCLIENT_H
