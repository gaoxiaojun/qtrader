#ifndef __TWS_SOCKET_H__
#define __TWS_SOCKET_H__

#include "shared/EClientSocketBase.h"

#include <QTcpSocket>

class EWrapper;

namespace TWS {

namespace Internal {

class TwsSocket : public QObject, public EClientSocketBase
{
    Q_OBJECT

public:
    TwsSocket(QObject *parent, EWrapper *ptr);
    ~TwsSocket();

	// override virtual funcs from EClient
	bool eConnect( const char *host, unsigned int port, int clientId=0);
	void eDisconnect();
    bool isSocketOK() const;
private:

	int send( const char* buf, size_t sz);
	int receive( char* buf, size_t sz);

public slots:
	// callback from socket
    void onConnect();
	void onReceive();
	void onClose();
    void socketError(QAbstractSocket::SocketError);
private:
    QTcpSocket m_socket;
};

} // namespace Internal

} // namespace TWS

#endif // __TWS_SOCKET_H__
