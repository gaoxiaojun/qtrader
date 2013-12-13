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
    connect(&m_socket, SIGNAL(disconnected()), this, SLOT(onClose()));
    connect(&m_socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(socketError(QAbstractSocket::SocketError)));
    connect(&m_socket, SIGNAL(readyRead()), this, SLOT(onReceive()));
}

TwsSocket::~TwsSocket()
{
    if(isConnected())
        getWrapper()->connectionClosed();
    eDisconnect();
}

bool TwsSocket::eConnect( const char *host, unsigned int port, int clientId)
{
    if( isConnected ()) {
		getWrapper()->error( NO_VALID_ID, ALREADY_CONNECTED.code(), ALREADY_CONNECTED.msg());
		return false;
	}

    bool signalBlock = m_socket.blockSignals (true);

    m_socket.connectToHost (host, port);

    bool bConnected = m_socket.waitForConnected (WAIT_TIME);

    if (!bConnected) {
        getWrapper()->error( NO_VALID_ID, CONNECT_FAIL.code(), CONNECT_FAIL.msg());
        goto exit_connect;
    }

    // set client id
	setClientId( clientId);

    onConnectBase();

    m_socket.waitForBytesWritten(WAIT_TIME);

    while(!isConnected()) {
        m_socket.waitForReadyRead(WAIT_TIME);
		if ( !checkMessages()) {
			getWrapper()->error( NO_VALID_ID, CONNECT_FAIL.code(), CONNECT_FAIL.msg());
            goto exit_connect;
		}
    }

    if(isConnected())
        setServerLogLevel (5);

exit_connect:
    m_socket.blockSignals (signalBlock);
    return isConnected();
}

void TwsSocket::eDisconnect()
{
    if (isSocketOK())
        m_socket.close();
    eDisconnectBase();
}

bool TwsSocket::isSocketOK() const
{
    return m_socket.isValid();
}

/* Call by EClientSocketBase::sendBufferedData & EClientSocketBase::bufferedSend */
int TwsSocket::send(const char* buf, size_t sz)
{
    int written = m_socket.write(buf, sz);
    m_socket.flush();
    return written;
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
void TwsSocket::onReceive()
{
    checkMessages();
}

void TwsSocket::onClose()
{
	eDisconnect();
    getWrapper()->connectionClosed();
}

void TwsSocket::socketError(QAbstractSocket::SocketError err)
{
    /* RemoteHostClosedError will be direct processed by onClose
     * to avoid duplicate connectionClosed callback
     */
    if (err != QAbstractSocket::RemoteHostClosedError)
        if (isConnected()) {
            getWrapper()->error( NO_VALID_ID, SOCKET_EXCEPTION.code(),
                SOCKET_EXCEPTION.msg() + m_socket.errorString ().toStdString ());
            onClose();
        }
}

} // namespace Internal

} // namespace TWS
