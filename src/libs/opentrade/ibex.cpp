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
#include "ibex.h"

#include <QSharedData>

namespace OpenTrade {

namespace Internal {

class IBExPrivate : public QSharedData
{
public:
    double m_displaySize;
    QString m_faGroup;
    IBFaMethod m_faMethod;
    double m_faPercentage;
    QString m_faProfile;
    bool m_hidden;
};

} // namespace Internal

IBEx::~IBEx()
{

}

IBEx& IBEx::operator=(const IBEx &other)
{
    d = other.d;
    return *this;
}

bool IBEx::operator==(const IBEx &other) const
{
    if(d == other.d)
      return true;

    return d->m_displaySize == other.d->m_displaySize &&
           d->m_faGroup == other.d->m_faGroup &&
           d->m_faMethod == other.d->m_faMethod &&
           d->m_faPercentage == other.d->m_faPercentage &&
           d->m_faProfile == other.d->m_faProfile &&
           d->m_hidden == other.d->m_hidden;
}

double IBEx::displaySize() const
{
    return d->m_displaySize;
}

void IBEx::setDisplaySize(double displaysize)
{
    d->m_displaySize = displaysize;
}

QString IBEx::faGroup() const
{
    return d->m_faGroup;
}

void IBEx::setFaGroup(const QString& fagroup)
{
    d->m_faGroup = fagroup;
}

IBFaMethod IBEx::faMethod() const
{
    return d->m_faMethod;
}

void IBEx::setFaMethod(IBFaMethod famethod)
{
    d->m_faMethod = famethod;
}

double IBEx::faPercentage() const
{
    return d->m_faPercentage;
}

void IBEx::setFaPercentage(double fapercentage)
{
    d->m_faPercentage = fapercentage;
}

QString IBEx::faProfile() const
{
    return d->m_faProfile;
}

void IBEx::setFaProfile(const QString& faprofile)
{
    d->m_faProfile = faprofile;
}

bool IBEx::hidden() const
{
    return d->m_hidden;
}

void IBEx::setHidden(const bool& hidden)
{
    d->m_hidden = hidden;
}


} // namespace OpenTrade

QDebug operator<<(QDebug c, const OpenTrade::IBEx &ibex)
{
    c.nospace() << "IBEx("
                << "DisplaySize:" << ibex.displaySize() 
                << "FaGroup:" << ibex.faGroup() 
                << "FaMethod:" << ibex.faMethod() 
                << "FaPercentage:" << ibex.faPercentage() 
                << "FaProfile:" << ibex.faProfile() 
                << "Hidden:" << ibex.hidden() 
                <<')';
    return c.space();
}
