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
#ifndef __OPENTRADE_SCRIPTINFO_H__
#define __OPENTRADE_SCRIPTINFO_H__

#include "opentrade_global.h"
#include "scriptsettings.h"

#include <QSharedDataPointer>
#include <QDebug>
#include <QString>


namespace OpenTrade {

namespace Internal {
class ScriptInfoPrivate;
}

class OPENTRADE_EXPORT ScriptInfo
{
public:

    ScriptInfo(const QString& path);
    ~ScriptInfo();

    ScriptInfo& operator=(const ScriptInfo &other);
    void swap(ScriptInfo &other) { qSwap(d, other.d); }

#ifdef Q_COMPILER_RVALUE_REFS
    inline ScriptInfo &operator=(ScriptInfo &&other)
    { qSwap(d, other.d); return *this; }
#endif

    bool operator==(const ScriptInfo &other) const;
    inline bool operator!=(const ScriptInfo &other) const { return !(operator==(other)); }


    QString path() const;
    void setPath(const QString& path);

    ScriptSettings settings() const;
    void setSettings(const ScriptSettings& settings);

private:
    QSharedDataPointer<Internal::ScriptInfoPrivate> d;
};

QDebug OPENTRADE_EXPORT operator << (QDebug, const ScriptInfo &scriptinfo);

} // namespace OpenTrade

Q_DECLARE_SHARED(OpenTrade::ScriptInfo)

#endif // __OPENTRADE_SCRIPTINFO_H__
