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
#ifndef __OPENTRADE_PROVIDERPROPERTY_H__
#define __OPENTRADE_PROVIDERPROPERTY_H__

#include "opentrade_global.h"

#include <QSharedDataPointer>
#include <QDebug>
#include <QString>
#include <QVariant>


namespace OpenTrade {

namespace Internal {
class ProviderPropertyPrivate;
}

class OPENTRADE_EXPORT ProviderProperty
{
public:

    ~ProviderProperty();

    ProviderProperty& operator=(const ProviderProperty &other);
    void swap(ProviderProperty &other) { qSwap(d, other.d); }

#ifdef Q_COMPILER_RVALUE_REFS
    inline ProviderProperty &operator=(ProviderProperty &&other)
    { qSwap(d, other.d); return *this; }
#endif

    bool operator==(const ProviderProperty &other) const;
    inline bool operator!=(const ProviderProperty &other) const { return !(operator==(other)); }


    QString name() const;

    Type type() const;

    QVariant value() const;
    void setValue(const QVariant& value);

private:
    QSharedDataPointer<Internal::ProviderPropertyPrivate> d;
};

QDebug OPENTRADE_EXPORT operator << (QDebug, const ProviderProperty &providerproperty);

} // namespace OpenTrade

Q_DECLARE_SHARED(OpenTrade::ProviderProperty)

#endif // __OPENTRADE_PROVIDERPROPERTY_H__
