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
#ifndef __OPENTRADE_IDE_H__
#define __OPENTRADE_IDE_H__

#include "opentrade_global.h"
#include "scriptinfo.h"

#include <QSharedDataPointer>
#include <QDebug>
#include <QString>


namespace OpenTrade {

namespace Internal {
class IDEPrivate;
}

class OPENTRADE_EXPORT IDE
{
public:

    ~IDE();

    IDE& operator=(const IDE &other);
    void swap(IDE &other) { qSwap(d, other.d); }

#ifdef Q_COMPILER_RVALUE_REFS
    inline IDE &operator=(IDE &&other)
    { qSwap(d, other.d); return *this; }
#endif

    bool operator==(const IDE &other) const;
    inline bool operator!=(const IDE &other) const { return !(operator==(other)); }

    void buildSolution();
    void closeSolution();
    bool openSolution(const QString& name);
    void startScript(const ScriptInfo& scriptInfo);
    void startSolution();
    void stopScript(const ScriptInfo& scriptInfo);
    void stopSolution();

    static strategyMode() const;
    void setStrategyMode(const static& strategymode);

    static directoryInfo() const;
    void setDirectoryInfo(const static& directoryinfo);

    static scenario() const;

    static directoryInfo() const;
    void setDirectoryInfo(const static& directoryinfo);

    static solution() const;
    void setSolution(const static& solution);

    static solutionInfo() const;

    static directoryInfo() const;
    void setDirectoryInfo(const static& directoryinfo);

private:
    QSharedDataPointer<Internal::IDEPrivate> d;
};

QDebug OPENTRADE_EXPORT operator << (QDebug, const IDE &ide);

} // namespace OpenTrade

Q_DECLARE_SHARED(OpenTrade::IDE)

#endif // __OPENTRADE_IDE_H__
