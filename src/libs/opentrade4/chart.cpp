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
#include "chart.h"

#include <QSharedData>

namespace OpenTrade {

namespace Internal {

class ChartPrivate : public QSharedData
{
public:
    QColor m_backColor;
    QColor m_borderColor;
    QColor m_bottomAxisGridColor;
    QColor m_bottomAxisTextColor;
    QColor m_candleDownColor;
    QColor m_candleUpColor;
    QColor m_crossColor;
    QColor m_dateTipRectangleColor;
    QColor m_dateTipTextColor;
    QColor m_foreColor;
    QColor m_rightAxisGridColor;
    QColor m_rightAxisMajorTicksColor;
    QColor m_rightAxisMinorTicksColor;
    QColor m_rightAxisTextColor;
    QColor m_splitterColor;
    QColor m_valueTipRectangleColor;
    QColor m_valueTipTextColor;
    QColor m_volumeColor;
};

} // namespace Internal

Chart::Chart()
{

}

Chart::~Chart()
{

}

Chart& Chart::operator=(const Chart &other)
{
    d = other.d;
    return *this;
}

bool Chart::operator==(const Chart &other) const
{
    if(d == other.d)
      return true;

    return d->m_backColor == other.d->m_backColor &&
           d->m_borderColor == other.d->m_borderColor &&
           d->m_bottomAxisGridColor == other.d->m_bottomAxisGridColor &&
           d->m_bottomAxisTextColor == other.d->m_bottomAxisTextColor &&
           d->m_candleDownColor == other.d->m_candleDownColor &&
           d->m_candleUpColor == other.d->m_candleUpColor &&
           d->m_crossColor == other.d->m_crossColor &&
           d->m_dateTipRectangleColor == other.d->m_dateTipRectangleColor &&
           d->m_dateTipTextColor == other.d->m_dateTipTextColor &&
           d->m_foreColor == other.d->m_foreColor &&
           d->m_rightAxisGridColor == other.d->m_rightAxisGridColor &&
           d->m_rightAxisMajorTicksColor == other.d->m_rightAxisMajorTicksColor &&
           d->m_rightAxisMinorTicksColor == other.d->m_rightAxisMinorTicksColor &&
           d->m_rightAxisTextColor == other.d->m_rightAxisTextColor &&
           d->m_splitterColor == other.d->m_splitterColor &&
           d->m_valueTipRectangleColor == other.d->m_valueTipRectangleColor &&
           d->m_valueTipTextColor == other.d->m_valueTipTextColor &&
           d->m_volumeColor == other.d->m_volumeColor;
}

QColor Chart::backColor() const
{
    return d->m_backColor;
}

void Chart::setBackColor(const QColor& backcolor)
{
    d->m_backColor = backcolor;
}

QColor Chart::borderColor() const
{
    return d->m_borderColor;
}

void Chart::setBorderColor(const QColor& bordercolor)
{
    d->m_borderColor = bordercolor;
}

QColor Chart::bottomAxisGridColor() const
{
    return d->m_bottomAxisGridColor;
}

void Chart::setBottomAxisGridColor(const QColor& bottomaxisgridcolor)
{
    d->m_bottomAxisGridColor = bottomaxisgridcolor;
}

QColor Chart::bottomAxisTextColor() const
{
    return d->m_bottomAxisTextColor;
}

void Chart::setBottomAxisTextColor(const QColor& bottomaxistextcolor)
{
    d->m_bottomAxisTextColor = bottomaxistextcolor;
}

QColor Chart::candleDownColor() const
{
    return d->m_candleDownColor;
}

void Chart::setCandleDownColor(const QColor& candledowncolor)
{
    d->m_candleDownColor = candledowncolor;
}

QColor Chart::candleUpColor() const
{
    return d->m_candleUpColor;
}

void Chart::setCandleUpColor(const QColor& candleupcolor)
{
    d->m_candleUpColor = candleupcolor;
}

QColor Chart::crossColor() const
{
    return d->m_crossColor;
}

void Chart::setCrossColor(const QColor& crosscolor)
{
    d->m_crossColor = crosscolor;
}

QColor Chart::dateTipRectangleColor() const
{
    return d->m_dateTipRectangleColor;
}

void Chart::setDateTipRectangleColor(const QColor& datetiprectanglecolor)
{
    d->m_dateTipRectangleColor = datetiprectanglecolor;
}

QColor Chart::dateTipTextColor() const
{
    return d->m_dateTipTextColor;
}

void Chart::setDateTipTextColor(const QColor& datetiptextcolor)
{
    d->m_dateTipTextColor = datetiptextcolor;
}

QColor Chart::foreColor() const
{
    return d->m_foreColor;
}

void Chart::setForeColor(const QColor& forecolor)
{
    d->m_foreColor = forecolor;
}

QColor Chart::rightAxisGridColor() const
{
    return d->m_rightAxisGridColor;
}

void Chart::setRightAxisGridColor(const QColor& rightaxisgridcolor)
{
    d->m_rightAxisGridColor = rightaxisgridcolor;
}

QColor Chart::rightAxisMajorTicksColor() const
{
    return d->m_rightAxisMajorTicksColor;
}

void Chart::setRightAxisMajorTicksColor(const QColor& rightaxismajortickscolor)
{
    d->m_rightAxisMajorTicksColor = rightaxismajortickscolor;
}

QColor Chart::rightAxisMinorTicksColor() const
{
    return d->m_rightAxisMinorTicksColor;
}

void Chart::setRightAxisMinorTicksColor(const QColor& rightaxisminortickscolor)
{
    d->m_rightAxisMinorTicksColor = rightaxisminortickscolor;
}

QColor Chart::rightAxisTextColor() const
{
    return d->m_rightAxisTextColor;
}

void Chart::setRightAxisTextColor(const QColor& rightaxistextcolor)
{
    d->m_rightAxisTextColor = rightaxistextcolor;
}

QColor Chart::splitterColor() const
{
    return d->m_splitterColor;
}

void Chart::setSplitterColor(const QColor& splittercolor)
{
    d->m_splitterColor = splittercolor;
}

QColor Chart::valueTipRectangleColor() const
{
    return d->m_valueTipRectangleColor;
}

void Chart::setValueTipRectangleColor(const QColor& valuetiprectanglecolor)
{
    d->m_valueTipRectangleColor = valuetiprectanglecolor;
}

QColor Chart::valueTipTextColor() const
{
    return d->m_valueTipTextColor;
}

void Chart::setValueTipTextColor(const QColor& valuetiptextcolor)
{
    d->m_valueTipTextColor = valuetiptextcolor;
}

QColor Chart::volumeColor() const
{
    return d->m_volumeColor;
}

void Chart::setVolumeColor(const QColor& volumecolor)
{
    d->m_volumeColor = volumecolor;
}


} // namespace OpenTrade

