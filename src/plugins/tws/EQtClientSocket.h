#ifndef EQtClientSocket_def
#define EQtClientSocket_def

#include "shared/EClientSocketBase.h"

#include <QTcpSocket>
#include <QMutex>

class EWrapper;

class EQtClientSocket : public QObject, public EClientSocketBase
{
public:

    explicit EQtClientSocket( EWrapper *ptr, bool autoReconnect = true);
    ~EQtClientSocket();

	// override virtual funcs from EClient
	bool eConnect( const char *host, unsigned int port, int clientId=0);
	void eDisconnect();

	bool isSocketOK() const;
    //virtual bool checkMessages();
private:

	int send( const char* buf, size_t sz);
	int receive( char* buf, size_t sz);

public:
	// callback from socket
	void onReceive();
	void onSend();
	void onError();

private:

	void onConnect();
	void onClose();


private slots:
    void socketConnected();
    void socketDisconnected();
    void socketError(QAbstractSocket::SocketError socketError);
    void socketHostFound();
    void socketStateChanged(QAbstractSocket::SocketState socketState);
    void socketAboutToClose();
    void socketBytesWritten(qint64 bytes);
    void socketReadyRead();

public:
	// helper
	bool handleSocketError();

private:

    QTcpSocket m_socket;
    QMutex m_login_mutex;
    bool m_autoReconnect;
};

#endif
