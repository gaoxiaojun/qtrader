/* Copyright (C) 2013 Interactive Brokers LLC. All rights reserved. This code is subject to the terms
 * and conditions of the IB API Non-Commercial License or the IB API Commercial License, as applicable. */

#include "EQtClientSocket.h"

#include "shared/TwsSocketClientErrors.h"
#include "shared/EWrapper.h"

#include <QMutexLocker>

#include <string.h>
#include <errno.h>

///////////////////////////////////////////////////////////
// member funcs
EQtClientSocket::EQtClientSocket( EWrapper *ptr, bool autoReconnect) :
    EClientSocketBase( ptr),
    m_autoReconnect(autoReconnect)
{
    //connect(&m_socket, SIGNAL(connected()), this, SLOT(socketConnected()));
    connect(&m_socket, SIGNAL(disconnected()), this, SLOT(socketDisconnected()));
    connect(&m_socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(socketError(QAbstractSocket::SocketError)));
    //connect(&m_socket, SIGNAL(hostFound()), this, SLOT(socketHostFound()));
    //connect(&m_socket, SIGNAL(stateChanged(QAbstractSocket::SocketState)), this, SLOT(socketStateChanged(QAbstractSocket::SocketState)));
    //connect(&m_socket, SIGNAL(aboutToClose()), this, SLOT(socketAboutToClose()));
    //connect(&m_socket, SIGNAL(bytesWritten(qint64)), this, SLOT(socketBytesWritten(qint64)));
    connect(&m_socket, SIGNAL(readyRead()), this, SLOT(socketReadyRead()));
}

EQtClientSocket::~EQtClientSocket()
{
    //disconnect(&m_socket, SIGNAL(connected()), this, SLOT(socketConnected()));
    disconnect(&m_socket, SIGNAL(disconnected()), this, SLOT(socketDisconnected()));
    disconnect(&m_socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(socketError(QAbstractSocket::SocketError)));
    //disconnect(&m_socket, SIGNAL(hostFound()), this, SLOT(socketHostFound()));
    //disconnect(&m_socket, SIGNAL(stateChanged(QAbstractSocket::SocketState)), this, SLOT(socketStateChanged(QAbstractSocket::SocketState)));
    //disconnect(&m_socket, SIGNAL(aboutToClose()), this, SLOT(socketAboutToClose()));
    //disconnect(&m_socket, SIGNAL(bytesWritten(qint64)), this, SLOT(socketBytesWritten(qint64)));
    disconnect(&m_socket, SIGNAL(readyRead()), this, SLOT(socketReadyRead()));

    if(m_socket.isValid ())
        m_socket.close();
}

bool EQtClientSocket::eConnect( const char *host, unsigned int port, int clientId)
{
    QMutexLocker locker(&m_login_mutex);

	// reset errno
    errno = 0;

	// already connected?
    if( isSocketOK ()) {
		errno = EISCONN;
		getWrapper()->error( NO_VALID_ID, ALREADY_CONNECTED.code(), ALREADY_CONNECTED.msg());
		return false;
	}

    // use local machine if no host passed in
    if ( !( host && *host)) {
        host = "127.0.0.1";
    }

    m_socket.connectToHost (host, port);

    bool is_connected = m_socket.waitForConnected (1000);

    if (!is_connected) {
        getWrapper()->error( NO_VALID_ID, CONNECT_FAIL.code(), CONNECT_FAIL.msg());
        return false;
    }

	// set client id
	setClientId( clientId);

	onConnectBase();

    while( isSocketOK() && !isConnected()) {
		if ( !checkMessages()) {
			getWrapper()->error( NO_VALID_ID, CONNECT_FAIL.code(), CONNECT_FAIL.msg());
			return false;
		}
    }

	// successfully connected
	return true;
}

void EQtClientSocket::eDisconnect()
{
    if (m_socket.isValid ())
        m_socket.close ();
    eDisconnectBase();
}

bool EQtClientSocket::isSocketOK() const
{
    return m_socket.isValid();
}

/* EClientSocketBase sendBufferedData & bufferedSend call send */
int EQtClientSocket::send(const char* buf, size_t sz)
{
    if( sz <= 0)
            return 0;

    int nResult = m_socket.write (buf, sz);

    if( nResult == -1 && !handleSocketError()) {
		return -1;
	}
	if( nResult <= 0) {
		return 0;
	}
    return nResult;
}

/* EClientSocketBase BufferRead call receive
 * BufferRead only called by checkMessages()
 */
int EQtClientSocket::receive(char* buf, size_t sz)
{
    if( sz <= 0)
		return 0;

    int nResult = m_socket.read(buf, sz);

	if( nResult == -1 && !handleSocketError()) {
		return -1;
	}
	if( nResult <= 0) {
		return 0;
	}
    return nResult;
}

///////////////////////////////////////////////////////////
// callbacks from socket

void EQtClientSocket::onConnect()
{
	if( !handleSocketError())
		return;

	onConnectBase();
}

void EQtClientSocket::onReceive()
{
	if( !handleSocketError())
		return;

	checkMessages();
}

void EQtClientSocket::onSend()
{
	if( !handleSocketError())
		return;

	sendBufferedData();
}

void EQtClientSocket::onClose()
{
	if( !handleSocketError())
		return;

	eDisconnect();
	getWrapper()->connectionClosed();
}

void EQtClientSocket::onError()
{
	handleSocketError();
}

///////////////////////////////////////////////////////////
// helper
bool EQtClientSocket::handleSocketError()
{
	// no error
    if( errno == 0)
		return true;

	// Socket is already connected
	if( errno == EISCONN) {
		return true;
	}

	if( errno == EWOULDBLOCK)
		return false;

	if( errno == ECONNREFUSED) {
		getWrapper()->error( NO_VALID_ID, CONNECT_FAIL.code(), CONNECT_FAIL.msg());
	}
	else {
		getWrapper()->error( NO_VALID_ID, SOCKET_EXCEPTION.code(),
			SOCKET_EXCEPTION.msg() + strerror(errno));
	}
	// reset errno
	errno = 0;
	eDisconnect();
    return false;
}

////////////////////////////////////////////////////////////
// slot
void EQtClientSocket::socketDisconnected()
{

}

/*void EQtClientSocket::socketConnected()
{

}*/


void EQtClientSocket::socketError(QAbstractSocket::SocketError socketError)
{

}

/*void EQtClientSocket::socketHostFound()
{

}

void EQtClientSocket::socketStateChanged(QAbstractSocket::SocketState socketState)
{

}

void EQtClientSocket::socketAboutToClose()
{

}

void EQtClientSocket::socketBytesWritten(qint64 bytes)
{

}*/

void EQtClientSocket::socketReadyRead()
{
    checkMessages ();
}
