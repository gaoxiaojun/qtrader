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
#ifndef __OPENTRADE_PROVIDERERROR_H__
#define __OPENTRADE_PROVIDERERROR_H__

#include "opentrade_global.h"

#include <QSharedDataPointer>
#include <QDebug>
#include <QDateTime>
#include <QString>


namespace OpenTrade {

namespace Internal {
class ProviderErrorPrivate;
}

class OPENTRADE_EXPORT ProviderError
{
public:

    ~ProviderError();

    ProviderError& operator=(const ProviderError &other);
    void swap(ProviderError &other) { qSwap(d, other.d); }

#ifdef Q_COMPILER_RVALUE_REFS
    inline ProviderError &operator=(ProviderError &&other)
    { qSwap(d, other.d); return *this; }
#endif

    bool operator==(const ProviderError &other) const;
    inline bool operator!=(const ProviderError &other) const { return !(operator==(other)); }


    int code() const;

    QDateTime dateTime() const;

    int id() const;

    QString message() const;

    QString provider() const;

private:
    QSharedDataPointer<Internal::ProviderErrorPrivate> d;
};

QDebug OPENTRADE_EXPORT operator << (QDebug, const ProviderError &providererror);

} // namespace OpenTrade

Q_DECLARE_SHARED(OpenTrade::ProviderError)

#endif // __OPENTRADE_PROVIDERERROR_H__
