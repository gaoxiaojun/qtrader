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
#ifndef __OPENTRADE_USERINDICATOR_H__
#define __OPENTRADE_USERINDICATOR_H__

#include "opentrade_global.h"
#include "bar.h"
#include "barseries.h"
#include "indicator.h"

#include <QSharedDataPointer>
#include <QDebug>
#include <QDateTime>
#include <QString>


namespace OpenTrade {

namespace Internal {
class UserIndicatorPrivate;
}

class OPENTRADE_EXPORT UserIndicator
{
public:

    UserIndicator(const ISeries& input);
    ~UserIndicator();

    UserIndicator& operator=(const UserIndicator &other);
    void swap(UserIndicator &other) { qSwap(d, other.d); }

#ifdef Q_COMPILER_RVALUE_REFS
    inline UserIndicator &operator=(UserIndicator &&other)
    { qSwap(d, other.d); return *this; }
#endif

    bool operator==(const UserIndicator &other) const;
    inline bool operator!=(const UserIndicator &other) const { return !(operator==(other)); }

    double ago(int n);
    double calculate(int index);
    bool contains(const QDateTime& dateTime);
    bool contains(const Bar& bar);
    Cross crosses(const BarSeries& series, const Bar& bar);
    Cross crosses(const Indicator& indicator, const Bar& bar);
    bool crossesAbove(const BarSeries& series, const Bar& bar);
    bool crossesAbove(const Indicator& indicator, const Bar& bar);
    bool crossesBelow(const BarSeries& series, const Bar& bar);
    bool crossesBelow(const Indicator& indicator, const Bar& bar);
    QDateTime getDateTime(int index);
    void init();

    override int() const;

    override dateTime() const;

    ISeries input() const;

    override double() const;

    override double() const;

    override double() const;

    override double() const;

    override double() const;

    override double() const;

    override dateTime() const;

    QString name() const;
    void setName(const QString& name);

private:
    QSharedDataPointer<Internal::UserIndicatorPrivate> d;
};

QDebug OPENTRADE_EXPORT operator << (QDebug, const UserIndicator &userindicator);

} // namespace OpenTrade

Q_DECLARE_SHARED(OpenTrade::UserIndicator)

#endif // __OPENTRADE_USERINDICATOR_H__
