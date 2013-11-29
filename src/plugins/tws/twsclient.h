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

#include "IBJts/source/posixclient/src/EPosixClientSocket.h"
#include <opentrade/instrument.h>

#include <QObject>
#include <QAtomicInt>
#include <QMap>

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

public:
    bool connect(const QString& host, unsigned int port, int clientId=0);
    void disconnect();

    // market data
    void subscribe(const OpenTrade::Instrument& instrument);
    void unsubscribe(const OpenTrade::Instrument& instrument);

    // order execution
    // historical
private:
    TickerId tickId();
    void convertInstrumentToContract(const OpenTrade::Instrument& inst, Contract* contract);
    void removeInfo(Internal::subscribeInfo *info);
private:
    Internal::TwsWrapper* m_wrapper;
    EPosixClientSocket* m_socket;
    QAtomicInt m_tickId;
    QMap<OpenTrade::Instrument*, Internal::subscribeInfo*> m_subscribes;

};

} // namespace TWS

#endif // TWSCLIENT_H
