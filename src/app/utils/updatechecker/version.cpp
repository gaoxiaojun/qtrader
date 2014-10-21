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

#include "Version.h"
#include <QStringList>

Version Version::fromString(const QString &string)
{
    QStringList parts = string.split(QLatin1String("."));
    if (parts.size() < 3 || parts.size() > 5)
        return Version();

    bool ok;
    unsigned int major = parts.at(0).toUShort(&ok);
    if (!ok)
        return Version();
    unsigned int minor = parts.at(1).toUShort(&ok);
    if (!ok)
        return Version();
    unsigned int patch = parts.at(2).toUShort(&ok);
    if (!ok)
        return Version();

    if (parts.size() == 4)
        return Version(major, minor, patch, parts.at(3));
    else
        return Version(major, minor, patch, QString());
}

Version::Version(unsigned int major, unsigned int minor, unsigned int patch, const QString &revisor)
    : m_major(major), m_minor(minor), m_patch(patch), m_revisor(revisor)
{
}

Version::Version()
    : m_major(0), m_minor(0), m_patch(0)
{
}

Version::Version(const Version &other)
    : m_major(), m_minor(), m_patch(), m_revisor()
{
    m_major = other.m_major;
    m_minor = other.m_minor;
    m_patch = other.m_patch;
    m_revisor = other.m_revisor;
}

Version Version::operator = (const Version &other)
{
    m_major = other.m_major;
    m_minor = other.m_minor;
    m_patch = other.m_patch;
    m_revisor = other.m_revisor;

    return *this;
}

bool Version::operator > (const Version &compareTo) const
{
    Q_ASSERT(isValid());
    Q_ASSERT(compareTo.isValid());

    if (m_major > compareTo.m_major)
        return true;
    if (m_major < compareTo.m_major)
        return false;
    if (m_minor > compareTo.m_minor)
        return true;
    if (m_minor < compareTo.m_minor)
        return false;
    return m_patch > compareTo.m_patch;
}

bool Version::isValid() const
{
    return m_major != 0 || m_minor != 0 || m_patch != 0;
}

QString Version::toString() const
{
    if (m_revisor.isEmpty())
        return QString::fromLatin1("%1.%2.%3").arg(m_major).arg(m_minor).arg(m_patch);
    else
        return QString::fromLatin1("%1.%2.%3.%4").arg(m_major).arg(m_minor).arg(m_patch).arg(m_revisor);
}

unsigned int Version::major() const
{
    return m_major;
}

unsigned int Version::minor() const
{
    return m_minor;
}

unsigned int Version::patch() const
{
    return m_patch;
}

QString Version::revisor() const
{
    return m_revisor;
}
