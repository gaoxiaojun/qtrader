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

#ifndef ORDER_H
#define ORDER_H

#include "opentrade_global.h"
#include "instrument.h"

#include <QObject>

namespace OpenTrade {

namespace Internal {
  class OrderPrivate;
}

class OPENTRADE_EXPORT Order : public QObject
{
    Q_OBJECT

public:
    enum OrderStatus {
        PendingNew      = 0,
        New             = 1,
        PartiallyFilled = 2,
        Filled          = 3,
        PendingCancel   = 4,
        Cancelled       = 5,
        Expired         = 6,
        PendingReplace  = 7,
        Replaced        = 8,
        Rejected        = 9
    };

    enum OrderSide {
        Buy  = 0,
        Sell = 1
    };

    enum OrderType {
        Market          = 0,
        Limit           = 1,
        Stop            = 2,
        StopLimit       = 3,
        Trail           = 4,
        TrailLimit      = 5,
        MarketOnClose   = 6
    };

    enum TimeInForce {
        DAY = 0,
        GTC = 1,
        OPG = 2,
        LOC = 3,
        FOK = 4,
        GTX = 5,
        GTD = 6,
        ATC = 7,
        GFS = 8
    };


public:
    explicit Order(const Instrument& inst, QObject *parent = 0);
    ~Order();

    void cancel();
    void replace();
    void send();

    QString account();
    void setAccount(const QString& acct);

    QString clientId();
    void setClientId(const QString& id);

    double avgPrice();
    double cumQty();
    QDateTime createTime();

    unsigned int expireSeconds();

    QDateTime expireTime();
    void setExpireTime(const QDateTime& expire);

    Instrument instrument();

    double lastPrice();
    double lastQty();
    double leavesQty();

    QString ocaGroup();
    void setOCAGroup(const QString& oca);

    double price();
    void setPrice(double price);

    double qty();
    void setQty(double qty);

    OrderSide side();
    void setSide(OrderSide side);

    OrderStatus status();
    void setStatus(OrderStatus status);

    double stopPrice();
    void setStopPrice(double price);

    bool strategyFill();
    double strategyPrice();

    QString text();
    void setText(const QString& text);

    TimeInForce tif();
    void setTIF(TimeInForce tif);

    double trailingAmt();
    void setTrailingAmt(double amt);

    OrderType type();
    void setOrderType(OrderType type);

    unsigned int route();
    void setRoute(unsigned int route);

    bool isCancelled();
    bool isDone();
    bool isExPired();
    bool isFilled();
    bool isNew();
    bool isPartiallyFilled();
    bool isPendingCancel();
    bool isPendingNew();
    bool isPendingReplace();
    bool isRejected();

signals:
    void orderStatusChanged(OrderStatus oldStatus, OrderStatus newStatus);
    void orderNew();
    void orderPartiallyFilled();
    void orderFilled();
    void orderCancelled();
    void orderExpired();
    void orderReplace();
    void orderRejected();
    void orderCancelRejected();
    void orderReplaceRejected();
    void orderDone();

public slots:

private:
    friend class Internal::OrderPrivate;
    Internal::OrderPrivate *d;
};

} // namespace OpenTrade

#endif // ORDER_H
