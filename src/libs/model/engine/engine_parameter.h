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
#ifndef __OPENTRADE_ENGINE_PARAMETER_H__
#define __OPENTRADE_ENGINE_PARAMETER_H__

#include "opentrade_global.h"

#include <QSharedDataPointer>
#include <QDebug>
#include <QString>
#include <QVariant>


namespace OpenTrade {

namespace Internal {
class Engine_ParameterPrivate;
}

class OPENTRADE_EXPORT Engine_Parameter
{
public:

    ~Engine_Parameter();

    Engine_Parameter& operator=(const Engine_Parameter &other);
    void swap(Engine_Parameter &other) { qSwap(d, other.d); }

#ifdef Q_COMPILER_RVALUE_REFS
    inline Engine_Parameter &operator=(Engine_Parameter &&other)
    { qSwap(d, other.d); return *this; }
#endif

    bool operator==(const Engine_Parameter &other) const;
    inline bool operator!=(const Engine_Parameter &other) const { return !(operator==(other)); }

    void parameter(const QString& name, const QVariant& value, const Type& type);

    QString name() const;
    void setName(const QString& name);

    Type type() const;
    void setType(const Type& type);

    QVariant value() const;
    void setValue(const QVariant& value);

private:
    QSharedDataPointer<Internal::Engine_ParameterPrivate> d;
};

QDebug OPENTRADE_EXPORT operator << (QDebug, const Engine_Parameter &engine_parameter);

} // namespace OpenTrade

Q_DECLARE_SHARED(OpenTrade::Engine_Parameter)

#endif // __OPENTRADE_ENGINE_PARAMETER_H__
