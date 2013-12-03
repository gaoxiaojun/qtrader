/* Copyright (C) 2013 Interactive Brokers LLC. All rights reserved. This code is subject to the terms
 * and conditions of the IB API Non-Commercial License or the IB API Commercial License, as applicable. */

#include "eqtclientsocket.h"

#include "shared/TwsSocketClientErrors.h"
#include "shared/EWrapper.h"

#include <QMutexLocker>

#include <string.h>
#include <errno.h>

using namespace TWS;

const int WAIT_TIME = 1000;
///////////////////////////////////////////////////////////
// member funcs
EQtClientSocket::EQtClientSocket( EWrapper *ptr) :
    EClientSocketBase( ptr)
{
    qRegisterMetaType<QAbstractSocket::SocketError>();
    connect(&m_socket, SIGNAL(disconnected()), this, SLOT(onClose()));
    connect(&m_socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(socketError(QAbstractSocket::SocketError)));
    connect(&m_socket, SIGNAL(readyRead()), this, SLOT(onReceive()));
}

EQtClientSocket::~EQtClientSocket()
{
    disconnect(&m_socket, SIGNAL(disconnected()), this, SLOT(onClose()));
    disconnect(&m_socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(socketError(QAbstractSocket::SocketError)));
    disconnect(&m_socket, SIGNAL(readyRead()), this, SLOT(onReceive()));

    if(isConnected())
        getWrapper()->connectionClosed();
    eDisconnect();
}

bool EQtClientSocket::eConnect( const char *host, unsigned int port, int clientId)
{
    QMutexLocker locker(&m_login_mutex);

    qDebug() << "eConnect..." << host << ":" << port << ":" << clientId;

	// already connected?
    if( isConnected ()) {
		errno = EISCONN;
		getWrapper()->error( NO_VALID_ID, ALREADY_CONNECTED.code(), ALREADY_CONNECTED.msg());
		return false;
	}

    // use local machine if no host passed in
    if ( !( host && *host)) {
        host = "127.0.0.1";
    }

    m_socket.connectToHost (host, port);

    bool bConnected = m_socket.waitForConnected (WAIT_TIME);

    if (!bConnected) {
        getWrapper()->error( NO_VALID_ID, CONNECT_FAIL.code(), CONNECT_FAIL.msg());
        return false;
    }

    // set client id
	setClientId( clientId);

	onConnectBase();

    m_socket.waitForBytesWritten(WAIT_TIME);

    while(!isConnected()) {
        m_socket.waitForReadyRead(WAIT_TIME);
		if ( !checkMessages()) {
			getWrapper()->error( NO_VALID_ID, CONNECT_FAIL.code(), CONNECT_FAIL.msg());
			return false;
		}
    }

    return isConnected();
}

void EQtClientSocket::eDisconnect()
{
    if (m_socket.isValid ())
        m_socket.close ();
    eDisconnectBase();
}

bool EQtClientSocket::isSocketOK() const
{
    return m_socket.isValid ()  && m_socket.isOpen ();
}

/* Call by EClientSocketBase::sendBufferedData & EClientSocketBase::bufferedSend */
int EQtClientSocket::send(const char* buf, size_t sz)
{
    return m_socket.write (buf, sz);
}

/* Call by EClientSocketBase::BufferRead
 * BufferRead only call by checkMessages()
 */
int EQtClientSocket::receive(char* buf, size_t sz)
{
    return m_socket.read(buf, sz);
}

///////////////////////////////////////////////////////////
// callbacks from socket

void EQtClientSocket::onReceive()
{
	checkMessages();
}

void EQtClientSocket::onClose()
{
	eDisconnect();
	getWrapper()->connectionClosed();
}

void EQtClientSocket::socketError(QAbstractSocket::SocketError err)
{
    if (err != QAbstractSocket::RemoteHostClosedError)
        if (isConnected ()) {
            getWrapper()->error( NO_VALID_ID, SOCKET_EXCEPTION.code(),
                SOCKET_EXCEPTION.msg() + m_socket.errorString ().toStdString ());
            onClose();
        }
}
