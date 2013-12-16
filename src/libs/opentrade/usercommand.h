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
#ifndef __OPENTRADE_USERCOMMAND_H__
#define __OPENTRADE_USERCOMMAND_H__

#include "opentrade_global.h"

#include <QSharedDataPointer>
#include <QDebug>
#include <QDateTime>
#include <QString>


namespace OpenTrade {

namespace Internal {
class UserCommandPrivate;
}

class OPENTRADE_EXPORT UserCommand
{
public:

    UserCommand(const QDateTime& datetime, const QString& text);
    ~UserCommand();

    UserCommand& operator=(const UserCommand &other);
    void swap(UserCommand &other) { qSwap(d, other.d); }

#ifdef Q_COMPILER_RVALUE_REFS
    inline UserCommand &operator=(UserCommand &&other)
    { qSwap(d, other.d); return *this; }
#endif

    bool operator==(const UserCommand &other) const;
    inline bool operator!=(const UserCommand &other) const { return !(operator==(other)); }


    QDateTime dateTime() const;
    void setDateTime(const QDateTime& datetime);

    QString text() const;
    void setText(const QString& text);

private:
    QSharedDataPointer<Internal::UserCommandPrivate> d;
};

QDebug OPENTRADE_EXPORT operator << (QDebug, const UserCommand &usercommand);

} // namespace OpenTrade

Q_DECLARE_SHARED(OpenTrade::UserCommand)

#endif // __OPENTRADE_USERCOMMAND_H__
