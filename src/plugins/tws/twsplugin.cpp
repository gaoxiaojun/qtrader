
#include "twsplugin.h"
#include <opentrade/iprovider.h>

#include "twsmarketdataprovider.h"
#include "twsclient.h"
#include "twsoptionspage.h"
#include "twsorderexecutionprovider.h"
#include "twshistoricalprovider.h"


#include <extensionsystem/pluginmanager.h>

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
    m_client = new TwsClient(this);
    addAutoReleasedObject(new TwsMarketDataProvier(this));
    //addAutoReleasedObject(new TwsHistoricalProvider(this));
    //addAutoReleasedObject(new TwsOrderExecutionProvider(this));
    addAutoReleasedObject (new TwsOptionsPage(this));
    return true;
}

void TwsPlugin::extensionsInitialized()
{
    m_client->connect ("127.0.0.1", 4001, 1);
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
    settings->beginGroup(QLatin1String("Tws"));
    /*settings->setValue(QLatin1String("Backward"), hasTwsFlag(TwsBackward));
    settings->setValue(QLatin1String("CaseSensitively"), hasTwsFlag(TwsCaseSensitively));
    settings->setValue(QLatin1String("WholeWords"), hasTwsFlag(TwsWholeWords));
    settings->setValue(QLatin1String("RegularExpression"), hasTwsFlag(TwsRegularExpression));
    settings->setValue(QLatin1String("PreserveCase"), hasTwsFlag(TwsPreserveCase));
    settings->setValue(QLatin1String("TwsStrings"), d->m_twsCompletions);
    settings->setValue(QLatin1String("ReplaceStrings"), d->m_replaceCompletions);*/
    settings->endGroup();
    //d->m_twsToolBar->writeSettings();
    //d->m_twsDialog->writeSettings();
}

void TwsPlugin::readSettings()
{
    QSettings *settings = Core::ICore::settings();
    settings->beginGroup(QLatin1String("Tws"));
    /*bool block = blockSignals(true);
    setBackward(settings->value(QLatin1String("Backward"), false).toBool());
    setCaseSensitive(settings->value(QLatin1String("CaseSensitively"), false).toBool());
    setWholeWord(settings->value(QLatin1String("WholeWords"), false).toBool());
    setRegularExpression(settings->value(QLatin1String("RegularExpression"), false).toBool());
    setPreserveCase(settings->value(QLatin1String("PreserveCase"), false).toBool());
    blockSignals(block);
    d->m_twsCompletions = settings->value(QLatin1String("TwsStrings")).toStringList();
    d->m_replaceCompletions = settings->value(QLatin1String("ReplaceStrings")).toStringList();
    d->m_twsCompletionModel->setStringList(d->m_twsCompletions);
    d->m_replaceCompletionModel->setStringList(d->m_replaceCompletions);*/
    settings->endGroup();
    //d->m_twsToolBar->readSettings();
    //d->m_twsDialog->readSettings();
    emit twsFlagsChanged(); // would have been done in the setXXX methods above
}

} // namespace Internal
} // namespace TWS

