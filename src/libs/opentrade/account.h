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

#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <QObject>
#include <QString>
#include <QVariant>
#include <QDateTime>

namespace OpenTrade {

namespace Internal {
  class AccountPrivate;
}

class Account : public QObject
{
    Q_OBJECT
public:
    Account(const QString& acctName, QObject *parent = 0);
    ~Account();

    double buyingPower() const;
    const QString& accountName() const;

    QVariant field(const QString& name) const;
    void setField(const QString& name, const QVariant & value);
    const QDateTime& lastUpdateTime() const;
    void setLastUpdateTime(const QDateTime& last);
    // Orders
    // Positions
    // addOrder()
    // addPosition()

signals:

public slots:

private:
    Internal::AccountPrivate *d;
};

} // namespace OpenTrade

#endif // ACCOUNT_H
