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
#include "scriptsettings.h"

#include <QSharedData>

namespace OpenTrade {

namespace Internal {

class ScriptSettingsPrivate : public QSharedData
{
public:
    int m_count;
};

} // namespace Internal

ScriptSettings::~ScriptSettings()
{

}

ScriptSettings& ScriptSettings::operator=(const ScriptSettings &other)
{
    d = other.d;
    return *this;
}

bool ScriptSettings::operator==(const ScriptSettings &other) const
{
    if(d == other.d)
      return true;

    return d->m_count == other.d->m_count;
}

void ScriptSettings::add(const QString& name, const QVariant& data)
{

}

void ScriptSettings::remove(const QString& name)
{

}

int ScriptSettings::count() const
{
    return d->m_count;
}


} // namespace OpenTrade

QDebug operator<<(QDebug c, const OpenTrade::ScriptSettings &scriptsettings)
{
    c.nospace() << "ScriptSettings("
                << "Count:" << scriptsettings.count() 
                <<')';
    return c.space();
}
