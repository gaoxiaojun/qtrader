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
#ifndef __OPENTRADE_BARREQUEST_H__
#define __OPENTRADE_BARREQUEST_H__

#include "opentrade_global.h"

#include <QSharedDataPointer>
#include <QDebug>


namespace OpenTrade {

namespace Internal {
class BarRequestPrivate;
}

class OPENTRADE_EXPORT BarRequest
{
public:

    BarRequest(BarType barType, long barSize, const bool& isBarFactoryRequest);
    ~BarRequest();

    BarRequest& operator=(const BarRequest &other);
    void swap(BarRequest &other) { qSwap(d, other.d); }

#ifdef Q_COMPILER_RVALUE_REFS
    inline BarRequest &operator=(BarRequest &&other)
    { qSwap(d, other.d); return *this; }
#endif

    bool operator==(const BarRequest &other) const;
    inline bool operator!=(const BarRequest &other) const { return !(operator==(other)); }


    long barSize() const;

    BarType barType() const;

    bool isBarFactoryRequest() const;
    void setIsBarFactoryRequest(const bool& isbarfactoryrequest);

private:
    QSharedDataPointer<Internal::BarRequestPrivate> d;
};

QDebug OPENTRADE_EXPORT operator << (QDebug, const BarRequest &barrequest);

} // namespace OpenTrade

Q_DECLARE_SHARED(OpenTrade::BarRequest)

#endif // __OPENTRADE_BARREQUEST_H__
