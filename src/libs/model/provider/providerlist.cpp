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
#include "providerlist.h"

#include <QSharedData>

namespace OpenTrade {

namespace Internal {

class ProviderListPrivate : public QSharedData
{
public:
    int m_count;
};

} // namespace Internal

ProviderList::~ProviderList()
{

}

ProviderList& ProviderList::operator=(const ProviderList &other)
{
    d = other.d;
    return *this;
}

bool ProviderList::operator==(const ProviderList &other) const
{
    if(d == other.d)
      return true;

    return d->m_count == other.d->m_count;
}

int ProviderList::count() const
{
    return d->m_count;
}


} // namespace OpenTrade

QDebug operator<<(QDebug c, const OpenTrade::ProviderList &providerlist)
{
    c.nospace() << "ProviderList("
                << "Count:" << providerlist.count() 
                <<')';
    return c.space();
}
