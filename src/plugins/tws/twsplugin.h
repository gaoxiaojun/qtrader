
#ifndef TWSPLUGIN_H
#define TWSPLUGIN_H

#include "tws_global.h"

#include <extensionsystem/iplugin.h>

#include <QtPlugin>

QT_BEGIN_NAMESPACE
QT_END_NAMESPACE

namespace Tws {
class TwsPluginPrivate;

namespace Internal {
class TwsToolBar;
class CurrentDocumentTws;
} // namespace Internal

class TWS_EXPORT TwsPlugin : public ExtensionSystem::IPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QtCreatorPlugin" FILE "Tws.json")

public:
    TwsPlugin();
    virtual ~TwsPlugin();
    static TwsPlugin *instance();

    enum TwsDirection {
        TwsForwardDirection,
        TwsBackwardDirection
    };

    // IPlugin
    bool initialize(const QStringList &arguments, QString *errorMessage);
    void extensionsInitialized();
    ShutdownFlag aboutToShutdown();

protected:
    void writeSettings();
    void readSettings();

public slots:

signals:
    void twsFlagsChanged();
private slots:

private:

    //variables
    TwsPluginPrivate *d;
};

} // namespace Tws

#endif // TWSPLUGIN_H
