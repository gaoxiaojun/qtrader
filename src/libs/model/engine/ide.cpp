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
#include "ide.h"

#include <QSharedData>

namespace OpenTrade {

namespace Internal {

class IDEPrivate : public QSharedData
{
public:
    static m_strategyMode;
    static m_directoryInfo;
    static m_scenario;
    static m_directoryInfo;
    static m_solution;
    static m_solutionInfo;
    static m_directoryInfo;
};

} // namespace Internal

IDE::~IDE()
{

}

IDE& IDE::operator=(const IDE &other)
{
    d = other.d;
    return *this;
}

bool IDE::operator==(const IDE &other) const
{
    if(d == other.d)
      return true;

    return d->m_strategyMode == other.d->m_strategyMode &&
           d->m_directoryInfo == other.d->m_directoryInfo &&
           d->m_scenario == other.d->m_scenario &&
           d->m_directoryInfo == other.d->m_directoryInfo &&
           d->m_solution == other.d->m_solution &&
           d->m_solutionInfo == other.d->m_solutionInfo &&
           d->m_directoryInfo == other.d->m_directoryInfo;
}

void IDE::buildSolution()
{

}

void IDE::closeSolution()
{

}

bool IDE::openSolution(const QString& name)
{

}

void IDE::startScript(const ScriptInfo& scriptInfo)
{

}

void IDE::startSolution()
{

}

void IDE::stopScript(const ScriptInfo& scriptInfo)
{

}

void IDE::stopSolution()
{

}

static IDE::strategyMode() const
{
    return d->m_strategyMode;
}

void IDE::setStrategyMode(const static& strategymode)
{
    d->m_strategyMode = strategymode;
}

static IDE::directoryInfo() const
{
    return d->m_directoryInfo;
}

void IDE::setDirectoryInfo(const static& directoryinfo)
{
    d->m_directoryInfo = directoryinfo;
}

static IDE::scenario() const
{
    return d->m_scenario;
}

static IDE::directoryInfo() const
{
    return d->m_directoryInfo;
}

void IDE::setDirectoryInfo(const static& directoryinfo)
{
    d->m_directoryInfo = directoryinfo;
}

static IDE::solution() const
{
    return d->m_solution;
}

void IDE::setSolution(const static& solution)
{
    d->m_solution = solution;
}

static IDE::solutionInfo() const
{
    return d->m_solutionInfo;
}

static IDE::directoryInfo() const
{
    return d->m_directoryInfo;
}

void IDE::setDirectoryInfo(const static& directoryinfo)
{
    d->m_directoryInfo = directoryinfo;
}


} // namespace OpenTrade

QDebug operator<<(QDebug c, const OpenTrade::IDE &ide)
{
    c.nospace() << "IDE("
                << "StrategyMode:" << ide.strategyMode() 
                << "DirectoryInfo:" << ide.directoryInfo() 
                << "Scenario:" << ide.scenario() 
                << "DirectoryInfo:" << ide.directoryInfo() 
                << "Solution:" << ide.solution() 
                << "SolutionInfo:" << ide.solutionInfo() 
                << "DirectoryInfo:" << ide.directoryInfo() 
                <<')';
    return c.space();
}
