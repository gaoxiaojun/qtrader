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
#include "clock.h"

#include <QSharedData>

namespace OpenTrade {

namespace Internal {

class ClockPrivate : public QSharedData
{
public:
    static m_dateTime;
};

} // namespace Internal

Clock::Clock()
{

}

Clock::~Clock()
{

}

Clock& Clock::operator=(const Clock &other)
{
    d = other.d;
    return *this;
}

bool Clock::operator==(const Clock &other) const
{
    if(d == other.d)
      return true;

    return d->m_dateTime == other.d->m_dateTime;
}

static Clock::dateTime() const
{
    return d->m_dateTime;
}


} // namespace OpenTrade

QDebug operator<<(QDebug c, const OpenTrade::Clock &clock)
{
    c.nospace() << "Clock("
                << "DateTime:" << clock.dateTime() 
                <<')';
    return c.space();
}
