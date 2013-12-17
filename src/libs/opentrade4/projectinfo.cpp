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
#include "projectinfo.h"

#include <QSharedData>

namespace OpenTrade {

namespace Internal {

class ProjectInfoPrivate : public QSharedData
{
public:
    FileInfo m_codeFile;
    QString m_name;
    FileInfo m_projectFile;
};

} // namespace Internal

ProjectInfo::~ProjectInfo()
{

}

ProjectInfo& ProjectInfo::operator=(const ProjectInfo &other)
{
    d = other.d;
    return *this;
}

bool ProjectInfo::operator==(const ProjectInfo &other) const
{
    if(d == other.d)
      return true;

    return d->m_codeFile == other.d->m_codeFile &&
           d->m_name == other.d->m_name &&
           d->m_projectFile == other.d->m_projectFile;
}

FileInfo ProjectInfo::codeFile() const
{
    return d->m_codeFile;
}

void ProjectInfo::setCodeFile(const FileInfo& codefile)
{
    d->m_codeFile = codefile;
}

QString ProjectInfo::name() const
{
    return d->m_name;
}

void ProjectInfo::setName(const QString& name)
{
    d->m_name = name;
}

FileInfo ProjectInfo::projectFile() const
{
    return d->m_projectFile;
}

void ProjectInfo::setProjectFile(const FileInfo& projectfile)
{
    d->m_projectFile = projectfile;
}


} // namespace OpenTrade

QDebug operator<<(QDebug c, const OpenTrade::ProjectInfo &projectinfo)
{
    c.nospace() << "ProjectInfo("
                << "CodeFile:" << projectinfo.codeFile() 
                << "Name:" << projectinfo.name() 
                << "ProjectFile:" << projectinfo.projectFile() 
                <<')';
    return c.space();
}
