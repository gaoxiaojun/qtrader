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

#include "historicalprovidermanager.h"

#include <extensionsystem/iplugin.h>
#include <extensionsystem/pluginmanager.h>

using namespace OpenTrade;

/*static Internal::HistoricalProviderManagerPrivate *d = 0;*/
static HistoricalProviderManager *m_instance = 0;

HistoricalProviderManager *HistoricalProviderManager::instance()
{
    return m_instance;
}

HistoricalProviderManager::HistoricalProviderManager(QObject *parent) :
    QObject(parent)
{
    m_instance = this;
}

HistoricalProviderManager::~HistoricalProviderManager()
{
    foreach(IHistoricalProvider *provider, m_providers) {
        disconnectToProvider (provider);
    }

    m_providers.clear();
}

void HistoricalProviderManager::init()
{
    connect(ExtensionSystem::PluginManager::instance(), SIGNAL(objectAdded(QObject*)),
            this, SLOT(objectAdded(QObject*)));
    connect(ExtensionSystem::PluginManager::instance(), SIGNAL(aboutToRemoveObject(QObject*)),
            this, SLOT(aboutToRemoveObject(QObject*)));
}

void HistoricalProviderManager::objectAdded(QObject *obj)
{
    IHistoricalProvider *provider = Aggregation::query<IHistoricalProvider>(obj);

    if(provider) {
        m_providers.append (provider);
        connectToProvider(provider);
    }
}

void HistoricalProviderManager::aboutToRemoveObject(QObject *obj)
{
    IHistoricalProvider *provider = Aggregation::query<IHistoricalProvider>(obj);

    if(provider) {
        m_providers.removeOne (provider);
        disconnectToProvider (provider);
    }
}

void HistoricalProviderManager::extensionsInitalized()
{
}

void HistoricalProviderManager::connectToProvider (IHistoricalProvider *provider)
{
    connect(provider, SIGNAL(historicalDataCancelled(const HistoricalDataRequest&)),
            this, SLOT(historicalDataCancelled(const HistoricalDataRequest&)));

    connect(provider, SIGNAL(historicalDataCompleted(const HistoricalDataRequest&)),
            this, SLOT(historicalDataCompleted(const HistoricalDataRequest&)));

    connect(provider, SIGNAL(HistoricalDataError(const HistoricalDataRequest&, const QString&)),
            this, SLOT(HistoricalDataError(const HistoricalDataRequest&, const QString&)));

    connect(provider, SIGNAL(newHistoricalBar(const HistoricalDataRequest&, const QDateTime&,
                           double, double, double, double, long)),
            this, SLOT(newHistoricalBar(const HistoricalDataRequest&, const QDateTime&,
                                        double, double, double, double, long)));

    connect(provider, SIGNAL(newHistoricalQuote(const HistoricalDataRequest&, const QDateTime&,
                             double, int, double, int)),
            this, SLOT(newHistoricalQuote(const HistoricalDataRequest&, const QDateTime&,
                                          double, int, double, int)));

    connect(provider, SIGNAL(newHistoricalTrade(const HistoricalDataRequest&, const QDateTime&, double, int)),
            this, SLOT(newHistoricalTrade(const HistoricalDataRequest&, const QDateTime&, double, int)));

}

void HistoricalProviderManager::disconnectToProvider (IHistoricalProvider *provider)
{
    disconnect(provider, SIGNAL(historicalDataCancelled(const HistoricalDataRequest&)),
            this, SLOT(historicalDataCancelled(const HistoricalDataRequest&)));

    disconnect(provider, SIGNAL(historicalDataCompleted(const HistoricalDataRequest&)),
            this, SLOT(historicalDataCompleted(const HistoricalDataRequest&)));

    disconnect(provider, SIGNAL(HistoricalDataError(const HistoricalDataRequest&, const QString&)),
            this, SLOT(HistoricalDataError(const HistoricalDataRequest&, const QString&)));

    disconnect(provider, SIGNAL(newHistoricalBar(const HistoricalDataRequest&, const QDateTime&,
                           double, double, double, double, long)),
            this, SLOT(newHistoricalBar(const HistoricalDataRequest&, const QDateTime&,
                                        double, double, double, double, long)));

    disconnect(provider, SIGNAL(newHistoricalQuote(const HistoricalDataRequest&, const QDateTime&,
                             double, int, double, int)),
            this, SLOT(newHistoricalQuote(const HistoricalDataRequest&, const QDateTime&,
                                          double, int, double, int)));

    disconnect(provider, SIGNAL(newHistoricalTrade(const HistoricalDataRequest&, const QDateTime&, double, int)),
            this, SLOT(newHistoricalTrade(const HistoricalDataRequest&, const QDateTime&, double, int)));
}

void HistoricalProviderManager::historicalDataCancelled(const HistoricalDataRequest& request )
{

}

void HistoricalProviderManager::historicalDataCompleted(const HistoricalDataRequest& request )
{

}

void HistoricalProviderManager::HistoricalDataError(const HistoricalDataRequest& request, QString message )
{

}

void HistoricalProviderManager::newHistoricalBar(const HistoricalDataRequest& request, const QDateTime& datetime,
                       double open, double high, double low, double close, long volume )
{

}

void HistoricalProviderManager::newHistoricalQuote(const HistoricalDataRequest& request, const QDateTime& datetime,
                         double bid, int bidSize, double ask, int askSize )
{

}

void HistoricalProviderManager::newHistoricalTrade(const HistoricalDataRequest& request, const QDateTime& datetime, double price, int size )
{

}
