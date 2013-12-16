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
#include "position.h"

#include <QSharedData>

namespace OpenTrade {

namespace Internal {

class PositionPrivate : public QSharedData
{
public:
    double m_amount;
    double m_debt;
    QDateTime m_entryDate;
    double m_entryPrice;
    double m_entryQty;
    Instrument m_instrument;
    double m_margin;
    double m_qty;
    double m_qtyBought;
    double m_qtySold;
    double m_qtySoldShort;
    PositionSide m_side;
    TransactionList m_transactions;
};

} // namespace Internal

Position::~Position()
{

}

Position& Position::operator=(const Position &other)
{
    d = other.d;
    return *this;
}

bool Position::operator==(const Position &other) const
{
    if(d == other.d)
      return true;

    return d->m_amount == other.d->m_amount &&
           d->m_debt == other.d->m_debt &&
           d->m_entryDate == other.d->m_entryDate &&
           d->m_entryPrice == other.d->m_entryPrice &&
           d->m_entryQty == other.d->m_entryQty &&
           d->m_instrument == other.d->m_instrument &&
           d->m_margin == other.d->m_margin &&
           d->m_qty == other.d->m_qty &&
           d->m_qtyBought == other.d->m_qtyBought &&
           d->m_qtySold == other.d->m_qtySold &&
           d->m_qtySoldShort == other.d->m_qtySoldShort &&
           d->m_side == other.d->m_side &&
           d->m_transactions == other.d->m_transactions;
}

double Position::getCashFlow()
{

}

double Position::getDebtValue()
{

}

qint64 Position::getDuration()
{

}

double Position::getLeverage()
{

}

double Position::getMarginValue()
{

}

double Position::getNetCashFlow()
{

}

double Position::getNetPnL()
{

}

double Position::getNetPnLPercent()
{

}

double Position::getPnL()
{

}

double Position::getPnLPercent()
{

}

double Position::getPrice()
{

}

double Position::getUnrealizedPnL()
{

}

double Position::getValue()
{

}

double Position::amount() const
{
    return d->m_amount;
}

double Position::debt() const
{
    return d->m_debt;
}

QDateTime Position::entryDate() const
{
    return d->m_entryDate;
}

double Position::entryPrice() const
{
    return d->m_entryPrice;
}

double Position::entryQty() const
{
    return d->m_entryQty;
}

Instrument Position::instrument() const
{
    return d->m_instrument;
}

double Position::margin() const
{
    return d->m_margin;
}

double Position::qty() const
{
    return d->m_qty;
}

double Position::qtyBought() const
{
    return d->m_qtyBought;
}

double Position::qtySold() const
{
    return d->m_qtySold;
}

double Position::qtySoldShort() const
{
    return d->m_qtySoldShort;
}

PositionSide Position::side() const
{
    return d->m_side;
}

TransactionList Position::transactions() const
{
    return d->m_transactions;
}


} // namespace OpenTrade

QDebug operator<<(QDebug c, const OpenTrade::Position &position)
{
    c.nospace() << "Position("
                << "Amount:" << position.amount() 
                << "Debt:" << position.debt() 
                << "EntryDate:" << position.entryDate() 
                << "EntryPrice:" << position.entryPrice() 
                << "EntryQty:" << position.entryQty() 
                << "Instrument:" << position.instrument() 
                << "Margin:" << position.margin() 
                << "Qty:" << position.qty() 
                << "QtyBought:" << position.qtyBought() 
                << "QtySold:" << position.qtySold() 
                << "QtySoldShort:" << position.qtySoldShort() 
                << "Side:" << position.side() 
                << "Transactions:" << position.transactions() 
                <<')';
    return c.space();
}
