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

#ifndef TWSSOCKET_HPP
#define TWSSOCKET_HPP

#include <QTcpSocket>
#include <QThread>

class TwsSocket : public QObject
{
public:
    enum TwsState {
        SocketDisconnected,
        SocketConnected,
        TwsServerConnected,
        TwsServerDisconnected,
        SocketDisconnected
    };

    TwsSocket(QObject *parent);

    connect(const QString& host, unsigned int port);
    disconnect();

signals:
    void TwsSocketError(const QString& errMsg);
    void TwsSocketStatusChanged(TwsState status);

private:
    QTcpSocket m_socket;
    QThread m_thread;
    TwsState m_status;
};

#endif // TWSSOCKET_HPP
