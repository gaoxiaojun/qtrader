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
#ifndef __OPENTRADE_CHART_H__
#define __OPENTRADE_CHART_H__

#include "opentrade_global.h"

#include <QSharedDataPointer>
#include <QDebug>
#include <QColor>


namespace OpenTrade {

namespace Internal {
class ChartPrivate;
}

class OPENTRADE_EXPORT Chart
{
public:

    Chart();
    ~Chart();

    Chart& operator=(const Chart &other);
    void swap(Chart &other) { qSwap(d, other.d); }

#ifdef Q_COMPILER_RVALUE_REFS
    inline Chart &operator=(Chart &&other)
    { qSwap(d, other.d); return *this; }
#endif

    bool operator==(const Chart &other) const;
    inline bool operator!=(const Chart &other) const { return !(operator==(other)); }


    QColor backColor() const;
    void setBackColor(const QColor& backcolor);

    QColor borderColor() const;
    void setBorderColor(const QColor& bordercolor);

    QColor bottomAxisGridColor() const;
    void setBottomAxisGridColor(const QColor& bottomaxisgridcolor);

    QColor bottomAxisTextColor() const;
    void setBottomAxisTextColor(const QColor& bottomaxistextcolor);

    QColor candleDownColor() const;
    void setCandleDownColor(const QColor& candledowncolor);

    QColor candleUpColor() const;
    void setCandleUpColor(const QColor& candleupcolor);

    QColor crossColor() const;
    void setCrossColor(const QColor& crosscolor);

    QColor dateTipRectangleColor() const;
    void setDateTipRectangleColor(const QColor& datetiprectanglecolor);

    QColor dateTipTextColor() const;
    void setDateTipTextColor(const QColor& datetiptextcolor);

    QColor foreColor() const;
    void setForeColor(const QColor& forecolor);

    QColor rightAxisGridColor() const;
    void setRightAxisGridColor(const QColor& rightaxisgridcolor);

    QColor rightAxisMajorTicksColor() const;
    void setRightAxisMajorTicksColor(const QColor& rightaxismajortickscolor);

    QColor rightAxisMinorTicksColor() const;
    void setRightAxisMinorTicksColor(const QColor& rightaxisminortickscolor);

    QColor rightAxisTextColor() const;
    void setRightAxisTextColor(const QColor& rightaxistextcolor);

    QColor splitterColor() const;
    void setSplitterColor(const QColor& splittercolor);

    QColor valueTipRectangleColor() const;
    void setValueTipRectangleColor(const QColor& valuetiprectanglecolor);

    QColor valueTipTextColor() const;
    void setValueTipTextColor(const QColor& valuetiptextcolor);

    QColor volumeColor() const;
    void setVolumeColor(const QColor& volumecolor);

private:
    QSharedDataPointer<Internal::ChartPrivate> d;
};

QDebug OPENTRADE_EXPORT operator << (QDebug, const Chart &chart);

} // namespace OpenTrade

Q_DECLARE_SHARED(OpenTrade::Chart)

#endif // __OPENTRADE_CHART_H__
