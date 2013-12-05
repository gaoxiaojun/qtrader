/****************************************************************************
**
** Copyright (C) 2013 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of Qt Creator.
**
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.  For licensing terms and
** conditions see http://qt.digia.com/licensing.  For further information
** use the contact form at http://qt.digia.com/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Digia gives you certain additional
** rights.  These rights are described in the Digia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
****************************************************************************/

#include <app/app_config.h>

#include <breakpad.h>
#include <crashreportdialog.h>
#include <iplugin.h>
#include <pluginerroroverview.h>
#include <pluginmanager.h>
#include <pluginspec.h>
#include <qtsingleapplication.h>
//#include <utils/hostosinfo.h>

#include <QDebug>
#include <QDir>
#include <QFileInfo>
#include <QLibraryInfo>
#include <QSettings>
#include <QTextStream>
#include <QThreadPool>
#include <QTimer>
#include <QTranslator>
#include <QUrl>
#include <QVariant>

#include <QNetworkProxyFactory>

#include <QApplication>
#include <QMessageBox>
#if QT_VERSION < QT_VERSION_CHECK(5, 0, 0)
#include <QDesktopServices>
#else
#include <QStandardPaths>
#endif


using namespace ExtensionSystem;

enum { OptionIndent = 4, DescriptionIndent = 34 };

const char fixedOptionsC[] =
" [OPTION]... [FILE]...\n"
"Options:\n"
"    -help                         Display this help\n"
"    -version                      Display program version\n"
"    -client                       Attempt to connect to already running first instance\n"
"    -settingspath <path>          Override the default path where user settings are stored\n"
"    -pid <pid>                    Attempt to connect to instance given by pid\n"
"    -block                        Block until editor is closed\n"
"    -pluginpath <path>            Add a custom search path for plugins\n";

const char HELP_OPTION1[] = "-h";
const char HELP_OPTION2[] = "-help";
const char HELP_OPTION3[] = "/h";
const char HELP_OPTION4[] = "--help";
const char VERSION_OPTION[] = "-version";
const char CLIENT_OPTION[] = "-client";
const char SETTINGS_OPTION[] = "-settingspath";
const char PID_OPTION[] = "-pid";
const char BLOCK_OPTION[] = "-block";
const char PLUGINPATH_OPTION[] = "-pluginpath";

typedef QList<PluginSpec *> PluginSpecSet;

// Helpers for displaying messages. Note that there is no console on Windows.
#ifdef Q_OS_WIN
// Format as <pre> HTML
static inline void toHtml(QString &t)
{
    t.replace(QLatin1Char('&'), QLatin1String("&amp;"));
    t.replace(QLatin1Char('<'), QLatin1String("&lt;"));
    t.replace(QLatin1Char('>'), QLatin1String("&gt;"));
    t.insert(0, QLatin1String("<html><pre>"));
    t.append(QLatin1String("</pre></html>"));
}

static void displayHelpText(QString t) // No console on Windows.
{
    toHtml(t);
    QMessageBox::information(0, QLatin1String(Application::Constants::APPLICATION_NAME), t);
}

static void displayError(const QString &t) // No console on Windows.
{
    QMessageBox::critical(0, QLatin1String(Application::Constants::APPLICATION_NAME), t);
}

#else

static void displayHelpText(const QString &t)
{
    qWarning("%s", qPrintable(t));
}

static void displayError(const QString &t)
{
    qCritical("%s", qPrintable(t));
}

#endif

static void printVersion(const PluginSpec *coreplugin)
{
    QString version;
    QTextStream str(&version);
    str << '\n' << Application::Constants::APPLICATION_NAME << ' ' << coreplugin->version()<< " based on Qt " << qVersion() << "\n\n";
    PluginManager::formatPluginVersions(str);
    str << '\n' << coreplugin->copyright() << '\n';
    displayHelpText(version);
}

static void printHelp(const QString &a0)
{
    QString help;
    QTextStream str(&help);
    str << "Usage: " << a0 << fixedOptionsC;
    PluginManager::formatOptions(str, OptionIndent, DescriptionIndent);
    PluginManager::formatPluginOptions(str, OptionIndent, DescriptionIndent);
    displayHelpText(help);
}

