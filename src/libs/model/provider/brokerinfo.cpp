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
#include "brokerinfo.h"

#include <QSharedData>

namespace OpenTrade {

namespace Internal {

class BrokerInfoPrivate : public QSharedData
{
public:
    BrokerAccountList m_accounts;
};

} // namespace Internal

BrokerInfo::BrokerInfo()
{

}

BrokerInfo::~BrokerInfo()
{

}

BrokerInfo& BrokerInfo::operator=(const BrokerInfo &other)
{
    d = other.d;
    return *this;
}

bool BrokerInfo::operator==(const BrokerInfo &other) const
{
    if(d == other.d)
      return true;

    return d->m_accounts == other.d->m_accounts;
}

BrokerAccount BrokerInfo::addAccount(const QString& name)
{

}

BrokerAccountList BrokerInfo::accounts() const
{
    return d->m_accounts;
}


} // namespace OpenTrade

QDebug operator<<(QDebug c, const OpenTrade::BrokerInfo &brokerinfo)
{
    c.nospace() << "BrokerInfo("
                << "Accounts:" << brokerinfo.accounts() 
                <<')';
    return c.space();
}
