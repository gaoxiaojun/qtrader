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
#ifndef __OPENTRADE_PROJECT_H__
#define __OPENTRADE_PROJECT_H__

#include "opentrade_global.h"
#include "instrument.h"
#include "engine_instrumentlist.h"
#include "parameterset.h"
#include "performance.h"
#include "portfolio.h"
#include "statistics.h"

#include <QSharedDataPointer>
#include <QDebug>
#include <QString>


namespace OpenTrade {

namespace Internal {
class ProjectPrivate;
}

class OPENTRADE_EXPORT Project
{
public:

    ~Project();

    Project& operator=(const Project &other);
    void swap(Project &other) { qSwap(d, other.d); }

#ifdef Q_COMPILER_RVALUE_REFS
    inline Project &operator=(Project &&other)
    { qSwap(d, other.d); return *this; }
#endif

    bool operator==(const Project &other) const;
    inline bool operator!=(const Project &other) const { return !(operator==(other)); }

    void addInstrument(const QString& symbol);
    void addInstrument(const Instrument& instrument);
    void clearInstruments();
    void removeInstrument(const QString& symbol);
    void removeInstrument(const Instrument& instrument);

    bool enabled() const;
    void setEnabled(const bool& enabled);

    Engine_InstrumentList instruments() const;
    void setInstruments(const Engine_InstrumentList& instruments);

    QString name() const;
    void setName(const QString& name);

    ParameterSet parameters() const;
    void setParameters(const ParameterSet& parameters);

    Performance performance() const;
    void setPerformance(const Performance& performance);

    Portfolio portfolio() const;
    void setPortfolio(const Portfolio& portfolio);

    bool reportEnabled() const;
    void setReportEnabled(const bool& reportenabled);

    Statistics statistics() const;

private:
    QSharedDataPointer<Internal::ProjectPrivate> d;
};

QDebug OPENTRADE_EXPORT operator << (QDebug, const Project &project);

} // namespace OpenTrade

Q_DECLARE_SHARED(OpenTrade::Project)

#endif // __OPENTRADE_PROJECT_H__
