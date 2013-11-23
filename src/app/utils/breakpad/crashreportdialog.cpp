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

#include "CrashReportDialog.h"

#include <QBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QCheckBox>
#include <QCommandLinkButton>
#include <QProgressBar>
#include <QStyle>
#include <QFile>
#include <QNetworkAccessManager>
#include <QUrl>
#include <QApplication>
#include <QStackedLayout>
#include <QNetworkReply>
#include <QDialogButtonBox>
#include <QPropertyAnimation>
#include <QShowEvent>
#include <QMenu>
#include <QFileDialog>
#include <QMessageBox>
#include <QNetworkRequest>
#if QT_VERSION >= QT_VERSION_CHECK(5,0,0)
#   include <QUrlQuery>
#endif

CrashReportDialog::CrashReportDialog(const QString& reportUrl, const QString &dumpFile, QWidget *parent)
    : QDialog(parent), m_reportUrl(reportUrl), m_dumpFile(dumpFile), m_uploadReply(0), m_finalResult(QDialog::Accepted)
{
    setFixedSize(430, 270);

    QBoxLayout *mainLayout = new QVBoxLayout(this);

    QBoxLayout *topLayout = new QHBoxLayout;
    mainLayout->addLayout(topLayout);

    QLabel *icon = new QLabel;
    icon->setPixmap(style()->standardPixmap(QStyle::SP_MessageBoxCritical));
    topLayout->addWidget(icon, 0, Qt::AlignLeft | Qt::AlignVCenter);

	m_titleLabel = new QLabel();
	m_titleLabel->setStyleSheet(QLatin1String("font-size:16px;color:#003399;"));
	m_titleLabel->setAlignment(Qt::AlignCenter);
	topLayout->addWidget(m_titleLabel, 1, Qt::AlignCenter);

    m_stackLayout = new QStackedLayout(mainLayout);

    QWidget *container = new QWidget;
    m_stackLayout->addWidget(container);
    QBoxLayout *layout = new QVBoxLayout(container);
    layout->setMargin(0);

    layout->addStretch();

	m_allowReport = new QCheckBox;
    m_allowReport->setChecked(true);
    m_allowReport->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(m_allowReport, SIGNAL(customContextMenuRequested(QPoint)), SLOT(reportContextMenu(QPoint)));
    layout->addWidget(m_allowReport, 0, Qt::AlignCenter);

    QBoxLayout *emailLayout = new QHBoxLayout;
    layout->addLayout(emailLayout);

	m_emailLabel = new QLabel;
	emailLayout->addWidget(m_emailLabel);

    m_emailInput = new QLineEdit;
    emailLayout->addWidget(m_emailInput);

	m_emailInformationLabel= new QLabel;
	m_emailInformationLabel->setStyleSheet(QLatin1String("color:#606060;font-size:9px"));
	m_emailInformationLabel->setWordWrap(true);
	m_emailInformationLabel->setAlignment(Qt::AlignRight | Qt::AlignTop);
	layout->addWidget(m_emailInformationLabel);

    layout->addStretch();
    layout->addSpacing(15);

    m_restartBtn = new QCommandLinkButton;
    m_restartBtn->setDefault(true);
    connect(m_restartBtn, SIGNAL(clicked()), SLOT(uploadAndRestart()));
    layout->addWidget(m_restartBtn);

    m_exitBtn = new QCommandLinkButton;
    connect(m_exitBtn, SIGNAL(clicked()), SLOT(uploadAndExit()));
    layout->addWidget(m_exitBtn);

    /* Upload progress widgets */
    QWidget *uploadContainer = new QWidget;
    m_stackLayout->addWidget(uploadContainer);

    QBoxLayout *uploadLayout = new QVBoxLayout(uploadContainer);
    uploadLayout->setMargin(0);
    uploadLayout->addStretch();

	m_progressLabel = new QLabel;
	uploadLayout->addWidget(m_progressLabel);

    m_uploadProgress = new QProgressBar;
    m_uploadProgress->setTextVisible(false);
    uploadLayout->addWidget(m_uploadProgress);

    uploadLayout->addStretch();

    QDialogButtonBox *btn = new QDialogButtonBox(QDialogButtonBox::Cancel, Qt::Horizontal);
    uploadLayout->addWidget(btn);

	retranslateUI();
}

CrashReportDialog::~CrashReportDialog()
{
    if (m_uploadReply)
    {
        m_uploadReply->abort();
        delete m_uploadReply;
    }
}

void CrashReportDialog::showEvent(QShowEvent *event)
{
    if (!event->spontaneous())
    {
        activateWindow();
        raise();
    }

    QDialog::showEvent(event);
}

void CrashReportDialog::reportContextMenu(const QPoint &point)
{
    QWidget *from = qobject_cast<QWidget*>(sender());
    if (!from)
        return;

    QMenu menu;
    menu.addAction(tr("Save crash report"), this, SLOT(saveCrashReport()));
    menu.exec(from->mapToGlobal(point));
}

