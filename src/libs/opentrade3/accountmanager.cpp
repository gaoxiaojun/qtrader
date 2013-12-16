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

#include "accountmanager.h"

#include <QMap>
#include <QReadWriteLock>

namespace OpenTrade {

namespace Internal {
class AccountManagerPrivate
{
public:
    AccountManagerPrivate() {}

    QMap<QString, Account*> m_accounts;
    QReadWriteLock m_locker;
};

} // namespace Internal

static AccountManager* m_instance = 0;

AccountManager::AccountManager(QObject *parent) :
    QObject(parent), d(new Internal::AccountManagerPrivate())
{
    m_instance = this;
}

AccountManager::~AccountManager ()
{
    delete d;
    m_instance = 0;
}

AccountManager* AccountManager::instance ()
{
    if (Q_UNLIKELY(!m_instance))
        m_instance = new AccountManager();

    return m_instance;
}

Account* AccountManager::createAccount(const QString& acctName)
{
    Account* acct = new Account(acctName, this);
    QWriteLocker locker(&d->m_locker);
    d->m_accounts.insert(acctName, acct);
    return acct;
}

Account* AccountManager::value(const QString& acctName)
{
    QReadLocker locker(&d->m_locker);
    if(d->m_accounts.contains (acctName))
        return d->m_accounts.value (acctName);
    else
        return 0;
}

} // namespace OpenTrade
