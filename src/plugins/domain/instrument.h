/****************************************************************************
**
** Copyright (C) 2013 Xiaojun Gao
** Contact: http://www.dailypips.org/legal
**
** This file is part of QTrader.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Digia gives you certain additional
** rights.  These rights are described in the Digia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
****************************************************************************/

#ifndef __INSTRUMENT_H__
#define __INSTRUMENT_H__

#include "domain_global.h"

#include <QString>
#include <QDateTime>


namespace Domain {

class OrderBook;
class Bar;
class Quote;
class Trade;

class DOMAIN_EXPORT Instrument
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

    enum PutCall {
        Put  = 0,
        Call = 1
    };

    Instrument(const QString& symbol, InstrumentType type);
    Instrument(const Instrument& other);
    Instrument& operator = (const Instrument& other);
    ~Instrument();

    QString symbol();
    InstrumentType instrumentType() ;

    /* 深度行情 */
    OrderBook orderBook();
    Bar bar();
    Quote quote();
    Trade trade();

    /* 交易所 */
    QString exchange();
    void setExchange(const QString& exchange);

    /* 交易货币 */
    QString currency();
    void setCurrency(const QString& currency);

    /* 交易品种描述 */
    QString description();
    void setDescription(const QString& desc);

    /* 板块  */
    QString group();
    void setGroup(const QString& group);

    /* 行业 */
    QString sector();
    void setSector(const QString& sector);

    /* 价格格式,例如日元显示为两位,欧元显示至少4位 */
    QString priceFormat();
    void setPriceFormat(const QString format);

    /* 因子 */
    double factor();
    void setFactor(double factor);

    /* 保证金 */
    double margin();
    void setMargin(double margin);

    double tickSize();
    void setTickSize(double tickSize);

    /* 到期日 */
    QDateTime maturity();
    void setMaturity(const QDateTime& date);

    /* strike价格,仅用于Options */
    double strike();
    void setStrike(double strike);

    /* 仅用于Options */
    PutCall putCall();
    void setPutCall(PutCall putCall);

private:
    Q_DECLARE_PRIVATE(Instrument)

};

} //namespace Domain

#endif // __INSTRUMENT_H__
