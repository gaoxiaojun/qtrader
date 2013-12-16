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
#include "appearance.h"

#include <QSharedData>

namespace OpenTrade {

namespace Internal {

class AppearancePrivate : public QSharedData
{
public:
    static m_font;
};

} // namespace Internal

Appearance::~Appearance()
{

}

Appearance& Appearance::operator=(const Appearance &other)
{
    d = other.d;
    return *this;
}

bool Appearance::operator==(const Appearance &other) const
{
    if(d == other.d)
    return true;

    return d->m_font == other.d->m_font;
}

static Appearance::font() const
{
    return d->m_font;
}

void Appearance::setFont(const static& font)
{
    d->m_font = font;
}


} // namespace OpenTrade

QDebug operator<<(QDebug c, const OpenTrade::Appearance &appearance)
{
    c.nospace() << "Appearance("
                << "Font:" << appearance.font() 
                <<')';
    return c.space();
}
