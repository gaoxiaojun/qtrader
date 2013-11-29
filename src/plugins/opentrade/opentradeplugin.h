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

#ifndef DOMAIN_HPP
#define DOMAIN_HPP

#include "opentrade_global.h"

#include <extensionsystem/iplugin.h>

#include <QtPlugin>

namespace OpenTrade {
namespace Internal {

class OpenTradePlugin : public ExtensionSystem::IPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.dailypips.QtTrader.QtTraderPlugin") // FILE "OpenTrade.json")

public:
    OpenTradePlugin();
    ~OpenTradePlugin();

    bool initialize(const QStringList &arguments, QString *errorString);
    void extensionsInitialized();
    ShutdownFlag aboutToShutdown();

};

} // namespace Internal
} // namespace OpenTrade

#endif // DOMAIN_HPP

