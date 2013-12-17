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
#include "transaction.h"

#include <QSharedData>

namespace OpenTrade {

namespace Internal {

class TransactionPrivate : public QSharedData
{
public:
    double m_cost;
    QDateTime m_dateTime;
    Instrument m_instrument;
    double m_pnL;
    double m_price;
    double m_qty;
    TransactionSide m_side;
    QString m_text;
};

} // namespace Internal

Transaction::~Transaction()
{

}

Transaction& Transaction::operator=(const Transaction &other)
{
    d = other.d;
    return *this;
}

bool Transaction::operator==(const Transaction &other) const
{
    if(d == other.d)
      return true;

    return d->m_cost == other.d->m_cost &&
           d->m_dateTime == other.d->m_dateTime &&
           d->m_instrument == other.d->m_instrument &&
           d->m_pnL == other.d->m_pnL &&
           d->m_price == other.d->m_price &&
           d->m_qty == other.d->m_qty &&
           d->m_side == other.d->m_side &&
           d->m_text == other.d->m_text;
}

double Transaction::cost() const
{
    return d->m_cost;
}

QDateTime Transaction::dateTime() const
{
    return d->m_dateTime;
}

Instrument Transaction::instrument() const
{
    return d->m_instrument;
}

double Transaction::pnL() const
{
    return d->m_pnL;
}

double Transaction::price() const
{
    return d->m_price;
}

double Transaction::qty() const
{
    return d->m_qty;
}

TransactionSide Transaction::side() const
{
    return d->m_side;
}

QString Transaction::text() const
{
    return d->m_text;
}


} // namespace OpenTrade

QDebug operator<<(QDebug c, const OpenTrade::Transaction &transaction)
{
    c.nospace() << "Transaction("
                << "Cost:" << transaction.cost() 
                << "DateTime:" << transaction.dateTime() 
                << "Instrument:" << transaction.instrument() 
                << "PnL:" << transaction.pnL() 
                << "Price:" << transaction.price() 
                << "Qty:" << transaction.qty() 
                << "Side:" << transaction.side() 
                << "Text:" << transaction.text() 
                <<')';
    return c.space();
}
