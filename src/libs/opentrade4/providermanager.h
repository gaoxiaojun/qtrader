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
#ifndef __OPENTRADE_PROVIDERMANAGER_H__
#define __OPENTRADE_PROVIDERMANAGER_H__

#include "opentrade_global.h"

#include <QSharedDataPointer>
#include <QDebug>


namespace OpenTrade {

namespace Internal {
class ProviderManagerPrivate;
}

class OPENTRADE_EXPORT ProviderManager
{
public:

    ~ProviderManager();

    ProviderManager& operator=(const ProviderManager &other);
    void swap(ProviderManager &other) { qSwap(d, other.d); }

#ifdef Q_COMPILER_RVALUE_REFS
    inline ProviderManager &operator=(ProviderManager &&other)
    { qSwap(d, other.d); return *this; }
#endif

    bool operator==(const ProviderManager &other) const;
    inline bool operator!=(const ProviderManager &other) const { return !(operator==(other)); }


    static providerList() const;
    void setProviderList(const static& providerlist);

private:
    QSharedDataPointer<Internal::ProviderManagerPrivate> d;
};

QDebug OPENTRADE_EXPORT operator << (QDebug, const ProviderManager &providermanager);

} // namespace OpenTrade

Q_DECLARE_SHARED(OpenTrade::ProviderManager)

#endif // __OPENTRADE_PROVIDERMANAGER_H__
