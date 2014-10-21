/****************************************************************************
** Copyright (C) 2001-2012 Klaralvdalens Datakonsult AB.  All rights reserved.
**
** This file is part of the KD Tools library.
**
** Licensees holding valid commercial KD Tools licenses may use this file in
** accordance with the KD Tools Commercial License Agreement provided with
** the Software.
**
**
** This file may be distributed and/or modified under the terms of the GNU
** Lesser General Public License version 2 and version 3 as published by the
** Free Software Foundation and appearing in the file LICENSE.LGPL included.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
** Contact info@kdab.net if any conditions of this licensing are not
** clear to you.
**
**********************************************************************/

#include "kdupdaterfiledownloaderfactory.h"
#include "kdupdaterfiledownloader_p.h"

#include <cassert>

/*!
   \internal
   \ingroup kdupdater
   \class KDUpdater::FileDownloaderFactory kdupdaterfiledownloaderfactory.h
   \brief Factory for \ref KDUpdater::FileDownloader

   This class acts as a factory for \ref KDUpdater::FileDownloader. You can register
   one or more file downloaders with this factory and query them based on their scheme.

   This class follows the singleton design pattern. Only one instance of this class can
   be created and its reference can be fetched from the \ref instance() method.
*/

using namespace KDUpdater;

struct FileDownloaderFactory::FileDownloaderFactoryData
{
    bool m_followRedirects;
};

FileDownloaderFactory& FileDownloaderFactory::instance()
{
    static KDUpdater::FileDownloaderFactory theFactory;
    return theFactory;
}

/*!
   Constructor
*/
FileDownloaderFactory::FileDownloaderFactory()
    : d ( new FileDownloaderFactoryData )
{
    // Register the default file downloader set
    registerFileDownloader< LocalFileDownloader >( QLatin1String( "file" ) );
#if 0
    registerFileDownloader< FtpDownloader >( QLatin1String( "ftp" ) );
#endif
    registerFileDownloader< HttpDownloader >( QLatin1String( "http" ) );
    registerFileDownloader< ResourceFileDownloader >( QLatin1String( "resource" ) );
    d->m_followRedirects = false;
}
/*!
  Configures the factory to handle redirects if the protocol of the download supports it
 */
void FileDownloaderFactory::setFollowRedirects( bool val )
{
    FileDownloaderFactory::instance().d->m_followRedirects = val;
}

/*!
    Checks if the factory creates downloader that follow redirects
*/
bool FileDownloaderFactory::followRedirects()
{
    return FileDownloaderFactory::instance().d->m_followRedirects;
}

/*!
  Destructor
*/
FileDownloaderFactory::~FileDownloaderFactory()
{
}

/*!
   Returns a new instance to the \ref KDUpdater::FileDownloader based whose scheme is equal to the string
   passed as parameter to this function.
   \note Ownership of this object remains to the programmer.
*/
FileDownloader* FileDownloaderFactory::create( const QString& scheme, QObject* parent ) const
{
    FileDownloader* const downloader = KDGenericFactory< FileDownloader >::create( scheme );
    if( downloader != 0 ) {
        downloader->setFollowRedirects( d->m_followRedirects );
        downloader->setParent( parent );
    }
    return downloader;
}

/*!
   KDUpdater::FileDownloaderFactory::registerFileDownlooader
   Registers a new file downloader with the factory. If there is already a downloader with the same scheme,
   the downloader is replaced. The ownership of the downloader is transfered to the factory.
*/

/*!
   Returns the number of file downloaders in the factory.
*/
int FileDownloaderFactory::fileDownloaderCount() const
{
    return productCount();
}

/*!
   Returns a list of schemes supported by this factory, i.e. for which a 
   FileDownloader was registered.
*/
QStringList FileDownloaderFactory::supportedSchemes() const
{
    return availableProducts();
}
