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
#include "script.h"

#include <QSharedData>

namespace OpenTrade {

namespace Internal {

class ScriptPrivate : public QSharedData
{
public:
};

} // namespace Internal

Script::Script()
{

}

Script::~Script()
{

}

Script& Script::operator=(const Script &other)
{
    d = other.d;
    return *this;
}

bool Script::operator==(const Script &other) const
{
    if(d == other.d)
      return true;

}

void Script::addTimer(const QDateTime& dateTime, const QVariant& data)
{

}

void Script::invoke(const Action& action)
{

}

void Script::onScriptStopped(const QString& path)
{

}

void Script::onSolutionOpened(const QString& name)
{

}

void Script::onSolutionStarted()
{

}

void Script::onSolutionStarting()
{

}

void Script::onSolutionStopped()
{

}

void Script::onSolutionStopping()
{

}

void Script::onStop()
{

}

void Script::onTimer(const QDateTime& dateTime, const QVariant& data)
{

}

void Script::removeTimer(const QDateTime& dateTime)
{

}

void Script::removeTimers()
{

}

void Script::run()
{

}


} // namespace OpenTrade

QDebug operator<<(QDebug c, const OpenTrade::Script &script)
{
    c.nospace() << "Script("
                <<')';
    return c.space();
}