static inline QString msgCoreLoadFailure(const QString &why)
{
    return QCoreApplication::translate("Application", "Failed to load core: %1").arg(why);
}

static inline int askMsgSendFailed()
{
    return QMessageBox::question(0, QApplication::translate("Application","Could not send message"),
                                 QCoreApplication::translate("Application", "Unable to send command line arguments to the already running instance. "
                                                             "It appears to be not responding. Do you want to start a new instance of Creator?"),
                                 QMessageBox::Yes | QMessageBox::No | QMessageBox::Retry,
                                 QMessageBox::Retry);
}

static QString getRootPath()
{
    // Figure out root:  Up one from 'bin'
    QDir rootDir = QApplication::applicationDirPath();
#ifndef Q_OS_WIN
    rootDir.cdUp();
#endif
    QString rootDirPath = rootDir.canonicalPath();
    rootDirPath += QLatin1Char('/');

    return rootDirPath;
}

static inline QStringList getPluginPaths()
{
    QStringList rc;

    QString pluginPath = getRootPath();
    pluginPath += QLatin1String(Application::Constants::APPLICATION_PLUGINS_PATH);
    rc.push_back(pluginPath);

    // 3) <localappdata>/plugins/<version>
    //    where <localappdata> is e.g.
    //    "%LOCALAPPDATA%dailypips/appname" on Windows Vista and later
    //    "$XDG_DATA_HOME/data/dailypips/appname" or "~/.local/share/data/dailypips/appname" on Linux
    //    "~/Library/Application Support/dailypips/appname" on Mac
#if QT_VERSION < QT_VERSION_CHECK(5, 0, 0)
    pluginPath = QDesktopServices::storageLocation(QDesktopServices::DataLocation);
#else
    pluginPath = QStandardPaths::writableLocation(QStandardPaths::DataLocation);
#endif
    pluginPath += QLatin1Char('/')
            + QLatin1String(Application::Constants::APPLICATION_ORGANIZATION_NAME)
            + QLatin1Char('/');

    pluginPath += QLatin1String(Application::Constants::APPLICATION_NAME);

    pluginPath += QLatin1String("/plugins/");
    pluginPath += QLatin1String(Application::Constants::APPLICATION_VERSION);

    rc.push_back(pluginPath);
    return rc;
}

