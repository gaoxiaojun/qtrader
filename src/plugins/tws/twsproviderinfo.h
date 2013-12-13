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

#ifndef TWSPROVIDERINFO_H
#define TWSPROVIDERINFO_H

#include <opentrade/iprovider.h>

namespace TWS {

class TwsProviderInfo : public OpenTrade::ProviderInfo
{
public:
    unsigned int id() const { return m_id;}
    QString description() const { return m_description; }
    QString name() const    { return m_name; }
    QString url() const     { return m_url; }
    QString version() const { return m_version; }
    QString compatVersion() const {return m_compatVersion; }
    QString license() const { return m_license; }
    QString vendor() const { return m_vendor; }
    QString copyright() const { return m_copyright; }

    unsigned int m_id;
    QString m_description;
    QString m_name;
    QString m_url;
    QString m_version;
    QString m_compatVersion;
    QString m_license;
    QString m_vendor;
    QString m_copyright;

};

} // namespace TWS

#endif // TWSPROVIDERINFO_H
