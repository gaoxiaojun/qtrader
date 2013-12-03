#ifndef EQtClientSocket_def
#define EQtClientSocket_def

#include "shared/EClientSocketBase.h"

#include <QTcpSocket>
#include <QMutex>

class EWrapper;

namespace TWS {
class EQtClientSocket : public QObject, public EClientSocketBase
{
    Q_OBJECT

public:

    explicit EQtClientSocket( EWrapper *ptr);
    ~EQtClientSocket();

	// override virtual funcs from EClient
	bool eConnect( const char *host, unsigned int port, int clientId=0);
	void eDisconnect();
    bool isSocketOK() const;
private:

	int send( const char* buf, size_t sz);
	int receive( char* buf, size_t sz);

public slots:
	// callback from socket
	void onReceive();
	void onClose();
    void socketError(QAbstractSocket::SocketError);
private:

    QTcpSocket m_socket;
    QMutex m_login_mutex;
};

} // namespace TWS
#endif
