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
#include "providermanager.h"

#include <QSharedData>

namespace OpenTrade {

namespace Internal {

class ProviderManagerPrivate : public QSharedData
{
public:
    static m_providerList;
};

} // namespace Internal

ProviderManager::~ProviderManager()
{

}

ProviderManager& ProviderManager::operator=(const ProviderManager &other)
{
    d = other.d;
    return *this;
}

bool ProviderManager::operator==(const ProviderManager &other) const
{
    if(d == other.d)
      return true;

    return d->m_providerList == other.d->m_providerList;
}

static ProviderManager::providerList() const
{
    return d->m_providerList;
}

void ProviderManager::setProviderList(const static& providerlist)
{
    d->m_providerList = providerlist;
}


} // namespace OpenTrade

QDebug operator<<(QDebug c, const OpenTrade::ProviderManager &providermanager)
{
    c.nospace() << "ProviderManager("
                << "ProviderList:" << providermanager.providerList() 
                <<')';
    return c.space();
}
