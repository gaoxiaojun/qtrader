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
#ifndef __OPENTRADE_SCRIPT_H__
#define __OPENTRADE_SCRIPT_H__

#include "opentrade_global.h"

#include <QSharedDataPointer>
#include <QDebug>
#include <QDateTime>
#include <QVariant>
#include <QString>


namespace OpenTrade {

namespace Internal {
class ScriptPrivate;
}

class OPENTRADE_EXPORT Script
{
public:

    Script();
    ~Script();

    Script& operator=(const Script &other);
    void swap(Script &other) { qSwap(d, other.d); }

#ifdef Q_COMPILER_RVALUE_REFS
    inline Script &operator=(Script &&other)
    { qSwap(d, other.d); return *this; }
#endif

    bool operator==(const Script &other) const;
    inline bool operator!=(const Script &other) const { return !(operator==(other)); }

    void addTimer(const QDateTime& dateTime, const QVariant& data);
    void invoke(const Action& action);
    void onScriptStopped(const QString& path);
    void onSolutionOpened(const QString& name);
    void onSolutionStarted();
    void onSolutionStarting();
    void onSolutionStopped();
    void onSolutionStopping();
    void onStop();
    void onTimer(const QDateTime& dateTime, const QVariant& data);
    void removeTimer(const QDateTime& dateTime);
    void removeTimers();
    void run();

private:
    QSharedDataPointer<Internal::ScriptPrivate> d;
};

QDebug OPENTRADE_EXPORT operator << (QDebug, const Script &script);

} // namespace OpenTrade

Q_DECLARE_SHARED(OpenTrade::Script)

#endif // __OPENTRADE_SCRIPT_H__
