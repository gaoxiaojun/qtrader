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

#include "twsoptionspage.h"
#include "iboptionswidget.h"
#include "twsclient.h"

#include <QIcon>

using namespace TWS;

TwsOptionsPage::TwsOptionsPage(QObject *parent) :
    Core::IOptionsPage(parent)
{
    setId ("IBOptions");
    setDisplayName (tr("IBOptions"));
    setCategory ("TWS");
    setDisplayCategory (tr("TWS"));
    setCategoryIcon (":/tws/images/ib.png");
}

TwsOptionsPage::~TwsOptionsPage ()
{

}


QWidget* TwsOptionsPage::createPage (QWidget *parent)
{
   m_pages = new IBOptionsWidget(parent);
   m_pages->setHost(TwsClient::instance ()->host());
   m_pages->setPort(TwsClient::instance()->port());

   return m_pages;
}

void TwsOptionsPage::apply ()
{
    if(m_pages) {
        TwsClient::instance ()->setHost (m_pages->host ());
        TwsClient::instance ()->setPort (m_pages->port ());
    }
}

void TwsOptionsPage::finish ()
{
    m_pages = 0;
}
