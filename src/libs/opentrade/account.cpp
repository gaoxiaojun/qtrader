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

#include "account.h"

#include <QReadWriteLock>

namespace OpenTrade {

namespace Internal {
class AccountPrivate {
public:
    AccountPrivate(const QString& acctName)
        :m_name(acctName)
    {}

    QString m_name;
    QDateTime m_last;
    QReadWriteLock m_locker;
};

} // namespace Internal

Account::Account(const QString& acctName, QObject *parent) :
    QObject(parent), d(new Internal::AccountPrivate(acctName))
{
}

Account::~Account()
{
    delete d;
}

const QString& Account::accountName() const
{
    return d->m_name;
}

QVariant Account::field(const QString& name) const
{
    QReadLocker locker(&d->m_locker);
    return this->property (name.toUtf8().data());
}

void Account::setField(const QString& name, const QVariant & value)
{
    QWriteLocker locker(&d->m_locker);
    this->setProperty (name.toUtf8().data(), value);
}

const QDateTime& Account::lastUpdateTime() const
{
    QReadLocker locker(&d->m_locker);
    return d->m_last;

}
void Account::setLastUpdateTime(const QDateTime& last)
{
    QWriteLocker locker(&d->m_locker);
    d->m_last = last;
}

} // namespace OpenTrade
