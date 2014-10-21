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

#ifndef ACCOUNTMANAGER_H
#define ACCOUNTMANAGER_H

#include "account.h"

#include <QObject>

namespace OpenTrade {

namespace Internal {
  class AccountManagerPrivate;
}

class AccountManager : public QObject
{
    Q_OBJECT
public:
    ~AccountManager();

    static AccountManager* instance();

    Account* createAccount(const QString& acctName);
    Account* value(const QString& acctName);

signals:

public slots:

private:
    explicit AccountManager(QObject *parent = 0);
    Q_DISABLE_COPY(AccountManager)
    Internal::AccountManagerPrivate *d;
};

} // namespace OpenTrade

#endif // ACCOUNTMANAGER_H
