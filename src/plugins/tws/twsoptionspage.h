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

#ifndef TwsOptionsPage_H
#define TwsOptionsPage_H

#include "iboptionswidget.h"
#include <coreplugin/dialogs/ioptionspage.h>

#include <QObject>

namespace TWS {

class TwsOptionsPage : public Core::IOptionsPage
{
    Q_OBJECT
public:
    explicit TwsOptionsPage(QObject *parent = 0);
    ~TwsOptionsPage();

    QWidget *createPage(QWidget *parent);
    void apply();
    void finish();
private:
     IBOptionsWidget * m_pages;
};

} // namespace TWS
#endif // TwsOptionsPage_H
