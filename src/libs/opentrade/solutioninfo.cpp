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
#include "solutioninfo.h"

#include <QSharedData>

namespace OpenTrade {

namespace Internal {

class SolutionInfoPrivate : public QSharedData
{
public:
    QString m_name;
    ProjectInfoList m_projects;
    FileInfo m_scenarioFile;
    FileInfo m_solutionFile;
};

} // namespace Internal

SolutionInfo::~SolutionInfo()
{

}

SolutionInfo& SolutionInfo::operator=(const SolutionInfo &other)
{
    d = other.d;
    return *this;
}

bool SolutionInfo::operator==(const SolutionInfo &other) const
{
    if(d == other.d)
      return true;

    return d->m_name == other.d->m_name &&
           d->m_projects == other.d->m_projects &&
           d->m_scenarioFile == other.d->m_scenarioFile &&
           d->m_solutionFile == other.d->m_solutionFile;
}

QString SolutionInfo::name() const
{
    return d->m_name;
}

void SolutionInfo::setName(const QString& name)
{
    d->m_name = name;
}

ProjectInfoList SolutionInfo::projects() const
{
    return d->m_projects;
}

FileInfo SolutionInfo::scenarioFile() const
{
    return d->m_scenarioFile;
}

void SolutionInfo::setScenarioFile(const FileInfo& scenariofile)
{
    d->m_scenarioFile = scenariofile;
}

FileInfo SolutionInfo::solutionFile() const
{
    return d->m_solutionFile;
}

void SolutionInfo::setSolutionFile(const FileInfo& solutionfile)
{
    d->m_solutionFile = solutionfile;
}


} // namespace OpenTrade

QDebug operator<<(QDebug c, const OpenTrade::SolutionInfo &solutioninfo)
{
    c.nospace() << "SolutionInfo("
                << "Name:" << solutioninfo.name() 
                << "Projects:" << solutioninfo.projects() 
                << "ScenarioFile:" << solutioninfo.scenarioFile() 
                << "SolutionFile:" << solutioninfo.solutionFile() 
                <<')';
    return c.space();
}
