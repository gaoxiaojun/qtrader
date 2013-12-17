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
#ifndef __OPENTRADE_INSTRUMENTMANAGER_H__
#define __OPENTRADE_INSTRUMENTMANAGER_H__

#include "opentrade_global.h"
#include "instrument.h"

#include <QSharedDataPointer>
#include <QDebug>
#include <QString>


namespace OpenTrade {

namespace Internal {
class InstrumentManagerPrivate;
}

class OPENTRADE_EXPORT InstrumentManager
{
public:

    ~InstrumentManager();

    InstrumentManager& operator=(const InstrumentManager &other);
    void swap(InstrumentManager &other) { qSwap(d, other.d); }

#ifdef Q_COMPILER_RVALUE_REFS
    inline InstrumentManager &operator=(InstrumentManager &&other)
    { qSwap(d, other.d); return *this; }
#endif

    bool operator==(const InstrumentManager &other) const;
    inline bool operator!=(const InstrumentManager &other) const { return !(operator==(other)); }

    void remove(const QString& symbol);
    void remove(const Instrument& instrument);

    static instrumentList() const;

private:
    QSharedDataPointer<Internal::InstrumentManagerPrivate> d;
};

QDebug OPENTRADE_EXPORT operator << (QDebug, const InstrumentManager &instrumentmanager);

} // namespace OpenTrade

Q_DECLARE_SHARED(OpenTrade::InstrumentManager)

#endif // __OPENTRADE_INSTRUMENTMANAGER_H__
