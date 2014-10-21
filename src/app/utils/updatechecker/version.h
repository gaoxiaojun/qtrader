/*
 * Copyright 2013-2014 Dailypips
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef VERSION_H
#define VERSION_H

#include <QString>

namespace Util {

class Version
{

public:
    static Version fromString(const QString &string);

    explicit Version(unsigned int major, unsigned int minor, unsigned int patch, const QString &revisor);

    Version();
    Version(const Version &copyMe);

    Version operator = (const Version &copyMe);
    bool operator > (const Version &compareTo) const;

    bool isValid() const;
    QString toString() const;

    unsigned int major() const;
    unsigned int minor() const;
    unsigned int patch() const;
    QString revisor() const;

private:
    unsigned int m_major;
    unsigned int m_minor;
    unsigned int m_patch;
    QString m_revisor;

};

} // namespace Util

#endif // VERSION_H
