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
#include "instrumentprovider.h"

#include <QSharedData>

namespace OpenTrade {

namespace Internal {

class InstrumentProviderPrivate : public QSharedData
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

InstrumentProvider::~InstrumentProvider()
{

}

InstrumentProvider& InstrumentProvider::operator=(const InstrumentProvider &other)
{
    d = other.d;
    return *this;
}

bool InstrumentProvider::operator==(const InstrumentProvider &other) const
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

void InstrumentProvider::connect()
{

}

void InstrumentProvider::disconnect()
{

}

int InstrumentProvider::id() const
{
    return d->m_id;
}

bool InstrumentProvider::isConnected() const
{
    return d->m_isConnected;
}

bool InstrumentProvider::isExecutionProvider() const
{
    return d->m_isExecutionProvider;
}

bool InstrumentProvider::isHistoricalDataProvider() const
{
    return d->m_isHistoricalDataProvider;
}

bool InstrumentProvider::isInstrumentProvider() const
{
    return d->m_isInstrumentProvider;
}

bool InstrumentProvider::isMarketDataProvider() const
{
    return d->m_isMarketDataProvider;
}

QString InstrumentProvider::name() const
{
    return d->m_name;
}

ProviderPropertyList InstrumentProvider::properties() const
{
    return d->m_properties;
}

void InstrumentProvider::setProperties(const ProviderPropertyList& properties)
{
    d->m_properties = properties;
}


} // namespace OpenTrade

QDebug operator<<(QDebug c, const OpenTrade::InstrumentProvider &instrumentprovider)
{
    c.nospace() << "InstrumentProvider("
                << "Id:" << instrumentprovider.id() 
                << "IsConnected:" << instrumentprovider.isConnected() 
                << "IsExecutionProvider:" << instrumentprovider.isExecutionProvider() 
                << "IsHistoricalDataProvider:" << instrumentprovider.isHistoricalDataProvider() 
                << "IsInstrumentProvider:" << instrumentprovider.isInstrumentProvider() 
                << "IsMarketDataProvider:" << instrumentprovider.isMarketDataProvider() 
                << "Name:" << instrumentprovider.name() 
                << "Properties:" << instrumentprovider.properties() 
                <<')';
    return c.space();
}
