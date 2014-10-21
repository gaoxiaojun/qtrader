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

#include "messagemanager.h"
#include "messageoutputwindow.h"

#include <extensionsystem/pluginmanager.h>

#include <QThread>
#include <QCoreApplication>
#include <QMetaObject>
#include <QDebug>
#include <qlogging.h>
#include <QRegExp>

using namespace Core;

static MessageManager *m_instance = 0;
Internal::MessageOutputWindow *m_messageOutputWindow = 0;

void PluginMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString& msg)
{
    QString name = QString(context.file).section ('/', -1, -1, QString::SectionSkipEmpty);
    QString prefix = QString("%1:%2").arg(name).arg(context.line);

    QString text;
    switch (type)
    {
    case QtDebugMsg:
        text = QString("[D]%1: %2").arg(prefix).arg(msg);
        break;
    case QtWarningMsg:
        text = QString("[W]%1: %2").arg(prefix).arg(msg);
        break;
    case QtCriticalMsg:
        text = QString("[C]%1: %2").arg(prefix).arg(msg);
        break;
    case QtFatalMsg:
        text = QString("[F]%1: %2").arg(prefix).arg(msg);
        abort();
    }
    MessageManager::write (text);
}

QObject *MessageManager::instance()
{
    return m_instance;
}

MessageManager::MessageManager()
{
    m_instance = this;
    m_messageOutputWindow = 0;
    qRegisterMetaType<Core::MessageManager::PrintToOutputPaneFlags>();
}

MessageManager::~MessageManager()
{
    if (m_messageOutputWindow) {
        ExtensionSystem::PluginManager::removeObject(m_messageOutputWindow);
        delete m_messageOutputWindow;
    }
    m_instance = 0;
}

void MessageManager::init()
{
    m_messageOutputWindow = new Internal::MessageOutputWindow;
    ExtensionSystem::PluginManager::addObject(m_messageOutputWindow);

    qInstallMessageHandler(PluginMessageOutput);
}

void MessageManager::showOutputPane()
{
    if (m_messageOutputWindow)
        m_messageOutputWindow->popup(IOutputPane::ModeSwitch);
}

void MessageManager::write(const QString &text)
{
    write(text, NoModeSwitch);
}

void MessageManager::write(const QString &text, PrintToOutputPaneFlags flags)
{
    if (!m_messageOutputWindow)
        return;

    if (QThread::currentThread () != qApp->thread ()) {
        QMetaObject::invokeMethod (MessageManager::instance (), "write",
                                   Qt::QueuedConnection,
                                   Q_ARG(QString, text),
                                   Q_ARG(Core::MessageManager::PrintToOutputPaneFlags, flags));
        return;
    }

    if (flags & Flash) {
        m_messageOutputWindow->flash();
    } else if (flags & Silent) {
        // Do nothing
    } else {
        m_messageOutputWindow->popup(Core::IOutputPane::Flag(int(flags)));
    }

    m_messageOutputWindow->append(text + QLatin1Char('\n'));
}

