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
#include "usercommand.h"

#include <QSharedData>

namespace OpenTrade {

namespace Internal {

class UserCommandPrivate : public QSharedData
{
public:
    QDateTime m_dateTime;
    QString m_text;
};

} // namespace Internal

UserCommand::UserCommand(const QDateTime& datetime, const QString& text)
{

}

UserCommand::~UserCommand()
{

}

UserCommand& UserCommand::operator=(const UserCommand &other)
{
    d = other.d;
    return *this;
}

bool UserCommand::operator==(const UserCommand &other) const
{
    if(d == other.d)
      return true;

    return d->m_dateTime == other.d->m_dateTime &&
           d->m_text == other.d->m_text;
}

QDateTime UserCommand::dateTime() const
{
    return d->m_dateTime;
}

void UserCommand::setDateTime(const QDateTime& datetime)
{
    d->m_dateTime = datetime;
}

QString UserCommand::text() const
{
    return d->m_text;
}

void UserCommand::setText(const QString& text)
{
    d->m_text = text;
}


} // namespace OpenTrade

QDebug operator<<(QDebug c, const OpenTrade::UserCommand &usercommand)
{
    c.nospace() << "UserCommand("
                << "DateTime:" << usercommand.dateTime() 
                << "Text:" << usercommand.text() 
                <<')';
    return c.space();
}
