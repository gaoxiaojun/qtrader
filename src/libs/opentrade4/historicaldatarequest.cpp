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
#include "historicaldatarequest.h"

#include <QSharedData>

namespace OpenTrade {

namespace Internal {

class HistoricalDataRequestPrivate : public QSharedData
{
public:
    long m_barSize;
    QDateTime m_beginDate;
    DataType m_dataType;
    QDateTime m_endDate;
    Instrument m_instrument;
};

} // namespace Internal

HistoricalDataRequest::~HistoricalDataRequest()
{

}

HistoricalDataRequest& HistoricalDataRequest::operator=(const HistoricalDataRequest &other)
{
    d = other.d;
    return *this;
}

bool HistoricalDataRequest::operator==(const HistoricalDataRequest &other) const
{
    if(d == other.d)
      return true;

    return d->m_barSize == other.d->m_barSize &&
           d->m_beginDate == other.d->m_beginDate &&
           d->m_dataType == other.d->m_dataType &&
           d->m_endDate == other.d->m_endDate &&
           d->m_instrument == other.d->m_instrument;
}

long HistoricalDataRequest::barSize() const
{
    return d->m_barSize;
}

QDateTime HistoricalDataRequest::beginDate() const
{
    return d->m_beginDate;
}

DataType HistoricalDataRequest::dataType() const
{
    return d->m_dataType;
}

QDateTime HistoricalDataRequest::endDate() const
{
    return d->m_endDate;
}

Instrument HistoricalDataRequest::instrument() const
{
    return d->m_instrument;
}


} // namespace OpenTrade

QDebug operator<<(QDebug c, const OpenTrade::HistoricalDataRequest &historicaldatarequest)
{
    c.nospace() << "HistoricalDataRequest("
                << "BarSize:" << historicaldatarequest.barSize() 
                << "BeginDate:" << historicaldatarequest.beginDate() 
                << "DataType:" << historicaldatarequest.dataType() 
                << "EndDate:" << historicaldatarequest.endDate() 
                << "Instrument:" << historicaldatarequest.instrument() 
                <<')';
    return c.space();
}
