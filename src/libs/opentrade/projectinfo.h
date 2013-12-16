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
#ifndef __OPENTRADE_PROJECTINFO_H__
#define __OPENTRADE_PROJECTINFO_H__

#include "opentrade_global.h"

#include <QSharedDataPointer>
#include <QDebug>
#include <QString>


namespace OpenTrade {

namespace Internal {
class ProjectInfoPrivate;
}

class OPENTRADE_EXPORT ProjectInfo
{
public:

    ~ProjectInfo();

    ProjectInfo& operator=(const ProjectInfo &other);
    void swap(ProjectInfo &other) { qSwap(d, other.d); }

#ifdef Q_COMPILER_RVALUE_REFS
    inline ProjectInfo &operator=(ProjectInfo &&other)
    { qSwap(d, other.d); return *this; }
#endif

    bool operator==(const ProjectInfo &other) const;
    inline bool operator!=(const ProjectInfo &other) const { return !(operator==(other)); }


    FileInfo codeFile() const;
    void setCodeFile(const FileInfo& codefile);

    QString name() const;
    void setName(const QString& name);

    FileInfo projectFile() const;
    void setProjectFile(const FileInfo& projectfile);

private:
    QSharedDataPointer<Internal::ProjectInfoPrivate> d;
};

QDebug OPENTRADE_EXPORT operator << (QDebug, const ProjectInfo &projectinfo);

} // namespace OpenTrade

Q_DECLARE_SHARED(OpenTrade::ProjectInfo)

#endif // __OPENTRADE_PROJECTINFO_H__
