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
#ifndef __OPENTRADE_INSTRUMENT_H__
#define __OPENTRADE_INSTRUMENT_H__

#include "opentrade_global.h"
#include "altidgrouplist.h"
#include "bar.h"
#include "orderbook.h"
#include "quote.h"
#include "trade.h"

#include <QSharedDataPointer>
#include <QDebug>
#include <QString>
#include <QDateTime>


namespace OpenTrade {

namespace Internal {
class InstrumentPrivate;
}

class OPENTRADE_EXPORT Instrument
{
public:
    enum InstrumentType {
        Stock = 0,
        Futures = 1,
        Option = 2,
        FutOpt = 3,
        Bond = 4,
        Index = 5,
        ETF = 6,
        FX = 7,
        MultiLeg = 8
    };

public:

    Instrument(InstrumentType type, const QString& symbol);
    Instrument(InstrumentType type, const QString& symbol, const QString& secutityExchange, const QString& currency);
    ~Instrument();

    Instrument& operator=(const Instrument &other);
    void swap(Instrument &other) { qSwap(d, other.d); }

#ifdef Q_COMPILER_RVALUE_REFS
    inline Instrument &operator=(Instrument &&other)
    { qSwap(d, other.d); return *this; }
#endif

    bool operator==(const Instrument &other) const;
    inline bool operator!=(const Instrument &other) const { return !(operator==(other)); }

    QString getExchange(const QString& source);
    QString getSymbol(const QString& source);

    AltIDGroupList altIDGroups() const;
    void setAltIDGroups(const AltIDGroupList& altidgroups);

    Bar bar() const;

    QString currency() const;
    void setCurrency(const QString& currency);

    QString description() const;
    void setDescription(const QString& description);

    QString exchange() const;
    void setExchange(const QString& exchange);

    double factor() const;
    void setFactor(double factor);

    QString group() const;
    void setGroup(const QString& group);

    double margin() const;
    void setMargin(double margin);

    QDateTime maturity() const;
    void setMaturity(const QDateTime& maturity);

    OrderBook orderBook() const;

    QString priceFormat() const;
    void setPriceFormat(const QString& priceformat);

    PutCall putCall() const;
    void setPutCall(PutCall putcall);

    Quote quote() const;

    QString sector() const;
    void setSector(const QString& sector);

    double strike() const;
    void setStrike(double strike);

    QString symbol() const;

    double tickSize() const;
    void setTickSize(double ticksize);

    Trade trade() const;

    InstrumentType type() const;

private:
    QSharedDataPointer<Internal::InstrumentPrivate> d;
};

QDebug OPENTRADE_EXPORT operator << (QDebug, const Instrument &instrument);

} // namespace OpenTrade

Q_DECLARE_SHARED(OpenTrade::Instrument)

#endif // __OPENTRADE_INSTRUMENT_H__
