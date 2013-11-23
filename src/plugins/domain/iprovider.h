/****************************************************************************
**
** Copyright (C) 2013 Xiaojun Gao
** Contact: http://www.dailypips.org/legal
**
** This file is part of QTrader.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Digia gives you certain additional
** rights.  These rights are described in the Digia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
****************************************************************************/

#ifndef IPROVIDER_HPP
#define IPROVIDER_HPP

#include <QObject>
#include <QDateTime>

class Instrument;
class Bar;


class IProvider : public QObject
{
    Q_OBJECT

public:
    explicit IProvider(QObject *parent = 0) : QObject(parent) {}
    virtual ~IProvider() {}

    virtual int id() const = 0;
    virtual bool isConnected() = 0;

    virtual QString description() const = 0;
    virtual QString name() const = 0;
    virtual QString url() const = 0;

    virtual void connect() = 0;
    virtual void disonnect() = 0;
    virtual void shutdown() = 0;

signals:
    void connted();
    void disconnected();

    void error(int providerId, const QString& errorMessage);
    void error(int providerId, int errorCode, const QString& errorMessage);
};

#endif // IPROVIDER_HPP
