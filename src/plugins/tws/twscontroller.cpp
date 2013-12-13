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

#include "twscontroller.h"

#include "twsclient.h"

namespace TWS {

namespace Internal {
} // namespace Internal


const QString TWS_DEFAULT_HOST = "127.0.0.1";
const unsigned int TWS_DEFAULT_PORT = 7496;

TwsController *m_instance = 0;

TwsController *TwsController::instance()
{
    return m_instance;
}

TwsController::TwsController(QObject *parent) :
    QObject(parent) //, m_mktconnect(false), m_hisconnect(false)
{
    m_client = new Internal::TwsClient(this);
    m_client->moveToThread (&m_thread);
    m_thread.start();
    m_instance = this;
    QObject::connect(m_client, SIGNAL(mktConnected()), this, SIGNAL(mktConnected()));
    QObject::connect(m_client, SIGNAL(mktDisconnected()), this, SIGNAL(mktDisconnected()));
    QObject::connect(m_client, SIGNAL(hisConnected()), this, SIGNAL(hisConnected()));
    QObject::connect(m_client, SIGNAL(hisDisconnected()), this, SIGNAL(hisDisconnected()));
}

TwsController::~TwsController()
{
    m_thread.quit();
    m_thread.wait();
    delete m_client;
}

void TwsController::connect()
{
    m_client->connect();
}

void TwsController::disconnect()
{
    m_client->disconnect ();
}

void TwsController::subscribe(const OpenTrade::Instrument &instrument)
{
    m_client->subscribe (instrument);
}

void TwsController::unsubscribe(const OpenTrade::Instrument& instrument)
{
    m_client->unsubscribe (instrument);
}

bool TwsController::isConnected () const
{
    return m_client->isConnected ();
}

unsigned int TwsController::serverVersion()
{
    return m_client->serverVersion ();
}

QString TwsController::connectionTime()
{
    return m_client->connectionTime ();
}

void TwsController::setHostAndPort(const QString &host, unsigned int port)
{
    m_client->setHostAndPort (host, port);
}

QString TwsController::host() const
{
    return m_client->host ();
}

unsigned int TwsController::port () const
{
    return m_client->port ();
}
// TODO: maybe bug in readSettings
void TwsController::readSettings (QSettings* settings)
{
    settings->beginGroup(QLatin1String("Tws"));
    QString host = settings->value(QLatin1String("Host"), TWS_DEFAULT_HOST).toString ();
    unsigned int port = settings->value(QLatin1String("Port"), TWS_DEFAULT_PORT).toInt ();
    m_client->setHostAndPort (host, port);
    settings->endGroup();
}

void TwsController::writeSettings (QSettings* settings)
{
    qDebug() << "Write Configure";
    settings->beginGroup(QLatin1String("Tws"));
    settings->setValue (QLatin1String("Host"), m_client->host ());
    settings->setValue (QLatin1String("Port"), m_client->port ());
    settings->endGroup();
}

} // namespace TWS
