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
#include "historicaldataprovider.h"

#include <QSharedData>

namespace OpenTrade {

namespace Internal {

class HistoricalDataProviderPrivate : public QSharedData
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

HistoricalDataProvider::~HistoricalDataProvider()
{

}

HistoricalDataProvider& HistoricalDataProvider::operator=(const HistoricalDataProvider &other)
{
    d = other.d;
    return *this;
}

bool HistoricalDataProvider::operator==(const HistoricalDataProvider &other) const
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

void HistoricalDataProvider::connect()
{

}

void HistoricalDataProvider::disconnect()
{

}

int HistoricalDataProvider::id() const
{
    return d->m_id;
}

bool HistoricalDataProvider::isConnected() const
{
    return d->m_isConnected;
}

bool HistoricalDataProvider::isExecutionProvider() const
{
    return d->m_isExecutionProvider;
}

bool HistoricalDataProvider::isHistoricalDataProvider() const
{
    return d->m_isHistoricalDataProvider;
}

bool HistoricalDataProvider::isInstrumentProvider() const
{
    return d->m_isInstrumentProvider;
}

bool HistoricalDataProvider::isMarketDataProvider() const
{
    return d->m_isMarketDataProvider;
}

QString HistoricalDataProvider::name() const
{
    return d->m_name;
}

ProviderPropertyList HistoricalDataProvider::properties() const
{
    return d->m_properties;
}

void HistoricalDataProvider::setProperties(const ProviderPropertyList& properties)
{
    d->m_properties = properties;
}


} // namespace OpenTrade

QDebug operator<<(QDebug c, const OpenTrade::HistoricalDataProvider &historicaldataprovider)
{
    c.nospace() << "HistoricalDataProvider("
                << "Id:" << historicaldataprovider.id() 
                << "IsConnected:" << historicaldataprovider.isConnected() 
                << "IsExecutionProvider:" << historicaldataprovider.isExecutionProvider() 
                << "IsHistoricalDataProvider:" << historicaldataprovider.isHistoricalDataProvider() 
                << "IsInstrumentProvider:" << historicaldataprovider.isInstrumentProvider() 
                << "IsMarketDataProvider:" << historicaldataprovider.isMarketDataProvider() 
                << "Name:" << historicaldataprovider.name() 
                << "Properties:" << historicaldataprovider.properties() 
                <<')';
    return c.space();
}
