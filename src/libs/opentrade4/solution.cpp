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
#include "solution.h"

#include <QSharedData>

namespace OpenTrade {

namespace Internal {

class SolutionPrivate : public QSharedData
{
public:
    double m_cash;
    QString m_name;
    Performance m_performance;
    Portfolio m_portfolio;
    ProjectList m_projects;
    bool m_reportEnabled;
    DataRequests m_requests;
    QDateTime m_startDate;
    Statistics m_statistics;
    QDateTime m_stopDate;
};

} // namespace Internal

Solution::~Solution()
{

}

Solution& Solution::operator=(const Solution &other)
{
    d = other.d;
    return *this;
}

bool Solution::operator==(const Solution &other) const
{
    if(d == other.d)
      return true;

    return d->m_cash == other.d->m_cash &&
           d->m_name == other.d->m_name &&
           d->m_performance == other.d->m_performance &&
           d->m_portfolio == other.d->m_portfolio &&
           d->m_projects == other.d->m_projects &&
           d->m_reportEnabled == other.d->m_reportEnabled &&
           d->m_requests == other.d->m_requests &&
           d->m_startDate == other.d->m_startDate &&
           d->m_statistics == other.d->m_statistics &&
           d->m_stopDate == other.d->m_stopDate;
}

double Solution::cash() const
{
    return d->m_cash;
}

void Solution::setCash(double cash)
{
    d->m_cash = cash;
}

QString Solution::name() const
{
    return d->m_name;
}

void Solution::setName(const QString& name)
{
    d->m_name = name;
}

Performance Solution::performance() const
{
    return d->m_performance;
}

void Solution::setPerformance(const Performance& performance)
{
    d->m_performance = performance;
}

Portfolio Solution::portfolio() const
{
    return d->m_portfolio;
}

void Solution::setPortfolio(const Portfolio& portfolio)
{
    d->m_portfolio = portfolio;
}

ProjectList Solution::projects() const
{
    return d->m_projects;
}

void Solution::setProjects(const ProjectList& projects)
{
    d->m_projects = projects;
}

bool Solution::reportEnabled() const
{
    return d->m_reportEnabled;
}

void Solution::setReportEnabled(bool reportenabled)
{
    d->m_reportEnabled = reportenabled;
}

DataRequests Solution::requests() const
{
    return d->m_requests;
}

void Solution::setRequests(const DataRequests& requests)
{
    d->m_requests = requests;
}

QDateTime Solution::startDate() const
{
    return d->m_startDate;
}

void Solution::setStartDate(const QDateTime& startdate)
{
    d->m_startDate = startdate;
}

Statistics Solution::statistics() const
{
    return d->m_statistics;
}

QDateTime Solution::stopDate() const
{
    return d->m_stopDate;
}

void Solution::setStopDate(const QDateTime& stopdate)
{
    d->m_stopDate = stopdate;
}


} // namespace OpenTrade

QDebug operator<<(QDebug c, const OpenTrade::Solution &solution)
{
    c.nospace() << "Solution("
                << "Cash:" << solution.cash() 
                << "Name:" << solution.name() 
                << "Performance:" << solution.performance() 
                << "Portfolio:" << solution.portfolio() 
                << "Projects:" << solution.projects() 
                << "ReportEnabled:" << solution.reportEnabled() 
                << "Requests:" << solution.requests() 
                << "StartDate:" << solution.startDate() 
                << "Statistics:" << solution.statistics() 
                << "StopDate:" << solution.stopDate() 
                <<')';
    return c.space();
}
