
#ifndef TWSPLUGIN_H
#define TWSPLUGIN_H

#include "tws_global.h"
#include "twsclient.h"

#include <extensionsystem/iplugin.h>
#include <coreplugin/actionmanager/command.h>
#include <coreplugin/icore.h>

#include <QtPlugin>

namespace TWS {

namespace Internal {

class TwsPlugin : public ExtensionSystem::IPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QtCreatorPlugin" FILE "Tws.json")

public:

    TwsPlugin();
    virtual ~TwsPlugin();

    // IPlugin
    bool initialize(const QStringList &arguments, QString *errorMessage);
    void extensionsInitialized();
    ShutdownFlag aboutToShutdown();

protected:
    void writeSettings();
    void readSettings();

public slots:
    void connectAction();
    void subscribeAction();
signals:
    void twsFlagsChanged();
private slots:

private:
    TwsClient *m_client;
};

} // namespace Internal
} // namespace TWS

#endif // TWSPLUGIN_H
