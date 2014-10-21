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

#ifndef __TWS_OPTIONS_WIDGET_H__
#define __TWS_OPTIONS_WIDGET_H__

#include <QWidget>

namespace Ui {
   class TwsOptionsWidget;
}

namespace TWS {

class TwsOptionsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TwsOptionsWidget(QWidget *parent = 0);
    ~TwsOptionsWidget();

public:
    void setHost(const QString& host);
    void setPort(unsigned int port);
    QString host() const;
    unsigned int port() const;

private:
    Ui::TwsOptionsWidget *ui;
};

} // namespace TWS

#endif // __TWS_OPTIONS_WIDGET_H__
