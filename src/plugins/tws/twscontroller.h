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

#include "twssocket.h"

#include <opentrade/instrument.h>
#include <opentrade/order.h>

#include <QThread>
#include <QSettings>

namespace TWS {

namespace Internal {
  class TwsClient;
}

class TwsController : public QObject
{
    Q_OBJECT

public:
    explicit TwsController(QObject *parent = 0);
    ~TwsController();
    static TwsController *instance();

public:
    void connect();
    void disconnect();
    bool isConnected() const;
    //bool isMktConnected() const { return m_mktconnect; }
    //bool isHisConnected() const { return m_hisconnect; }

    //
    QString host() const;
    unsigned int port () const;

    void setHostAndPort(const QString& host, unsigned int port);

    // market data
    void subscribe(const OpenTrade::Instrument& instrument);
    void unsubscribe(const OpenTrade::Instrument& instrument);

    // order execution
    void send(const OpenTrade::Order& order);
    void cancel(const OpenTrade::Order& order);
    void replace(const OpenTrade::Order& order, double newQty, double newPrice, double newStopPrice);

    // historical
    void RequestHistoricalData(const OpenTrade::Instrument& instrument, int barSize, const QDateTime& begin, const QDateTime& end);
    //void CancelHistoricalData(const OpenTrade::HistoricalDataRequest& request );

    // account info

    // instrument list

    // client info
    unsigned int serverVersion();
    QString connectionTime();

public:
    void readSettings(QSettings* settings);
    void writeSettings(QSettings* settings);

signals:
    void mktConnected();
    void mktDisconnected();
    void hisConnected();
    void hisDisconnected();

private:
    Internal::TwsClient *m_client;
    QThread m_thread;
};

} // namespace TWS

#endif // TWSCLIENT_H
