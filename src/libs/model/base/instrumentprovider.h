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
#ifndef __OPENTRADE_INSTRUMENTPROVIDER_H__
#define __OPENTRADE_INSTRUMENTPROVIDER_H__

#include "opentrade_global.h"
#include "providerpropertylist.h"

#include <QSharedDataPointer>
#include <QDebug>
#include <QString>


namespace OpenTrade {

namespace Internal {
class InstrumentProviderPrivate;
}

class OPENTRADE_EXPORT InstrumentProvider
{
public:

    ~InstrumentProvider();

    InstrumentProvider& operator=(const InstrumentProvider &other);
    void swap(InstrumentProvider &other) { qSwap(d, other.d); }

#ifdef Q_COMPILER_RVALUE_REFS
    inline InstrumentProvider &operator=(InstrumentProvider &&other)
    { qSwap(d, other.d); return *this; }
#endif

    bool operator==(const InstrumentProvider &other) const;
    inline bool operator!=(const InstrumentProvider &other) const { return !(operator==(other)); }

    void connect();
    void disconnect();

    int id() const;

    bool isConnected() const;

    bool isExecutionProvider() const;

    bool isHistoricalDataProvider() const;

    bool isInstrumentProvider() const;

    bool isMarketDataProvider() const;

    QString name() const;

    ProviderPropertyList properties() const;
    void setProperties(const ProviderPropertyList& properties);

private:
    QSharedDataPointer<Internal::InstrumentProviderPrivate> d;
};

QDebug OPENTRADE_EXPORT operator << (QDebug, const InstrumentProvider &instrumentprovider);

} // namespace OpenTrade

Q_DECLARE_SHARED(OpenTrade::InstrumentProvider)

#endif // __OPENTRADE_INSTRUMENTPROVIDER_H__
