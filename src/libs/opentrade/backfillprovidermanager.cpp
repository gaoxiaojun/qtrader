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

#include "backfillprovidermanager.h"

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
    foreach(IBackfillProvider *provider, m_providers) {
        disconnectToProvider (provider);
    }

    m_providers.clear();
}

void HistoricalProviderManager::initialize()
{
    connect(ExtensionSystem::PluginManager::instance(), SIGNAL(objectAdded(QObject*)),
            this, SLOT(objectAdded(QObject*)));
    connect(ExtensionSystem::PluginManager::instance(), SIGNAL(aboutToRemoveObject(QObject*)),
            this, SLOT(aboutToRemoveObject(QObject*)));
}

void HistoricalProviderManager::objectAdded(QObject *obj)
{
    IBackfillProvider *provider = Aggregation::query<IBackfillProvider>(obj);

    if(provider) {
        m_providers.append (provider);
        connectToProvider(provider);
    }
}

void HistoricalProviderManager::aboutToRemoveObject(QObject *obj)
{
    IBackfillProvider *provider = Aggregation::query<IBackfillProvider>(obj);

    if(provider) {
        m_providers.removeOne (provider);
        disconnectToProvider (provider);
    }
}

void HistoricalProviderManager::extensionsInitalized()
{
}

void HistoricalProviderManager::connectToProvider (IBackfillProvider *provider)
{
    connect(provider, SIGNAL(historicalDataCancelled(const BackfillRequest&)),
            this, SLOT(historicalDataCancelled(const BackfillRequest&)));

    connect(provider, SIGNAL(historicalDataCompleted(const BackfillRequest&)),
            this, SLOT(historicalDataCompleted(const BackfillRequest&)));

    connect(provider, SIGNAL(HistoricalDataError(const BackfillRequest&, const QString&)),
            this, SLOT(HistoricalDataError(const BackfillRequest&, const QString&)));

    connect(provider, SIGNAL(newHistoricalBar(const BackfillRequest&, const QDateTime&,
                           double, double, double, double, long)),
            this, SLOT(newHistoricalBar(const BackfillRequest&, const QDateTime&,
                                        double, double, double, double, long)));

    connect(provider, SIGNAL(newHistoricalQuote(const BackfillRequest&, const QDateTime&,
                             double, int, double, int)),
            this, SLOT(newHistoricalQuote(const BackfillRequest&, const QDateTime&,
                                          double, int, double, int)));

    connect(provider, SIGNAL(newHistoricalTrade(const BackfillRequest&, const QDateTime&, double, int)),
            this, SLOT(newHistoricalTrade(const BackfillRequest&, const QDateTime&, double, int)));

}

void HistoricalProviderManager::disconnectToProvider (IBackfillProvider *provider)
{
    disconnect(provider, SIGNAL(historicalDataCancelled(const BackfillRequest&)),
            this, SLOT(historicalDataCancelled(const BackfillRequest&)));

    disconnect(provider, SIGNAL(historicalDataCompleted(const BackfillRequest&)),
            this, SLOT(historicalDataCompleted(const BackfillRequest&)));

    disconnect(provider, SIGNAL(HistoricalDataError(const BackfillRequest&, const QString&)),
            this, SLOT(HistoricalDataError(const BackfillRequest&, const QString&)));

    disconnect(provider, SIGNAL(newHistoricalBar(const BackfillRequest&, const QDateTime&,
                           double, double, double, double, long)),
            this, SLOT(newHistoricalBar(const BackfillRequest&, const QDateTime&,
                                        double, double, double, double, long)));

    disconnect(provider, SIGNAL(newHistoricalQuote(const BackfillRequest&, const QDateTime&,
                             double, int, double, int)),
            this, SLOT(newHistoricalQuote(const BackfillRequest&, const QDateTime&,
                                          double, int, double, int)));

    disconnect(provider, SIGNAL(newHistoricalTrade(const BackfillRequest&, const QDateTime&, double, int)),
            this, SLOT(newHistoricalTrade(const BackfillRequest&, const QDateTime&, double, int)));
}

void HistoricalProviderManager::historicalDataCancelled(const BackfillRequest& request )
{

}

void HistoricalProviderManager::historicalDataCompleted(const BackfillRequest& request )
{

}

void HistoricalProviderManager::HistoricalDataError(const BackfillRequest& request, QString message )
{

}

void HistoricalProviderManager::newHistoricalBar(const BackfillRequest& request, const QDateTime& datetime,
                       double open, double high, double low, double close, long volume )
{

}

void HistoricalProviderManager::newHistoricalQuote(const BackfillRequest& request, const QDateTime& datetime,
                         double bid, int bidSize, double ask, int askSize )
{

}

void HistoricalProviderManager::newHistoricalTrade(const BackfillRequest& request, const QDateTime& datetime, double price, int size )
{

}
