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
#include "userindicator.h"

#include <QSharedData>

namespace OpenTrade {

namespace Internal {

class UserIndicatorPrivate : public QSharedData
{
public:
    override m_int;
    override m_dateTime;
    ISeries m_input;
    override m_double;
    override m_double;
    override m_double;
    override m_double;
    override m_double;
    override m_double;
    override m_dateTime;
    QString m_name;
};

} // namespace Internal

UserIndicator::UserIndicator(const ISeries& input)
{

}

UserIndicator::~UserIndicator()
{

}

UserIndicator& UserIndicator::operator=(const UserIndicator &other)
{
    d = other.d;
    return *this;
}

bool UserIndicator::operator==(const UserIndicator &other) const
{
    if(d == other.d)
      return true;

    return d->m_int == other.d->m_int &&
           d->m_dateTime == other.d->m_dateTime &&
           d->m_input == other.d->m_input &&
           d->m_double == other.d->m_double &&
           d->m_double == other.d->m_double &&
           d->m_double == other.d->m_double &&
           d->m_double == other.d->m_double &&
           d->m_double == other.d->m_double &&
           d->m_double == other.d->m_double &&
           d->m_dateTime == other.d->m_dateTime &&
           d->m_name == other.d->m_name;
}

double UserIndicator::ago(int n)
{

}

double UserIndicator::calculate(int index)
{

}

bool UserIndicator::contains(const QDateTime& dateTime)
{

}

bool UserIndicator::contains(const Bar& bar)
{

}

Cross UserIndicator::crosses(const BarSeries& series, const Bar& bar)
{

}

Cross UserIndicator::crosses(const Indicator& indicator, const Bar& bar)
{

}

bool UserIndicator::crossesAbove(const BarSeries& series, const Bar& bar)
{

}

bool UserIndicator::crossesAbove(const Indicator& indicator, const Bar& bar)
{

}

bool UserIndicator::crossesBelow(const BarSeries& series, const Bar& bar)
{

}

bool UserIndicator::crossesBelow(const Indicator& indicator, const Bar& bar)
{

}

QDateTime UserIndicator::getDateTime(int index)
{

}

void UserIndicator::init()
{

}

override UserIndicator::int() const
{
    return d->m_int;
}

override UserIndicator::dateTime() const
{
    return d->m_dateTime;
}

ISeries UserIndicator::input() const
{
    return d->m_input;
}

override UserIndicator::double() const
{
    return d->m_double;
}

override UserIndicator::double() const
{
    return d->m_double;
}

override UserIndicator::double() const
{
    return d->m_double;
}

override UserIndicator::double() const
{
    return d->m_double;
}

override UserIndicator::double() const
{
    return d->m_double;
}

override UserIndicator::double() const
{
    return d->m_double;
}

override UserIndicator::dateTime() const
{
    return d->m_dateTime;
}

QString UserIndicator::name() const
{
    return d->m_name;
}

void UserIndicator::setName(const QString& name)
{
    d->m_name = name;
}


} // namespace OpenTrade

QDebug operator<<(QDebug c, const OpenTrade::UserIndicator &userindicator)
{
    c.nospace() << "UserIndicator("
                << "int:" << userindicator.int() 
                << "DateTime:" << userindicator.dateTime() 
                << "Input:" << userindicator.input() 
                << "double:" << userindicator.double() 
                << "double:" << userindicator.double() 
                << "double:" << userindicator.double() 
                << "double:" << userindicator.double() 
                << "double:" << userindicator.double() 
                << "double:" << userindicator.double() 
                << "DateTime:" << userindicator.dateTime() 
                << "Name:" << userindicator.name() 
                <<')';
    return c.space();
}
