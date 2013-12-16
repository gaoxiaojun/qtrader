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
#include "portfolioaccount.h"

#include <QSharedData>

namespace OpenTrade {

namespace Internal {

class PortfolioAccountPrivate : public QSharedData
{
public:
};

} // namespace Internal

PortfolioAccount::~PortfolioAccount()
{

}

PortfolioAccount& PortfolioAccount::operator=(const PortfolioAccount &other)
{
    d = other.d;
    return *this;
}

bool PortfolioAccount::operator==(const PortfolioAccount &other) const
{
    if(d == other.d)
      return true;

}

void PortfolioAccount::clear()
{

}

void PortfolioAccount::deposit(const QDateTime& datetime, double value)
{

}

void PortfolioAccount::deposit(const QString& currencyCode, double value)
{

}

void PortfolioAccount::deposit(const QDateTime& datetime, double value, const QString& text)
{

}

void PortfolioAccount::deposit(const QString& currencyCode, double value, const QDateTime& dateTime)
{

}

void PortfolioAccount::deposit(const QString& currencyCode, double value, const QDateTime& dateTime, const QString& text)
{

}

void PortfolioAccount::withdraw(const QDateTime& datetime, double value)
{

}

void PortfolioAccount::withdraw(const QString& currencyCode, double value)
{

}

void PortfolioAccount::withdraw(const QDateTime& datetime, double value, const QString& text)
{

}

void PortfolioAccount::withdraw(const QString& currencyCode, double value, const QDateTime& dateTime)
{

}

void PortfolioAccount::withdraw(const QString& currencyCode, double value, const QDateTime& dateTime, const QString& text)
{

}


} // namespace OpenTrade

QDebug operator<<(QDebug c, const OpenTrade::PortfolioAccount &portfolioaccount)
{
    c.nospace() << "PortfolioAccount("
                <<')';
    return c.space();
}
