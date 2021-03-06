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

#ifndef __INSTRUMENT_H__
#define __INSTRUMENT_H__

#include "opentrade_global.h"

#include <QString>
#include <QDateTime>
#include <QDebug>
#include <qglobal.h>

namespace OpenTrade {

class OrderBook;
class Bar;
class Quote;
class Trade;

namespace Internal {
  class InstrumentPrivate;
}

/* TODO:
 * 确保是个immutable class 或者...
*/
class OPENTRADE_EXPORT Instrument
{
public:
    enum InstrumentType {
        None     = 0,
        Stock    = 1,
        Futures  = 2,
        Option   = 3,
        FutOpt   = 4,
        Bond     = 5,
        Index    = 6,
        ETF      = 7,
        Forex    = 8,
        MultiLeg = 9
    };

    enum PutCall {
        None = 0,
        Put  = 1,
        Call = 2
    };
    Instrument(Instrument::InstrumentType type, const QString& symbol);
    Instrument(Instrument::InstrumentType type, const QString& symbol, const QString& currency, const QString& exchange);
    Instrument(const Instrument& other);
    ~Instrument();

    Instrument& operator = (const Instrument& other);
    void swap(Instrument &other) { qSwap(d, other.d); }

#ifdef Q_COMPILER_RVALUE_REFS
    inline Instrument &operator=(Instrument &&other)
    { qSwap(d, other.d); return *this; }
#endif

    bool operator==(const Instrument &other) const;
    inline bool operator!=(const Instrument &other) const { return !(operator==(other)); }

    QString symbol() const;
    InstrumentType type() const;

    // 深度行情 Gets a reference to instrument order book
    OrderBook orderBook();
    // Gets last bar for this instrument
    Bar bar();
    // Gets last quote for this instrument
    Quote quote();
    // Gets last trade for this instrument
    Trade trade();

    /* 交易所 */
    QString exchange() const;
    void setExchange(const QString& exchange);

    /* 交易货币 */
    QString currency() const;
    void setCurrency(const QString& currency);

    /* 交易品种描述 */
    QString description() const;
    void setDescription(const QString& desc);

    /* 板块  */
    QString group() const;
    void setGroup(const QString& group);

    /* 行业 */
    QString sector() const;
    void setSector(const QString& sector);

    /* 价格格式,例如日元显示为两位,欧元显示至少4位 */
    QString priceFormat() const;
    void setPriceFormat(const QString format);

    /* 因子 */
    // For Derivatives: Contract Value Factor by which price must be adjusted to determine the true nominal value of
    // one futures/options contract.
    // (Qty * Price) * Factor = Nominal Value
    double factor() const;
    void setFactor(double factor);

    /* 保证金 */
    double margin() const;
    void setMargin(double margin);

    /* 价格最小变动单位 */
    double tickSize() const;
    void setTickSize(double tickSize);

    /* 到期日 Options or Futures */
    QDateTime maturity() const;
    void setMaturity(const QDateTime& date);

    /* strike价格,仅用于Options */
    double strike() const;
    void setStrike(double strike);

    /* 仅用于Options */
    PutCall putCall() const;
    void setPutCall(PutCall putCall);

private:
    QSharedDataPointer<Internal::InstrumentPrivate> d;
    friend class Internal::InstrumentPrivate;
};

class OPENTRADE_EXPORT Forex: public Instrument
{
public:
    Forex(const QString& symbol)
        :Instrument(Instrument::Forex, symbol)
    {}
};

class OPENTRADE_EXPORT Stock: public Instrument
{
public:
    Stock(const QString& symbol, const QString& currency, const QString& exchange)
        :Instrument(Instrument::Stock, symbol, currency, exchange)
    {}
};

class OPENTRADE_EXPORT Future: public Instrument
{
public:
    Future(const QString& symbol)
        :Instrument(Instrument::Futures, symbol)
    {}
};

QDebug operator<<(QDebug, const OpenTrade::Instrument &instrument);

} //namespace OpenTrade

Q_DECLARE_SHARED(OpenTrade::Instrument)

#endif // __INSTRUMENT_H__
