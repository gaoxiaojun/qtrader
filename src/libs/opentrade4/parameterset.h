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
#ifndef __OPENTRADE_PARAMETERSET_H__
#define __OPENTRADE_PARAMETERSET_H__

#include "opentrade_global.h"
#include "engine_parameter.h"

#include <QSharedDataPointer>
#include <QDebug>
#include <QString>


namespace OpenTrade {

namespace Internal {
class ParameterSetPrivate;
}

class OPENTRADE_EXPORT ParameterSet
{
public:

    ~ParameterSet();

    ParameterSet& operator=(const ParameterSet &other);
    void swap(ParameterSet &other) { qSwap(d, other.d); }

#ifdef Q_COMPILER_RVALUE_REFS
    inline ParameterSet &operator=(ParameterSet &&other)
    { qSwap(d, other.d); return *this; }
#endif

    bool operator==(const ParameterSet &other) const;
    inline bool operator!=(const ParameterSet &other) const { return !(operator==(other)); }

    bool contains(const QString& name);
    bool tryGetValue(const QString& name, const Engine_Parameter& parameter);

    int count() const;

private:
    QSharedDataPointer<Internal::ParameterSetPrivate> d;
};

QDebug OPENTRADE_EXPORT operator << (QDebug, const ParameterSet &parameterset);

} // namespace OpenTrade

Q_DECLARE_SHARED(OpenTrade::ParameterSet)

#endif // __OPENTRADE_PARAMETERSET_H__
