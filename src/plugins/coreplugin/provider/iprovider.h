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

#ifndef __OPENTRADE_IPROVIDER_H__
#define __OPENTRADE_IPROVIDER_H__

#include "core_global.h"

#include <QObject>
#include <QDateTime>

namespace OpenTrade {

class Instrument;
class Bar;

/*namespace Internal {
  class ProviderInfoPrivate;
}*/

class CORE_EXPORT ProviderInfo
{
public:
    //~ProviderInfo();
    unsigned int id() const;
    QString description() const;
    QString name() const;
    QString url() const;
    QString version() const;
    QString compatVersion() const;
    QString license() const;
    QString vendor() const;
    QString copyright() const;
/*private:
    ProviderInfo();
    Internal::ProviderInfoPrivate *d;
    friend class Internal::ProviderInfoPrivate;*/
};

class CORE_EXPORT IProvider : public QObject
{
    Q_OBJECT

public:
    explicit IProvider(QObject *parent = 0) : QObject(parent) {}
    virtual ~IProvider() {}

    virtual ProviderInfo *info() const = 0;

    virtual bool isConnected() const = 0;

    virtual void connect() = 0;
    virtual void disonnect() = 0;
    virtual void shutdown() = 0;


signals:
    void connted();
    void disconnected();

    void error(const QString& errorMessage);
    void error(int errorCode, const QString& errorMessage);

    /* For cases where you may require information on the sender of the signal,
     * Qt provides the QObject::sender() function, which returns a pointer to the object that sent the signal.
     * Be aware that sender() returns a null pointer, if the slot is called directly
     * (i.e. not using a signal/slot connection).
     */
};

} // namespace OpenTrade
#endif // __OPENTRADE_IPROVIDER_H__
