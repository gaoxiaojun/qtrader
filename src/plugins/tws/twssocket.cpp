/* Copyright (C) 2013 Interactive Brokers LLC. All rights reserved. This code is subject to the terms
 * and conditions of the IB API Non-Commercial License or the IB API Commercial License, as applicable. */

#include "twssocket.h"

#include "shared/TwsSocketClientErrors.h"
#include "shared/EWrapper.h"

#include <QMutexLocker>

#include <string.h>
#include <errno.h>

namespace TWS {
namespace Internal {

const int WAIT_TIME = 1000;
const int RESERVE_ORDER_ID = 100000;

///////////////////////////////////////////////////////////
// member funcs
TwsSocket::TwsSocket(QObject *parent, EWrapper *ptr) :
    QObject(parent), EClientSocketBase(ptr), m_socket(this)
{
    //qRegisterMetaType<QAbstractSocket::SocketError>();
    connect(&m_socket, SIGNAL(disconnected()), this, SLOT(onClose()));
    connect(&m_socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(socketError(QAbstractSocket::SocketError)));
    connect(&m_socket, SIGNAL(readyRead()), this, SLOT(onReceive()));
}

TwsSocket::~TwsSocket()
{
    disconnect(&m_socket, SIGNAL(disconnected()), this, SLOT(onClose()));
    disconnect(&m_socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(socketError(QAbstractSocket::SocketError)));
    disconnect(&m_socket, SIGNAL(readyRead()), this, SLOT(onReceive()));

    if(isConnected())
        getWrapper()->connectionClosed();
    eDisconnect();
}

bool TwsSocket::eConnect( const char *host, unsigned int port, int clientId)
{
	// already connected?
    if( isConnected ()) {
		getWrapper()->error( NO_VALID_ID, ALREADY_CONNECTED.code(), ALREADY_CONNECTED.msg());
		return false;
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

    if(isConnected())
        onConnect();

    return isConnected();
}

void TwsSocket::eDisconnect()
{
    //QMutexLocker locker(&m_mutex);
    if (m_socket.isValid ())
        m_socket.close ();
    eDisconnectBase();
}

bool TwsSocket::isSocketOK() const
{
    return m_socket.isValid ()  && m_socket.isOpen ();
}

/* Call by EClientSocketBase::sendBufferedData & EClientSocketBase::bufferedSend */
int TwsSocket::send(const char* buf, size_t sz)
{
    return m_socket.write (buf, sz);
}

/* Call by EClientSocketBase::BufferRead
 * BufferRead only call by checkMessages()
 */
int TwsSocket::receive(char* buf, size_t sz)
{
    return m_socket.read(buf, sz);
}

///////////////////////////////////////////////////////////
// callbacks from socket
void TwsSocket::onConnect()
{
    // DETAIL LEVEL, log everything
    setServerLogLevel (5);

    reqIds (RESERVE_ORDER_ID);
    reqCurrentTime ();
}

void TwsSocket::onReceive()
{
    if (isConnected())
        checkMessages();
}

void TwsSocket::onClose()
{
	eDisconnect();
	getWrapper()->connectionClosed();
}

void TwsSocket::socketError(QAbstractSocket::SocketError err)
{
    if (err != QAbstractSocket::RemoteHostClosedError)
        if (isConnected ()) {
            getWrapper()->error( NO_VALID_ID, SOCKET_EXCEPTION.code(),
                SOCKET_EXCEPTION.msg() + m_socket.errorString ().toStdString ());
            onClose();
        }
}

} // namespace Internal

} // namespace TWS
