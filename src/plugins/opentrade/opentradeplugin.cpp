#include "OpenTradePlugin.h"
#include "opentradeconstants.h"

/* follow include file for register meta type */
#include "quote.h"
#include "bar.h"
#include "Order.h"

#include <QMetaType>

using namespace OpenTrade::Internal;

OpenTradePlugin::OpenTradePlugin()
{
    //qRegisterMetaType<OpenTrade::Quote*>();
    //qRegisterMetaType<OpenTrade::Bar*>();
}

OpenTradePlugin::~OpenTradePlugin()
{
    // Unregister objects from the plugin manager's object pool
    // Delete members
}

bool OpenTradePlugin::initialize(const QStringList &arguments, QString *errorString)
{
    // Register objects in the plugin manager's object pool
    // Load settings
    // Add actions to menus
    // Connect to other plugins' signals
    // In the initialize function, a plugin can be sure that the plugins it
    // depends on have initialized their members.

    Q_UNUSED(arguments)
    Q_UNUSED(errorString)

    /*QAction *action = new QAction(tr("Domain action"), this);
    Core::Command *cmd = Core::ActionManager::registerAction(action, Constants::ACTION_ID,
                                                             Core::Context(Core::Constants::C_GLOBAL));
    cmd->setDefaultKeySequence(QKeySequence(tr("Ctrl+Alt+Meta+A")));
    connect(action, SIGNAL(triggered()), this, SLOT(triggerAction()));

    Core::ActionContainer *menu = Core::ActionManager::createMenu(Constants::MENU_ID);
    menu->menu()->setTitle(tr("Domain"));
    menu->addAction(cmd);
    Core::ActionManager::actionContainer(Core::Constants::M_TOOLS)->addMenu(menu);*/

    return true;
}

void OpenTradePlugin::extensionsInitialized()
{
    // Retrieve objects from the plugin manager's object pool
    // In the extensionsInitialized function, a plugin can be sure that all
    // plugins that depend on it are completely initialized.
}

ExtensionSystem::IPlugin::ShutdownFlag OpenTradePlugin::aboutToShutdown()
{
    // Save settings
    // Disconnect from signals that are not needed during shutdown
    // Hide UI (if you add UI that is not in the main window directly)
    return SynchronousShutdown;
}

Q_EXPORT_PLUGIN2(Domain, OpenTradePlugin)

