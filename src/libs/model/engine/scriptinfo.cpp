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
#include "scriptinfo.h"

#include <QSharedData>

namespace OpenTrade {

namespace Internal {

class ScriptInfoPrivate : public QSharedData
{
public:
    QString m_path;
    ScriptSettings m_settings;
};

} // namespace Internal

ScriptInfo::ScriptInfo(const QString& path)
{

}

ScriptInfo::~ScriptInfo()
{

}

ScriptInfo& ScriptInfo::operator=(const ScriptInfo &other)
{
    d = other.d;
    return *this;
}

bool ScriptInfo::operator==(const ScriptInfo &other) const
{
    if(d == other.d)
      return true;

    return d->m_path == other.d->m_path &&
           d->m_settings == other.d->m_settings;
}

QString ScriptInfo::path() const
{
    return d->m_path;
}

void ScriptInfo::setPath(const QString& path)
{
    d->m_path = path;
}

ScriptSettings ScriptInfo::settings() const
{
    return d->m_settings;
}

void ScriptInfo::setSettings(const ScriptSettings& settings)
{
    d->m_settings = settings;
}


} // namespace OpenTrade

QDebug operator<<(QDebug c, const OpenTrade::ScriptInfo &scriptinfo)
{
    c.nospace() << "ScriptInfo("
                << "Path:" << scriptinfo.path() 
                << "Settings:" << scriptinfo.settings() 
                <<')';
    return c.space();
}
