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
#ifndef __OPENTRADE_SOLUTION_H__
#define __OPENTRADE_SOLUTION_H__

#include "opentrade_global.h"
#include "performance.h"
#include "portfolio.h"
#include "projectlist.h"
#include "datarequests.h"
#include "statistics.h"

#include <QSharedDataPointer>
#include <QDebug>
#include <QString>
#include <QDateTime>


namespace OpenTrade {

namespace Internal {
class SolutionPrivate;
}

class OPENTRADE_EXPORT Solution
{
public:

    ~Solution();

    Solution& operator=(const Solution &other);
    void swap(Solution &other) { qSwap(d, other.d); }

#ifdef Q_COMPILER_RVALUE_REFS
    inline Solution &operator=(Solution &&other)
    { qSwap(d, other.d); return *this; }
#endif

    bool operator==(const Solution &other) const;
    inline bool operator!=(const Solution &other) const { return !(operator==(other)); }


    double cash() const;
    void setCash(double cash);

    QString name() const;
    void setName(const QString& name);

    Performance performance() const;
    void setPerformance(const Performance& performance);

    Portfolio portfolio() const;
    void setPortfolio(const Portfolio& portfolio);

    ProjectList projects() const;
    void setProjects(const ProjectList& projects);

    bool reportEnabled() const;
    void setReportEnabled(const bool& reportenabled);

    DataRequests requests() const;
    void setRequests(const DataRequests& requests);

    QDateTime startDate() const;
    void setStartDate(const QDateTime& startdate);

    Statistics statistics() const;

    QDateTime stopDate() const;
    void setStopDate(const QDateTime& stopdate);

private:
    QSharedDataPointer<Internal::SolutionPrivate> d;
};

QDebug OPENTRADE_EXPORT operator << (QDebug, const Solution &solution);

} // namespace OpenTrade

Q_DECLARE_SHARED(OpenTrade::Solution)

#endif // __OPENTRADE_SOLUTION_H__
