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
#include "altidgroup.h"

#include <QSharedData>

namespace OpenTrade {

namespace Internal {

class AltIDGroupPrivate : public QSharedData
{
public:
    QString m_altExchange;
    QString m_altSource;
    QString m_altSymbol;
};

} // namespace Internal

AltIDGroup::~AltIDGroup()
{

}

AltIDGroup& AltIDGroup::operator=(const AltIDGroup &other)
{
    d = other.d;
    return *this;
}

bool AltIDGroup::operator==(const AltIDGroup &other) const
{
    if(d == other.d)
      return true;

    return d->m_altExchange == other.d->m_altExchange &&
           d->m_altSource == other.d->m_altSource &&
           d->m_altSymbol == other.d->m_altSymbol;
}

QString AltIDGroup::altExchange() const
{
    return d->m_altExchange;
}

void AltIDGroup::setAltExchange(const QString& altexchange)
{
    d->m_altExchange = altexchange;
}

QString AltIDGroup::altSource() const
{
    return d->m_altSource;
}

void AltIDGroup::setAltSource(const QString& altsource)
{
    d->m_altSource = altsource;
}

QString AltIDGroup::altSymbol() const
{
    return d->m_altSymbol;
}

void AltIDGroup::setAltSymbol(const QString& altsymbol)
{
    d->m_altSymbol = altsymbol;
}


} // namespace OpenTrade

QDebug operator<<(QDebug c, const OpenTrade::AltIDGroup &altidgroup)
{
    c.nospace() << "AltIDGroup("
                << "AltExchange:" << altidgroup.altExchange() 
                << "AltSource:" << altidgroup.altSource() 
                << "AltSymbol:" << altidgroup.altSymbol() 
                <<')';
    return c.space();
}
