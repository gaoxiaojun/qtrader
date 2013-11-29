
#include "twsplugin.h"

#include <coreplugin/actionmanager/actionmanager.h>
#include <coreplugin/actionmanager/actioncontainer.h>
#include <coreplugin/coreconstants.h>
#include <coreplugin/icore.h>
#include <coreplugin/id.h>

#include <extensionsystem/pluginmanager.h>

#include <QMenu>
#include <QStringListModel>
#include <QAction>

#include <QtPlugin>
#include <QSettings>

namespace Tws {

class TwsPluginPrivate {
public:
    explicit TwsPluginPrivate(TwsPlugin *q);

    //variables
    static TwsPlugin *m_instance;

    /*QHash<ITwsFilter *, QAction *> m_filterActions;

    Internal::CurrentDocumentTws *m_currentDocumentTws;
    Internal::TwsToolBar *m_twsToolBar;
    Internal::TwsToolWindow *m_twsDialog;
    TwsFlags m_twsFlags;
    QStringListModel *m_twsCompletionModel;
    QStringListModel *m_replaceCompletionModel;
    QStringList m_twsCompletions;
    QStringList m_replaceCompletions;
    QAction *m_openTwsDialog;*/
};

TwsPluginPrivate::TwsPluginPrivate(TwsPlugin *q) //:
    /*m_currentDocumentTws(0), m_twsToolBar(0), m_twsDialog(0),
    m_twsCompletionModel(new QStringListModel(q)),
    m_replaceCompletionModel(new QStringListModel(q))*/
{
}

TwsPlugin *TwsPluginPrivate::m_instance = 0;

TwsPlugin::TwsPlugin() : d(new TwsPluginPrivate(this))
{
    //QTC_ASSERT(!TwsPluginPrivate::m_instance, return);
    TwsPluginPrivate::m_instance = this;
}

TwsPlugin::~TwsPlugin()
{
    TwsPluginPrivate::m_instance = 0;
    //delete d->m_currentDocumentTws;
    //delete d->m_twsToolBar;
    //delete d->m_twsDialog;
    delete d;
}

TwsPlugin *TwsPlugin::instance()
{
    return TwsPluginPrivate::m_instance;
}

bool TwsPlugin::initialize(const QStringList &, QString *)
{
    /*setupMenu();

    d->m_currentDocumentTws = new Internal::CurrentDocumentTws;

    d->m_twsToolBar = new Internal::TwsToolBar(this, d->m_currentDocumentTws);
    d->m_twsDialog = new Internal::TwsToolWindow(this);
    SearchResultWindow *searchResultWindow = new SearchResultWindow(d->m_twsDialog);
    addAutoReleasedObject(searchResultWindow);*/
    return true;
}

void TwsPlugin::extensionsInitialized()
{
    /*setupFilterMenuItems();*/
    readSettings();
}

ExtensionSystem::IPlugin::ShutdownFlag TwsPlugin::aboutToShutdown()
{
    //d->m_twsToolBar->setVisible(false);
    //d->m_twsToolBar->setParent(0);
    //d->m_currentDocumentTws->removeConnections();
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


} // namespace Tws


Q_EXPORT_PLUGIN(Tws::TwsPlugin)
