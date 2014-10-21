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
#include "project.h"

#include <QSharedData>

namespace OpenTrade {

namespace Internal {

class ProjectPrivate : public QSharedData
{
public:
    bool m_enabled;
    Engine_InstrumentList m_instruments;
    QString m_name;
    ParameterSet m_parameters;
    Performance m_performance;
    Portfolio m_portfolio;
    bool m_reportEnabled;
    Statistics m_statistics;
};

} // namespace Internal

Project::~Project()
{

}

Project& Project::operator=(const Project &other)
{
    d = other.d;
    return *this;
}

bool Project::operator==(const Project &other) const
{
    if(d == other.d)
      return true;

    return d->m_enabled == other.d->m_enabled &&
           d->m_instruments == other.d->m_instruments &&
           d->m_name == other.d->m_name &&
           d->m_parameters == other.d->m_parameters &&
           d->m_performance == other.d->m_performance &&
           d->m_portfolio == other.d->m_portfolio &&
           d->m_reportEnabled == other.d->m_reportEnabled &&
           d->m_statistics == other.d->m_statistics;
}

void Project::addInstrument(const QString& symbol)
{

}

void Project::addInstrument(const Instrument& instrument)
{

}

void Project::clearInstruments()
{

}

void Project::removeInstrument(const QString& symbol)
{

}

void Project::removeInstrument(const Instrument& instrument)
{

}

bool Project::enabled() const
{
    return d->m_enabled;
}

void Project::setEnabled(bool enabled)
{
    d->m_enabled = enabled;
}

Engine_InstrumentList Project::instruments() const
{
    return d->m_instruments;
}

void Project::setInstruments(const Engine_InstrumentList& instruments)
{
    d->m_instruments = instruments;
}

QString Project::name() const
{
    return d->m_name;
}

void Project::setName(const QString& name)
{
    d->m_name = name;
}

ParameterSet Project::parameters() const
{
    return d->m_parameters;
}

void Project::setParameters(const ParameterSet& parameters)
{
    d->m_parameters = parameters;
}

Performance Project::performance() const
{
    return d->m_performance;
}

void Project::setPerformance(const Performance& performance)
{
    d->m_performance = performance;
}

Portfolio Project::portfolio() const
{
    return d->m_portfolio;
}

void Project::setPortfolio(const Portfolio& portfolio)
{
    d->m_portfolio = portfolio;
}

bool Project::reportEnabled() const
{
    return d->m_reportEnabled;
}

void Project::setReportEnabled(bool reportenabled)
{
    d->m_reportEnabled = reportenabled;
}

Statistics Project::statistics() const
{
    return d->m_statistics;
}


} // namespace OpenTrade

QDebug operator<<(QDebug c, const OpenTrade::Project &project)
{
    c.nospace() << "Project("
                << "Enabled:" << project.enabled() 
                << "Instruments:" << project.instruments() 
                << "Name:" << project.name() 
                << "Parameters:" << project.parameters() 
                << "Performance:" << project.performance() 
                << "Portfolio:" << project.portfolio() 
                << "ReportEnabled:" << project.reportEnabled() 
                << "Statistics:" << project.statistics() 
                <<')';
    return c.space();
}