int main(int argc, char **argv)
{
#ifdef Q_OS_MAC
    // increase the number of file that can be opened in Qt Creator.
    struct rlimit rl;
    getrlimit(RLIMIT_NOFILE, &rl);

    rl.rlim_cur = qMin((rlim_t)OPEN_MAX, rl.rlim_max);
    setrlimit(RLIMIT_NOFILE, &rl);
#endif

#if defined(Q_OS_UNIX) && !defined(Q_OS_MAC)
    // QML is unusable with the xlib backend
    QApplication::setGraphicsSystem(QLatin1String("raster"));
#endif

    SharedTools::QtSingleApplication app((QLatin1String(Application::Constants::APPLICATION_NAME)), argc, argv);

    if ((argc > 2) && (QLatin1String("--crash") == argv[1]))
    {
        QString minidump = argc >= 3 ? QLatin1String(argv[2]) : QString();
        Utils::CrashReportDialog dialog(QLatin1String(Application::Constants::APPLICATION_CRASHREPORT_URL),
                    minidump);
                    dialog.exec();
                    if (dialog.result() != QDialog::Accepted)
                        return 0;
    }


    const int threadCount = QThreadPool::globalInstance()->maxThreadCount();
    QThreadPool::globalInstance()->setMaxThreadCount(qMax(4, 2 * threadCount));

    Utils::setupBreakPadCrashHandler(); // Display a backtrace once a serious signal is delivered.

#if QT_VERSION >= QT_VERSION_CHECK(5, 0, 1)
    app.setAttribute(Qt::AA_UseHighDpiPixmaps);
#endif


    app.setApplicationName(Application::Constants::APPLICATION_NAME);
    app.setOrganizationName(Application::Constants::APPLICATION_ORGANIZATION_NAME);
    app.setApplicationVersion(Application::Constants::APPLICATION_VERSION);

    app.setProperty("application_version_revisor", Application::Constants::APPLICATION_VERSION_REVISOR);
    app.setProperty("application_copyright", Application::Constants::APPLICATION_COPYRIGHT);

    QDir dir(getRootPath() + QLatin1String(Application::Constants::APPLICATION_DATA_PATH));
    app.setProperty("application_resource_path", dir.canonicalPath());

    dir = QDir(getRootPath() + QLatin1String(Application::Constants::APPLICATION_DOC_PATH));
    app.setProperty("application_document_path", dir.canonicalPath());

    dir = QDir(getRootPath() + QLatin1String(Application::Constants::APPLICATION_LIBS_PATH));
    app.setProperty("application_library_path", dir.canonicalPath());

    // Manually determine -settingspath command line option
    // We can't use the regular way of the plugin manager, because that needs to parse pluginspecs
    // but the settings path can influence which plugins are enabled
    QString settingsPath;
    QStringList customPluginPaths;
    QStringList arguments = app.arguments(); // adapted arguments list is passed to plugin manager later
    QMutableStringListIterator it(arguments);

    while (it.hasNext()) {
        const QString &arg = it.next();
        if (arg == QLatin1String(SETTINGS_OPTION)) {
            it.remove();
            if (it.hasNext()) {
                settingsPath = QDir::fromNativeSeparators(it.next());
                it.remove();
            }
        } else if (arg == QLatin1String(PLUGINPATH_OPTION)) {
            it.remove();
            if (it.hasNext()) {
                customPluginPaths << QDir::fromNativeSeparators(it.next());
                it.remove();
            }
        }
    }

    if (!settingsPath.isEmpty())
        QSettings::setPath(QSettings::IniFormat, QSettings::UserScope, settingsPath);

    // Must be done before any QSettings class is created
    QSettings::setPath(QSettings::IniFormat, QSettings::SystemScope,
                       QCoreApplication::applicationDirPath()
                       + QLatin1String(Application::Constants::APPLICATION_DATA_PATH));
    QSettings::setDefaultFormat(QSettings::IniFormat);
    // plugin manager takes control of this settings object
    QSettings *settings = new QSettings(QSettings::IniFormat, QSettings::UserScope,
                                        QLatin1String(Application::Constants::APPLICATION_ORGANIZATION_NAME),
                                        QLatin1String(Application::Constants::APPLICATION_NAME));;

    QSettings *globalSettings = new QSettings(QSettings::IniFormat, QSettings::SystemScope,
                                              QLatin1String(Application::Constants::APPLICATION_ORGANIZATION_NAME),
                                              QLatin1String(Application::Constants::APPLICATION_NAME));;

    PluginManager pluginManager;
    PluginManager::setGlobalSettings(globalSettings);
    PluginManager::setSettings(settings);

    QTranslator apptranslator;
    QTranslator qtTranslator;
    QStringList uiLanguages;
// uiLanguages crashes on Windows with 4.8.0 release builds
#if (QT_VERSION >= 0x040801) || (QT_VERSION >= 0x040800 && !defined(Q_OS_WIN))
    uiLanguages = QLocale::system().uiLanguages();
#else
    uiLanguages << QLocale::system().name();
#endif
    QString overrideLanguage = settings->value(QLatin1String("General/OverrideLanguage")).toString();

    if (!overrideLanguage.isEmpty())
        uiLanguages.prepend(overrideLanguage);

#if QT_VERSION < QT_VERSION_CHECK(5, 0, 0)
    QString appUserTrPath = QDesktopServices::storageLocation(QDesktopServices::DataLocation);
#else
    QString appUserTrPath = QStandardPaths::writableLocation(QStandardPaths::DataLocation);
#endif
    appUserTrPath += QLatin1Char('/')
            + QLatin1String(Application::Constants::APPLICATION_ORGANIZATION_NAME)
            + QLatin1Char('/');

    appUserTrPath += QLatin1String(Application::Constants::APPLICATION_NAME);

    appUserTrPath += QLatin1String("/translations/");
    appUserTrPath += QLatin1String(Application::Constants::APPLICATION_VERSION);

    const QString &appExternalTrPath = getRootPath()
            + QLatin1String(Application::Constants::APPLICATION_DATA_PATH)
            + QLatin1String("/translations/");

    const QString &appResourceTrPath = QLatin1String(":/")
            + QLatin1String(Application::Constants::APPLICATION_NAME)
            + QLatin1String("/translations/");

    const QString &qtTrPath = QLibraryInfo::location(QLibraryInfo::TranslationsPath);

    const QString appTrFile = QString(Application::Constants::APPLICATION_NAME);

    foreach (QString locale, uiLanguages) {
#if (QT_VERSION >= 0x050000)
        locale = QLocale(locale).name();
#else
        locale.replace(QLatin1Char('-'), QLatin1Char('_')); // work around QTBUG-25973
#endif
        if (apptranslator.load(appTrFile + locale, appUserTrPath) ||
            apptranslator.load(appTrFile + locale, appExternalTrPath) ||
            apptranslator.load(locale, appResourceTrPath)
                ) {
            const QString &qtTrFile = QLatin1String("qt_") + locale;

            if (qtTranslator.load(qtTrFile, qtTrPath) || qtTranslator.load(qtTrFile, appUserTrPath) ||
                  qtTranslator.load(qtTrFile, appExternalTrPath)
                    ) {
                app.installTranslator(&apptranslator);
                app.installTranslator(&qtTranslator);
                app.setProperty("application_locale", locale);
                break;
            }
            apptranslator.load(QString()); // unload()
        } else if (locale == QLatin1String("C") /* overrideLanguage == "English" */) {
            // use built-in
            break;
        } else if (locale.startsWith(QLatin1String("en")) /* "English" is built-in */) {
            // use built-in
            break;
        }
    }

    // Make sure we honor the system's proxy settings
#if defined(Q_OS_UNIX)
    QUrl proxyUrl(QString::fromLatin1(qgetenv("http_proxy")));
    if (proxyUrl.isValid()) {
        QNetworkProxy proxy(QNetworkProxy::HttpProxy, proxyUrl.host(),
                            proxyUrl.port(), proxyUrl.userName(), proxyUrl.password());
        QNetworkProxy::setApplicationProxy(proxy);
# if defined(Q_OS_MAC) // unix and mac
    } else {
        QNetworkProxyFactory::setUseSystemConfiguration(true);
# endif
    }
#else // windows
    QNetworkProxyFactory::setUseSystemConfiguration(true);
#endif
    // Load
    const QStringList pluginPaths = getPluginPaths() + customPluginPaths;
    PluginManager::setPluginPaths(pluginPaths);
    QMap<QString, QString> foundAppOptions;
    if (arguments.size() > 1) {
        QMap<QString, bool> appOptions;
        appOptions.insert(QLatin1String(HELP_OPTION1), false);
        appOptions.insert(QLatin1String(HELP_OPTION2), false);
        appOptions.insert(QLatin1String(HELP_OPTION3), false);
        appOptions.insert(QLatin1String(HELP_OPTION4), false);
        appOptions.insert(QLatin1String(VERSION_OPTION), false);
        appOptions.insert(QLatin1String(CLIENT_OPTION), false);
        appOptions.insert(QLatin1String(PID_OPTION), true);
        appOptions.insert(QLatin1String(BLOCK_OPTION), false);
        QString errorMessage;
        if (!PluginManager::parseOptions(arguments, appOptions, &foundAppOptions, &errorMessage)) {
            displayError(errorMessage);
            printHelp(QFileInfo(app.applicationFilePath()).baseName());
            return -1;
        }
    }

    const PluginSpecSet plugins = PluginManager::plugins();
    PluginSpec *coreplugin = 0;
    foreach (PluginSpec *spec, plugins) {
        if (spec->name() == QLatin1String(Application::Constants::APPLICATION_CORE_PLUGIN_NAME)) {
            coreplugin = spec;
            break;
        }
    }
    if (!coreplugin) {
        QString nativePaths = QDir::toNativeSeparators(pluginPaths.join(QLatin1String(",")));
        const QString reason = QCoreApplication::translate(Application::Constants::APPLICATION_NAME,
                                                           "Could not find %1 plugin' in %2")
                                                            .arg(QLatin1String(Application::Constants::APPLICATION_CORE_PLUGIN_NAME))
                                                            .arg(nativePaths);
        displayError(msgCoreLoadFailure(reason));
        return 1;
    }
    if (coreplugin->hasError()) {
        displayError(msgCoreLoadFailure(coreplugin->errorString()));
        return 1;
    }
    if (foundAppOptions.contains(QLatin1String(VERSION_OPTION))) {
        printVersion(coreplugin);
        return 0;
    }
    if (foundAppOptions.contains(QLatin1String(HELP_OPTION1))
            || foundAppOptions.contains(QLatin1String(HELP_OPTION2))
            || foundAppOptions.contains(QLatin1String(HELP_OPTION3))
            || foundAppOptions.contains(QLatin1String(HELP_OPTION4))) {
        printHelp(QFileInfo(app.applicationFilePath()).baseName());
        return 0;
    }

    qint64 pid = -1;
    if (foundAppOptions.contains(QLatin1String(PID_OPTION))) {
        QString pidString = foundAppOptions.value(QLatin1String(PID_OPTION));
        bool pidOk;
        qint64 tmpPid = pidString.toInt(&pidOk);
        if (pidOk)
            pid = tmpPid;
    }

    bool isBlock = foundAppOptions.contains(QLatin1String(BLOCK_OPTION));
    if (app.isRunning() && (pid != -1 || isBlock
                            || foundAppOptions.contains(QLatin1String(CLIENT_OPTION)))) {
        app.setBlock(isBlock);
        if (app.sendMessage(PluginManager::serializedArguments(), 5000 /*timeout*/, pid))
            return 0;

        // Message could not be send, maybe it was in the process of quitting
        if (app.isRunning(pid)) {
            // Nah app is still running, ask the user
            int button = askMsgSendFailed();
            while (button == QMessageBox::Retry) {
                if (app.sendMessage(PluginManager::serializedArguments(), 5000 /*timeout*/, pid))
                    return 0;
                if (!app.isRunning(pid)) // App quit while we were trying so start a new creator
                    button = QMessageBox::Yes;
                else
                    button = askMsgSendFailed();
            }
            if (button == QMessageBox::No)
                return -1;
        }
    }

    PluginManager::loadPlugins();
    if (coreplugin->hasError()) {
        displayError(msgCoreLoadFailure(coreplugin->errorString()));
        return 1;
    }
    if (PluginManager::hasError()) {
        PluginErrorOverview *errorOverview = new PluginErrorOverview(QApplication::activeWindow());
        errorOverview->setAttribute(Qt::WA_DeleteOnClose);
        errorOverview->setModal(true);
        errorOverview->show();
    }

    // Set up remote arguments.
    QObject::connect(&app, SIGNAL(messageReceived(QString,QObject*)),
                     &pluginManager, SLOT(remoteArguments(QString,QObject*)));

    QObject::connect(&app, SIGNAL(fileOpenRequest(QString)), coreplugin->plugin(),
                     SLOT(fileOpenRequest(QString)));

    // quit when last window (relevant window, see WA_QuitOnClose) is closed
    // this should actually be the default, but doesn't work in Qt 5
    // QTBUG-31569
    QObject::connect(&app, SIGNAL(lastWindowClosed()), &app, SLOT(quit()));
    // shutdown plugin manager on the exit
    QObject::connect(&app, SIGNAL(aboutToQuit()), &pluginManager, SLOT(shutdown()));

    const int r = app.exec();

    return r;
}
