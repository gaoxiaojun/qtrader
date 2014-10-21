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
#include "barserieslist.h"

#include <QSharedData>

namespace OpenTrade {

namespace Internal {

class BarSeriesListPrivate : public QSharedData
{
public:
};

} // namespace Internal

BarSeriesList::BarSeriesList()
{

}

BarSeriesList::~BarSeriesList()
{

}

BarSeriesList& BarSeriesList::operator=(const BarSeriesList &other)
{
    d = other.d;
    return *this;
}

bool BarSeriesList::operator==(const BarSeriesList &other) const
{
    if(d == other.d)
      return true;

}


} // namespace OpenTrade

QDebug operator<<(QDebug c, const OpenTrade::BarSeriesList &barserieslist)
{
    c.nospace() << "BarSeriesList("
                <<')';
    return c.space();
}
