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
#ifndef __OPENTRADE_PORTFOLIOACCOUNT_H__
#define __OPENTRADE_PORTFOLIOACCOUNT_H__

#include "opentrade_global.h"

#include <QSharedDataPointer>
#include <QDebug>
#include <QDateTime>
#include <QString>


namespace OpenTrade {

namespace Internal {
class PortfolioAccountPrivate;
}

class OPENTRADE_EXPORT PortfolioAccount
{
public:

    ~PortfolioAccount();

    PortfolioAccount& operator=(const PortfolioAccount &other);
    void swap(PortfolioAccount &other) { qSwap(d, other.d); }

#ifdef Q_COMPILER_RVALUE_REFS
    inline PortfolioAccount &operator=(PortfolioAccount &&other)
    { qSwap(d, other.d); return *this; }
#endif

    bool operator==(const PortfolioAccount &other) const;
    inline bool operator!=(const PortfolioAccount &other) const { return !(operator==(other)); }

    void clear();
    void deposit(const QDateTime& datetime, double value);
    void deposit(const QString& currencyCode, double value);
    void deposit(const QDateTime& datetime, double value, const QString& text);
    void deposit(const QString& currencyCode, double value, const QDateTime& dateTime);
    void deposit(const QString& currencyCode, double value, const QDateTime& dateTime, const QString& text);
    void withdraw(const QDateTime& datetime, double value);
    void withdraw(const QString& currencyCode, double value);
    void withdraw(const QDateTime& datetime, double value, const QString& text);
    void withdraw(const QString& currencyCode, double value, const QDateTime& dateTime);
    void withdraw(const QString& currencyCode, double value, const QDateTime& dateTime, const QString& text);

private:
    QSharedDataPointer<Internal::PortfolioAccountPrivate> d;
};

QDebug OPENTRADE_EXPORT operator << (QDebug, const PortfolioAccount &portfolioaccount);

} // namespace OpenTrade

Q_DECLARE_SHARED(OpenTrade::PortfolioAccount)

#endif // __OPENTRADE_PORTFOLIOACCOUNT_H__
