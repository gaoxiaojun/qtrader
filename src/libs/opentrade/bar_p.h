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

#ifndef BAR_P_H
#define BAR_P_H

#include <float.h>
#include <limits.h>

namespace OpenTrade {
class BarSeries;

namespace Internal {

class BarPrivate {
public:
    BarPrivate()
        :m_open(DBL_MAX), m_high(DBL_MAX), m_low(DBL_MAX), m_close(DBL_MAX),
          m_volume (DBL_MAX), m_series(0)
    {}

    BarPrivate(double open, double high, double low, double close, double volume)
        :m_open(open), m_high(high), m_low(low), m_close(close), m_volume(volume), m_series(0)
    {}

    inline bool isValid() const {
        if ((m_open == DBL_MAX) || (m_high == DBL_MAX) || (m_low == DBL_MAX) || (m_close == DBL_MAX)
                || (m_volume == DBL_MAX))
            return false;
        else
            return true;
    }

    friend class BarSeries;
public:
    double m_open;
    double m_high;
    double m_low;
    double m_close;
    double m_volume;
    BarSeries* m_series;
};

} // namespace Internal
} // namespace OpenTrade

#endif // BAR_P_H
