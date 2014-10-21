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
#ifndef __OPENTRADE_SCRIPTSETTINGS_H__
#define __OPENTRADE_SCRIPTSETTINGS_H__

#include "opentrade_global.h"

#include <QSharedDataPointer>
#include <QDebug>
#include <QString>
#include <QVariant>


namespace OpenTrade {

namespace Internal {
class ScriptSettingsPrivate;
}

class OPENTRADE_EXPORT ScriptSettings
{
public:

    ~ScriptSettings();

    ScriptSettings& operator=(const ScriptSettings &other);
    void swap(ScriptSettings &other) { qSwap(d, other.d); }

#ifdef Q_COMPILER_RVALUE_REFS
    inline ScriptSettings &operator=(ScriptSettings &&other)
    { qSwap(d, other.d); return *this; }
#endif

    bool operator==(const ScriptSettings &other) const;
    inline bool operator!=(const ScriptSettings &other) const { return !(operator==(other)); }

    void add(const QString& name, const QVariant& data);
    void remove(const QString& name);

    int count() const;

private:
    QSharedDataPointer<Internal::ScriptSettingsPrivate> d;
};

QDebug OPENTRADE_EXPORT operator << (QDebug, const ScriptSettings &scriptsettings);

} // namespace OpenTrade

Q_DECLARE_SHARED(OpenTrade::ScriptSettings)

#endif // __OPENTRADE_SCRIPTSETTINGS_H__
