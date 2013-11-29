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

#include "orderexecutionprovidermanager.h"
#include <extensionsystem/iplugin.h>
#include <extensionsystem/pluginmanager.h>

using namespace OpenTrade;

/*static Internal::OrderExecutionProviderManagerPrivate *d = 0;*/
static OrderExecutionProviderManager *m_instance = 0;

OrderExecutionProviderManager *OrderExecutionProviderManager::instance()
{
    return m_instance;
}

OrderExecutionProviderManager::OrderExecutionProviderManager(QObject *parent) :
    QObject(parent)
{
    m_instance = this;
}

OrderExecutionProviderManager::~OrderExecutionProviderManager()
{
    foreach(IOrderExecutionProvider *provider, m_providers) {
        disconnectToProvider (provider);
    }

    m_providers.clear();
}

void OrderExecutionProviderManager::init()
{
    connect(ExtensionSystem::PluginManager::instance(), SIGNAL(objectAdded(QObject*)),
            this, SLOT(objectAdded(QObject*)));
    connect(ExtensionSystem::PluginManager::instance(), SIGNAL(aboutToRemoveObject(QObject*)),
            this, SLOT(aboutToRemoveObject(QObject*)));
}

void OrderExecutionProviderManager::objectAdded(QObject *obj)
{
    IOrderExecutionProvider *provider = Aggregation::query<IOrderExecutionProvider>(obj);

    if(provider) {
        m_providers.append (provider);
        connectToProvider (provider);
    }
}

void OrderExecutionProviderManager::aboutToRemoveObject(QObject *obj)
{
    IOrderExecutionProvider *provider = Aggregation::query<IOrderExecutionProvider>(obj);

    if(provider) {
        m_providers.removeOne (provider);
        disconnectToProvider (provider);
    }
}

void OrderExecutionProviderManager::extensionsInitalized()
{
}

void OrderExecutionProviderManager::connectToProvider (IOrderExecutionProvider *provider)
{
    connect(provider, SIGNAL(orderAccepted(const Order&)), this, SLOT(orderAccepted(const Order&)));
    connect(provider, SIGNAL(orderCancelled(const Order&)), this, SLOT(orderCancelled(const Order&)));
    connect(provider, SIGNAL(orderRejected(const Order&, const QString&)), this, SLOT(orderRejected(const Order& ,const QString&)));
    connect(provider, SIGNAL(orderReplaced(const Order&)), this, SLOT(orderReplaced(const Order&)));
    connect(provider, SIGNAL(orderCancelReject(const Order&, Order::OrderStatus, const QString&)),
            this, SLOT(orderCancelReject(const Order&, Order::OrderStatus,const QString&)));
    connect(provider, SIGNAL(orderPendingReplace(const Order&)), this, SLOT(orderPendingReplace(const Order&)));
    connect(provider, SIGNAL(orderReplaceReject(const Order&, Order::OrderStatus, const QString&)),
            this, SLOT(orderReplaceReject(const Order&,Order::OrderStatus,const QString&)));
    connect(provider, SIGNAL(orderFilled(const Order&,double,int)), this, SLOT(orderFilled(const Order&,double,int)));
    /*connect(provider, SIGNAL(orderFilled(const Order&, double, int, CommissionType, double)),
              this, SLOT(orderFilled(const Order&, double, int, CommissionType, double));*/

}

void OrderExecutionProviderManager::disconnectToProvider (IOrderExecutionProvider *provider)
{
    disconnect(provider, SIGNAL(orderAccepted(const Order&)), this, SLOT(orderAccepted(const Order&)));
    disconnect(provider, SIGNAL(orderCancelled(const Order&)), this, SLOT(orderCancelled(const Order&)));
    disconnect(provider, SIGNAL(orderRejected(const Order&, const QString&)), this, SLOT(orderRejected(const Order& ,const QString&)));
    disconnect(provider, SIGNAL(orderReplaced(const Order&)), this, SLOT(orderReplaced(const Order&)));
    disconnect(provider, SIGNAL(orderCancelReject(const Order&, Order::OrderStatus, const QString&)),
            this, SLOT(orderCancelReject(const Order&, Order::OrderStatus,const QString&)));
    disconnect(provider, SIGNAL(orderPendingReplace(const Order&)), this, SLOT(orderPendingReplace(const Order&)));
    disconnect(provider, SIGNAL(orderReplaceReject(const Order&, Order::OrderStatus, const QString&)),
            this, SLOT(orderReplaceReject(const Order&,Order::OrderStatus,const QString&)));
    disconnect(provider, SIGNAL(orderFilled(const Order&,double,int)), this, SLOT(orderFilled(const Order&,double,int)));
    /*disconnect(provider, SIGNAL(orderFilled(const Order&, double, int, CommissionType, double)),
              this, SLOT(orderFilled(const Order&, double, int, CommissionType, double));*/

}


void OrderExecutionProviderManager:: orderAccepted(const Order& order)
{

}

void OrderExecutionProviderManager:: orderCancelled(const Order& order)
{

}

void OrderExecutionProviderManager:: orderRejected(const Order& order, const QString& message)
{

}

void OrderExecutionProviderManager:: orderReplaced(const Order& order)
{

}

void OrderExecutionProviderManager:: orderCancelReject(const Order& order, Order::OrderStatus status, const QString& message)
{

}

void OrderExecutionProviderManager:: orderPendingReplace(const Order& order)
{

}

void OrderExecutionProviderManager:: orderReplaceReject(const Order& order, Order::OrderStatus status, const QString& message )
{

}

void OrderExecutionProviderManager:: orderFilled(const Order& order, double price, int quantity )
{

}

/*void OrderExecutionProviderManager:: orderFilled(const Order& order, double price, int quantity, CommissionType commissionType, double commission )
{

}*/
