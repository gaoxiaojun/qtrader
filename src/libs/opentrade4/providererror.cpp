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
#include "providererror.h"

#include <QSharedData>

namespace OpenTrade {

namespace Internal {

class ProviderErrorPrivate : public QSharedData
{
public:
    int m_code;
    QDateTime m_dateTime;
    int m_id;
    QString m_message;
    QString m_provider;
};

} // namespace Internal

ProviderError::~ProviderError()
{

}

ProviderError& ProviderError::operator=(const ProviderError &other)
{
    d = other.d;
    return *this;
}

bool ProviderError::operator==(const ProviderError &other) const
{
    if(d == other.d)
      return true;

    return d->m_code == other.d->m_code &&
           d->m_dateTime == other.d->m_dateTime &&
           d->m_id == other.d->m_id &&
           d->m_message == other.d->m_message &&
           d->m_provider == other.d->m_provider;
}

int ProviderError::code() const
{
    return d->m_code;
}

QDateTime ProviderError::dateTime() const
{
    return d->m_dateTime;
}

int ProviderError::id() const
{
    return d->m_id;
}

QString ProviderError::message() const
{
    return d->m_message;
}

QString ProviderError::provider() const
{
    return d->m_provider;
}


} // namespace OpenTrade

QDebug operator<<(QDebug c, const OpenTrade::ProviderError &providererror)
{
    c.nospace() << "ProviderError("
                << "Code:" << providererror.code() 
                << "DateTime:" << providererror.dateTime() 
                << "Id:" << providererror.id() 
                << "Message:" << providererror.message() 
                << "Provider:" << providererror.provider() 
                <<')';
    return c.space();
}
