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
#include "barrequest.h"

#include <QSharedData>

namespace OpenTrade {

namespace Internal {

class BarRequestPrivate : public QSharedData
{
public:
    long m_barSize;
    BarType m_barType;
    bool m_isBarFactoryRequest;
};

} // namespace Internal

BarRequest::BarRequest(BarType barType, long barSize, bool isBarFactoryRequest)
{

}

BarRequest::~BarRequest()
{

}

BarRequest& BarRequest::operator=(const BarRequest &other)
{
    d = other.d;
    return *this;
}

bool BarRequest::operator==(const BarRequest &other) const
{
    if(d == other.d)
      return true;

    return d->m_barSize == other.d->m_barSize &&
           d->m_barType == other.d->m_barType &&
           d->m_isBarFactoryRequest == other.d->m_isBarFactoryRequest;
}

long BarRequest::barSize() const
{
    return d->m_barSize;
}

BarType BarRequest::barType() const
{
    return d->m_barType;
}

bool BarRequest::isBarFactoryRequest() const
{
    return d->m_isBarFactoryRequest;
}

void BarRequest::setIsBarFactoryRequest(bool isbarfactoryrequest)
{
    d->m_isBarFactoryRequest = isbarfactoryrequest;
}


} // namespace OpenTrade

QDebug operator<<(QDebug c, const OpenTrade::BarRequest &barrequest)
{
    c.nospace() << "BarRequest("
                << "BarSize:" << barrequest.barSize() 
                << "BarType:" << barrequest.barType() 
                << "isBarFactoryRequest:" << barrequest.isBarFactoryRequest() 
                <<')';
    return c.space();
}