QDebug operator<<(QDebug c, const OpenTrade::Chart &chart)
{
    c.nospace() << "Chart("
                << "BackColor:" << chart.backColor() 
                << "BorderColor:" << chart.borderColor() 
                << "BottomAxisGridColor:" << chart.bottomAxisGridColor() 
                << "BottomAxisTextColor:" << chart.bottomAxisTextColor() 
                << "CandleDownColor:" << chart.candleDownColor() 
                << "CandleUpColor:" << chart.candleUpColor() 
                << "CrossColor:" << chart.crossColor() 
                << "DateTipRectangleColor:" << chart.dateTipRectangleColor() 
                << "DateTipTextColor:" << chart.dateTipTextColor() 
                << "ForeColor:" << chart.foreColor() 
                << "RightAxisGridColor:" << chart.rightAxisGridColor() 
                << "RightAxisMajorTicksColor:" << chart.rightAxisMajorTicksColor() 
                << "RightAxisMinorTicksColor:" << chart.rightAxisMinorTicksColor() 
                << "RightAxisTextColor:" << chart.rightAxisTextColor() 
                << "SplitterColor:" << chart.splitterColor() 
                << "ValueTipRectangleColor:" << chart.valueTipRectangleColor() 
                << "ValueTipTextColor:" << chart.valueTipTextColor() 
                << "VolumeColor:" << chart.volumeColor() 
                <<')';
    return c.space();
}
