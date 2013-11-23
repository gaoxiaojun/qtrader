#ifndef DOMAIN_HPP
#define DOMAIN_HPP

#include "domain_global.hpp"

#include <extensionsystem/iplugin.h>

namespace Domain {
namespace Internal {

class DomainPlugin : public ExtensionSystem::IPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QtCreatorPlugin")

public:
    DomainPlugin();
    ~DomainPlugin();

    bool initialize(const QStringList &arguments, QString *errorString);
    void extensionsInitialized();
    ShutdownFlag aboutToShutdown();

private slots:
    void triggerAction();
};

} // namespace Internal
} // namespace Domain

#endif // DOMAIN_HPP

