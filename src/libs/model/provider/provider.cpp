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
#include "provider.h"

#include <QSharedData>

namespace OpenTrade {

namespace Internal {

class ProviderPrivate : public QSharedData
{
public:
    int m_id;
    bool m_isConnected;
    bool m_isExecutionProvider;
    bool m_isHistoricalDataProvider;
    bool m_isInstrumentProvider;
    bool m_isMarketDataProvider;
    QString m_name;
    ProviderPropertyList m_properties;
};

} // namespace Internal

Provider::~Provider()
{

}

Provider& Provider::operator=(const Provider &other)
{
    d = other.d;
    return *this;
}

bool Provider::operator==(const Provider &other) const
{
    if(d == other.d)
      return true;

    return d->m_id == other.d->m_id &&
           d->m_isConnected == other.d->m_isConnected &&
           d->m_isExecutionProvider == other.d->m_isExecutionProvider &&
           d->m_isHistoricalDataProvider == other.d->m_isHistoricalDataProvider &&
           d->m_isInstrumentProvider == other.d->m_isInstrumentProvider &&
           d->m_isMarketDataProvider == other.d->m_isMarketDataProvider &&
           d->m_name == other.d->m_name &&
           d->m_properties == other.d->m_properties;
}

void Provider::connect()
{

}

void Provider::disconnect()
{

}

int Provider::id() const
{
    return d->m_id;
}

bool Provider::isConnected() const
{
    return d->m_isConnected;
}

bool Provider::isExecutionProvider() const
{
    return d->m_isExecutionProvider;
}

bool Provider::isHistoricalDataProvider() const
{
    return d->m_isHistoricalDataProvider;
}

bool Provider::isInstrumentProvider() const
{
    return d->m_isInstrumentProvider;
}

bool Provider::isMarketDataProvider() const
{
    return d->m_isMarketDataProvider;
}

QString Provider::name() const
{
    return d->m_name;
}

ProviderPropertyList Provider::properties() const
{
    return d->m_properties;
}

void Provider::setProperties(const ProviderPropertyList& properties)
{
    d->m_properties = properties;
}


} // namespace OpenTrade

QDebug operator<<(QDebug c, const OpenTrade::Provider &provider)
{
    c.nospace() << "Provider("
                << "Id:" << provider.id() 
                << "IsConnected:" << provider.isConnected() 
                << "IsExecutionProvider:" << provider.isExecutionProvider() 
                << "IsHistoricalDataProvider:" << provider.isHistoricalDataProvider() 
                << "IsInstrumentProvider:" << provider.isInstrumentProvider() 
                << "IsMarketDataProvider:" << provider.isMarketDataProvider() 
                << "Name:" << provider.name() 
                << "Properties:" << provider.properties() 
                <<')';
    return c.space();
}
