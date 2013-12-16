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
#ifndef __OPENTRADE_ENGINE_INSTRUMENTLIST_H__
#define __OPENTRADE_ENGINE_INSTRUMENTLIST_H__

#include "opentrade_global.h"
#include "instrument.h"

#include <QSharedDataPointer>
#include <QDebug>
#include <QString>


namespace OpenTrade {

namespace Internal {
class Engine_InstrumentListPrivate;
}

class OPENTRADE_EXPORT Engine_InstrumentList
{
public:

    ~Engine_InstrumentList();

    Engine_InstrumentList& operator=(const Engine_InstrumentList &other);
    void swap(Engine_InstrumentList &other) { qSwap(d, other.d); }

#ifdef Q_COMPILER_RVALUE_REFS
    inline Engine_InstrumentList &operator=(Engine_InstrumentList &&other)
    { qSwap(d, other.d); return *this; }
#endif

    bool operator==(const Engine_InstrumentList &other) const;
    inline bool operator!=(const Engine_InstrumentList &other) const { return !(operator==(other)); }

    void add(const QString& symbol);
    void add(const Instrument& instrument);
    void clear();
    bool contains(const QString& name);
    void remove(const QString& symbol);
    void remove(const Instrument& instrument);
    bool tryGetValue(const QString& name, const Instrument& instrument);

    int count() const;

private:
    QSharedDataPointer<Internal::Engine_InstrumentListPrivate> d;
};

QDebug OPENTRADE_EXPORT operator << (QDebug, const Engine_InstrumentList &engine_instrumentlist);

} // namespace OpenTrade

Q_DECLARE_SHARED(OpenTrade::Engine_InstrumentList)

#endif // __OPENTRADE_ENGINE_INSTRUMENTLIST_H__
