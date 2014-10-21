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
#include "barseriesinfo.h"

#include <QSharedData>

namespace OpenTrade {

namespace Internal {

class BarSeriesInfoPrivate : public QSharedData
{
public:
    long m_barSize;
    BarType m_barType;
};

} // namespace Internal

BarSeriesInfo::~BarSeriesInfo()
{

}

BarSeriesInfo& BarSeriesInfo::operator=(const BarSeriesInfo &other)
{
    d = other.d;
    return *this;
}

bool BarSeriesInfo::operator==(const BarSeriesInfo &other) const
{
    if(d == other.d)
      return true;

    return d->m_barSize == other.d->m_barSize &&
           d->m_barType == other.d->m_barType;
}

long BarSeriesInfo::barSize() const
{
    return d->m_barSize;
}

void BarSeriesInfo::setBarSize(long barsize)
{
    d->m_barSize = barsize;
}

BarType BarSeriesInfo::barType() const
{
    return d->m_barType;
}

void BarSeriesInfo::setBarType(BarType bartype)
{
    d->m_barType = bartype;
}


} // namespace OpenTrade

QDebug operator<<(QDebug c, const OpenTrade::BarSeriesInfo &barseriesinfo)
{
    c.nospace() << "BarSeriesInfo("
                << "BarSize:" << barseriesinfo.barSize() 
                << "BarType:" << barseriesinfo.barType() 
                <<')';
    return c.space();
}
