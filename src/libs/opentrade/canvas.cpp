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
#include "canvas.h"

#include <QSharedData>

namespace OpenTrade {

namespace Internal {

class CanvasPrivate : public QSharedData
{
public:
};

} // namespace Internal

Canvas::Canvas(const QString& name)
{

}

Canvas::~Canvas()
{

}

Canvas& Canvas::operator=(const Canvas &other)
{
    d = other.d;
    return *this;
}

bool Canvas::operator==(const Canvas &other) const
{
    if(d == other.d)
      return true;

}

void Canvas::add(const BarSeries& series)
{

}

void Canvas::add(const Indicator& indicator)
{

}

void Canvas::add(const Order& order)
{

}

void Canvas::add(const QuoteSeries& quoteSeries)
{

}

void Canvas::add(const TimeSeries& series)
{

}

void Canvas::add(const TradeSeries& tradeSeries)
{

}

void Canvas::add(const Transaction& transaction)
{

}

void Canvas::cd(int pad)
{

}

void Canvas::clear()
{

}

void Canvas::divide(int x, int y)
{

}

void Canvas::run()
{

}

void Canvas::setRangeX(const QDateTime& dateTime1, const QDateTime& dateTime2)
{

}

void Canvas::setRangeX(double minX, double maxX)
{

}

void Canvas::setRangeY(double minY, double maxY)
{

}

void Canvas::update()
{

}


} // namespace OpenTrade

QDebug operator<<(QDebug c, const OpenTrade::Canvas &canvas)
{
    c.nospace() << "Canvas("
                <<')';
    return c.space();
}
