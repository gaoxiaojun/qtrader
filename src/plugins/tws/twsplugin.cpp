
#include "twsplugin.h"
#include "twsconstants.h"

#include "twsmarketdataprovider.h"
#include "twsoptionspage.h"
#include "twsorderexecutionprovider.h"
#include "twshistoricalprovider.h"

#include <coreplugin/icore.h>
#include <coreplugin/icontext.h>
#include <coreplugin/actionmanager/actionmanager.h>
#include <coreplugin/actionmanager/command.h>
#include <coreplugin/actionmanager/actioncontainer.h>
#include <coreplugin/coreconstants.h>
#include <extensionsystem/pluginmanager.h>

#include <QAction>
#include <QMessageBox>
#include <QMainWindow>
#include <QMenu>
#include <QSettings>
#include <QtPlugin>

namespace TWS {

namespace Internal {

TwsPlugin::TwsPlugin()
{
}

TwsPlugin::~TwsPlugin()
{
}

bool TwsPlugin::initialize(const QStringList &, QString *)
{

    QAction *connectAction = new QAction(tr("Connect"), this);
    Core::Command *connectCmd = Core::ActionManager::registerAction(connectAction, Constants::TWS_CONNECT_ACTION_ID,
                                                                 Core::Context(Core::Constants::C_GLOBAL));
    connectCmd->setDefaultKeySequence(QKeySequence(tr("Ctrl+Alt+Meta+C")));
    connect(connectAction, SIGNAL(triggered()), this, SLOT(connectAction()));

    QAction *subscribeAction = new QAction(tr("Subscribe"), this);
    Core::Command *subscibeCmd = Core::ActionManager::registerAction(subscribeAction, Constants::TWS_SUBSCRIBE_ACTION_ID,
                                                                 Core::Context(Core::Constants::C_GLOBAL));
    subscibeCmd->setDefaultKeySequence(QKeySequence(tr("Ctrl+Alt+Meta+S")));
    connect(subscribeAction, SIGNAL(triggered()), this, SLOT(subscribeAction()));

    QAction *unsubscribeAction = new QAction(tr("Unsubscribe"), this);
    Core::Command *unsubscibeCmd = Core::ActionManager::registerAction(unsubscribeAction, Constants::TWS_UNSUBSCRIBE_ACTION_ID,
                                                                 Core::Context(Core::Constants::C_GLOBAL));
    unsubscibeCmd->setDefaultKeySequence(QKeySequence(tr("Ctrl+Alt+Meta+U")));
    connect(unsubscribeAction, SIGNAL(triggered()), this, SLOT(unsubscribeAction()));

    QAction *disconnectAction = new QAction(tr("Disconnect"), this);
    Core::Command *disconnectCmd = Core::ActionManager::registerAction(disconnectAction, Constants::TWS_DISCONNECT_ACTION_ID,
                                                                 Core::Context(Core::Constants::C_GLOBAL));
    disconnectCmd->setDefaultKeySequence(QKeySequence(tr("Ctrl+Alt+Meta+D")));
    connect(disconnectAction, SIGNAL(triggered()), this, SLOT(disconnectAction()));

    Core::ActionContainer *menu = Core::ActionManager::createMenu(Constants::TWS_MENU_ID);
    menu->menu()->setTitle(tr("TWS"));
    menu->addAction(connectCmd);
    menu->addAction (subscibeCmd);
    menu->addAction(unsubscibeCmd);
    menu->addAction(disconnectCmd);
    Core::ActionManager::actionContainer(Core::Constants::M_TOOLS)->addMenu(menu);

    m_controller = new TwsController(this);
    addAutoReleasedObject(new TwsMarketDataProvier(this, m_controller));
    //addAutoReleasedObject(new TwsHistoricalProvider(this));
    //addAutoReleasedObject(new TwsOrderExecutionProvider(this));
    addAutoReleasedObject (new TwsOptionsPage(this));
    return true;
}

void TwsPlugin::extensionsInitialized()
{
    readSettings();
}

ExtensionSystem::IPlugin::ShutdownFlag TwsPlugin::aboutToShutdown()
{
    writeSettings();
    return SynchronousShutdown;
}

/*void TwsPlugin::setupMenu()
{
    Core::ActionContainer *medit = Core::ActionManager::actionContainer(Core::Constants::M_EDIT);
    Core::ActionContainer *mtws = Core::ActionManager::createMenu(Constants::M_FIND);
    medit->addMenu(mtws, Core::Constants::G_EDIT_FIND);
    mtws->menu()->setTitle(tr("&Tws/Replace"));
    mtws->appendGroup(Constants::G_FIND_CURRENTDOCUMENT);
    mtws->appendGroup(Constants::G_FIND_FILTERS);
    mtws->appendGroup(Constants::G_FIND_FLAGS);
    mtws->appendGroup(Constants::G_FIND_ACTIONS);
    Core::Context globalcontext(Core::Constants::C_GLOBAL);
    Core::Command *cmd;
    mtws->addSeparator(globalcontext, Constants::G_FIND_FLAGS);
    mtws->addSeparator(globalcontext, Constants::G_FIND_ACTIONS);

    Core::ActionContainer *mtwsadvanced = Core::ActionManager::createMenu(Constants::M_FIND_ADVANCED);
    mtwsadvanced->menu()->setTitle(tr("Advanced Tws"));
    mtws->addMenu(mtwsadvanced, Constants::G_FIND_FILTERS);
    d->m_openTwsDialog = new QAction(tr("Open Advanced Tws..."), this);
    d->m_openTwsDialog->setIconText(tr("Advanced..."));
    cmd = Core::ActionManager::registerAction(d->m_openTwsDialog, Constants::ADVANCED_FIND, globalcontext);
    cmd->setDefaultKeySequence(QKeySequence(tr("Ctrl+Shift+F")));
    mtwsadvanced->addAction(cmd);
    connect(d->m_openTwsDialog, SIGNAL(triggered()), this, SLOT(openTwsFilter()));
}

void TwsPlugin::setupFilterMenuItems()
{
    QList<ITwsFilter*> twsInterfaces =
        ExtensionSystem::PluginManager::getObjects<ITwsFilter>();
    Core::Command *cmd;
    Core::Context globalcontext(Core::Constants::C_GLOBAL);

    Core::ActionContainer *mtwsadvanced = Core::ActionManager::actionContainer(Constants::M_FIND_ADVANCED);
    d->m_filterActions.clear();
    bool haveEnabledFilters = false;
    const Core::Id base("TwsFilter.");
    foreach (ITwsFilter *filter, twsInterfaces) {
        QAction *action = new QAction(QLatin1String("    ") + filter->displayName(), this);
        bool isEnabled = filter->isEnabled();
        if (isEnabled)
            haveEnabledFilters = true;
        action->setEnabled(isEnabled);
        action->setData(qVariantFromValue(filter));
        cmd = Core::ActionManager::registerAction(action,
            base.withSuffix(filter->id()), globalcontext);
        cmd->setDefaultKeySequence(filter->defaultShortcut());
        mtwsadvanced->addAction(cmd);
        d->m_filterActions.insert(filter, action);
        connect(action, SIGNAL(triggered(bool)), this, SLOT(openTwsFilter()));
        connect(filter, SIGNAL(enabledChanged(bool)), this, SLOT(filterChanged()));
    }
    d->m_twsDialog->setTwsFilters(twsInterfaces);
    d->m_openTwsDialog->setEnabled(haveEnabledFilters);
}*/

void TwsPlugin::writeSettings()
{
    QSettings *settings = Core::ICore::settings();
    m_controller->writeSettings (settings);
}

void TwsPlugin::readSettings()
{
    QSettings *settings = Core::ICore::settings();
    m_controller->readSettings (settings);
    emit twsFlagsChanged(); // would have been done in the setXXX methods above
}

void TwsPlugin::connectAction()
{
    /*if (m_controller->connect ()) {
        qDebug() << "serverVersion:" << m_controller->serverVersion ();
    }*/
    m_controller->connect ();
}

void TwsPlugin::subscribeAction()
{
    OpenTrade::Instrument inst(OpenTrade::Instrument::Forex, "EUR", "CHF", "SMART");
    qDebug() << inst.symbol () << "." << inst.currency ();
    if( m_controller->isConnected ()) {
        m_controller->subscribe (inst);
    }
}

void TwsPlugin::disconnectAction()
{
    m_controller->disconnect ();
}

void TwsPlugin::unsubscribeAction()
{
    OpenTrade::Instrument inst(OpenTrade::Instrument::Forex, "EUR", "CHF", "SMART");
    qDebug() << inst.symbol () << "." << inst.currency ();
    if( m_controller->isConnected ()) {
        m_controller->unsubscribe (inst);
    }
}

} // namespace Internal

} // namespace TWS