void CrashReportDialog::saveCrashReport()
{
    QString path = QFileDialog::getSaveFileName(this, tr("Save crash report"), QString(), tr("Crash report (*.dmp)"));
    if (path.isEmpty())
        return;

    if (QFile::exists(path))
        QFile::remove(path);

    if (!m_dumpFile.copy(path))
		QMessageBox::critical(this, tr("Error"), tr("An error occurred while saving the crash report:\n\n%1").arg(m_dumpFile.errorString()));
}

void CrashReportDialog::changeEvent(QEvent *event)
{
	if (event && event->type() == QEvent::LanguageChange)
		retranslateUI();

	QDialog::changeEvent(event);
}

void CrashReportDialog::uploadAndRestart()
{
    m_finalResult = QDialog::Accepted;
    sendReport();
}

void CrashReportDialog::uploadAndExit()
{
    m_finalResult = QDialog::Rejected;
    sendReport();
}

void CrashReportDialog::sendReport()
{
    if (m_uploadReply)
        return;

    if (!m_allowReport->isChecked())
    {
        done(m_finalResult);
        return;
    }

    QString platform =
#if defined(Q_OS_WIN)
                       QLatin1String("windows");
#elif defined(Q_OS_MAC)
                       QLatin1String("mac");
#elif defined(Q_OS_LINUX)
                       QLatin1String("linux");
#else
                       QLatin1String("unknown");
#endif

    QNetworkAccessManager *nam = new QNetworkAccessManager(this);
#if QT_VERSION < QT_VERSION_CHECK(5, 0, 0)
    QUrl queryUrl(m_reportUrl);
#else
    QUrlQuery queryUrl(m_reportUrl);
    QUrl url;
#endif
    queryUrl.addQueryItem(QLatin1String("version"), qApp->applicationVersion());
    queryUrl.addQueryItem(QLatin1String("platform"), platform);
    if (!m_emailInput->text().isEmpty())
        queryUrl.addQueryItem(QLatin1String("email"), m_emailInput->text());

    if (!m_dumpFile.exists() || !m_dumpFile.open(QIODevice::ReadOnly))
    {
        queryUrl.addQueryItem(QLatin1String("dump"), QLatin1String("0"));
#if QT_VERSION < QT_VERSION_CHECK(5, 0, 0)
        url.setQuery(queryUrl);
#endif
        m_uploadReply = nam->get(QNetworkRequest(url));
    }
    else
    {
#if QT_VERSION < QT_VERSION_CHECK(5, 0, 0)
        url.setQuery(queryUrl);
#endif
        QNetworkRequest req(url);
        const char *boundary = "UPLOADDUMP";
        req.setHeader(QNetworkRequest::ContentTypeHeader, QByteArray("multipart/form-data; boundary=") + boundary);

        QByteArray data;
        data.append("--");
        data.append(boundary);
        data.append("\r\ncontent-disposition: form-data; name=\"dump\"; filename=\"temp.dmp\"\r\nContent-Transfer-Encoding: binary\r\nContent-Length: ");
        data.append(m_dumpFile.size());
        data.append("\r\nContent-type: application/x-octet-stream\r\n\r\n");
        data.append(m_dumpFile.readAll());
        data.append("\r\n--");
        data.append(boundary);
        data.append("--\r\n");
        m_dumpFile.close();

        m_uploadReply = nam->post(req, data);
    }

    connect(m_uploadReply, SIGNAL(finished()), SLOT(uploadFinished()));
    bool ok = connect(m_uploadReply, SIGNAL(uploadProgress(qint64,qint64)), SLOT(setUploadProgress(qint64)));
    Q_UNUSED(ok);
    Q_ASSERT(ok);
    m_uploadProgress->setMaximum((int)m_dumpFile.size());

    m_stackLayout->setCurrentIndex(1);

    setFixedHeight(QWIDGETSIZE_MAX);
    QPropertyAnimation *resizeAnimation = new QPropertyAnimation(this, "size");
    resizeAnimation->setEndValue(QSize(width(), minimumSizeHint().height()));
    resizeAnimation->setDuration(150);
    resizeAnimation->setEasingCurve(QEasingCurve::InQuad);
    resizeAnimation->start(QAbstractAnimation::DeleteWhenStopped);
}

void CrashReportDialog::setUploadProgress(qint64 done)
{
    m_uploadProgress->setValue((int)done);
}

void CrashReportDialog::uploadFinished()
{
    m_uploadReply->deleteLater();
    m_uploadReply = 0;

    done(m_finalResult);
}


void CrashReportDialog::retranslateUI()
{
	setWindowTitle(tr("Application - Report Crash"));

	m_titleLabel->setText(tr("The Application crashed!"));
	m_allowReport->setText(tr("Send an automatic crash report"));
	m_emailLabel->setText(tr("Email:"));
	m_emailInformationLabel->setText(tr("If you enter your email address, we will update you on our progress with this bug"));
	m_progressLabel->setText(tr("Sending crash report..."));

	m_allowReport->setText(tr("Send an automatic crash report"));

	m_restartBtn->setText(tr("Restart Client"));
	m_exitBtn->setText(tr("Exit"));

}
