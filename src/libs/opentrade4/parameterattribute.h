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
#ifndef __OPENTRADE_PARAMETERATTRIBUTE_H__
#define __OPENTRADE_PARAMETERATTRIBUTE_H__

#include "opentrade_global.h"

#include <QSharedDataPointer>
#include <QDebug>
#include <QString>


namespace OpenTrade {

namespace Internal {
class ParameterAttributePrivate;
}

class OPENTRADE_EXPORT ParameterAttribute
{
public:

    ParameterAttribute();
    ParameterAttribute(const QString& description);
    ParameterAttribute(const QString& description, const QString& category);
    ~ParameterAttribute();

    ParameterAttribute& operator=(const ParameterAttribute &other);
    void swap(ParameterAttribute &other) { qSwap(d, other.d); }

#ifdef Q_COMPILER_RVALUE_REFS
    inline ParameterAttribute &operator=(ParameterAttribute &&other)
    { qSwap(d, other.d); return *this; }
#endif

    bool operator==(const ParameterAttribute &other) const;
    inline bool operator!=(const ParameterAttribute &other) const { return !(operator==(other)); }


    QString category() const;

    QString description() const;

private:
    QSharedDataPointer<Internal::ParameterAttributePrivate> d;
};

QDebug OPENTRADE_EXPORT operator << (QDebug, const ParameterAttribute &parameterattribute);

} // namespace OpenTrade

Q_DECLARE_SHARED(OpenTrade::ParameterAttribute)

#endif // __OPENTRADE_PARAMETERATTRIBUTE_H__
