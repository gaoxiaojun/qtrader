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

#ifndef ORDERMANAGER_H
#define ORDERMANAGER_H

#include "opentrade_global.h"

#include "order.h"

#include <QObject>

/*
 * 主要功能:
 *   1.创建订单
 *
 */
class OPENTRADE_EXPORT OrderManager : public QObject
{
    Q_OBJECT
public:
    explicit OrderManager(QObject *parent = 0);

    /*
     *
     */

signals:

public slots:

};

#endif // ORDERMANAGER_H
