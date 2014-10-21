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

#include "kdupdaterupdatesourcesinfo.h"
#include "kdupdatertarget.h"

#include <QDomElement>
#include <QDomDocument>
#include <QDomText>
#include <QDomCDATASection>
#include <QFileInfo>
#include <QFile>
#include <QTextStream>
#include <QVector>

#include <algorithm>

#include <KDToolsCore/kdsavefile.h>

/*!
   \ingroup kdupdater
   \class KDUpdater::UpdateSourcesInfo kdupdaterupdatesourcesinfo.h KDUpdaterUpdateSourcesInfo
   \brief Provides access to information about the update sources set for the target.

   An update source is a repository that contains updates applicable for the target.
   Applications can download updates from the update source and install them locally.

   Each target can have one or more update sources from which it can download updates.
   Information about update source is stored in a file called UpdateSources.xml. This class helps
   access and modify the UpdateSources.xml file.

   The complete file name of the UpdateSources.xml file can be specified via the \ref fileName()
   property. The class then parses the XML file and makes available information contained in
   that XML file through an easy-to-use API. You can

   \li Get update sources information via the \ref updateSourceInfoCount() and \ref updateSourceInfo()
   methods.
   \li You can add/remove/change update source information via the \ref addUpdateSourceInfo(),
   \ref removeUpdateSource(), \ref setUpdateSourceAt() methods.

   The class emits appropriate signals to inform listeners about changes in the update target.
*/

/*! \enum UpdateSourcesInfo::Error
 * Error codes related to retrieving update sources
 */

/*! \var UpdateSourcesInfo::Error UpdateSourcesInfo::NoError
 * No error occurred
 */

/*! \var UpdateSourcesInfo::Error UpdateSourcesInfo::NotYetReadError
 * The package information was not parsed yet from the XML file
 */

/*! \var UpdateSourcesInfo::Error UpdateSourcesInfo::CouldNotReadSourceFileError
 * the specified update source file could not be read (does not exist or not readable)
 */

/*! \var UpdateSourcesInfo::Error UpdateSourcesInfo::InvalidXmlError
 * The source file contains invalid XML. 
 */

/*! \var UpdateSourcesInfo::Error UpdateSourcesInfo::InvalidContentError
 * The source file contains valid XML, but does not match the expected format for source descriptions
 */

/*! \var UpdateSourcesInfo::Error UpdateSourcesInfo::CouldNotSaveChangesError
 * Changes made to the object could be saved back to the source file
 */

/*!
   \fn void KDUpdater::UpdateSourcesInfo::reset

   This signal is emitted whenever the contents of this UpdateSourcesInfo is refreshed, usually from within the refresh() slot.
*/

/*! 
   \fn void KDUpdater::UpdateSourcesInfo::aboutToAddUpdateSourceInfo( int index, const UpdateSourceInfo& info )

   This signal is emitted immediately before UpdateSourceInfo \a info is getting added at \a index.
*/

/*! 
   \fn void KDUpdater::UpdateSourcesInfo::updateSourceInfoAdded( const UpdateSourceInfo& info )

   This signal is emitted when UpdateSourceInfo \a info was added.
*/

/*!
   \fn void KDUpdater::UpdateSourcesInfo::abautToRemoveUpdateSourceInfo( const UpdateSourceInfo& info )

   This signal is emitted immediately before UpdateSourceInfo \a info is getting removed.
*/

/*!
   \fn void KDUpdater::UpdateSourcesInfo::updateSourceInfoRemoved( const UpdateSourceInfo& info )

   This signal is emitted when UpdateSourceInfo \a info was removed.
*/

/*!
   \fn void KDUpdater::UpdateSourcesInfo::updateSourceInfoChanged( const UpdateSourceInfo& newInfo, const UpdateSourceInfo& oldInfo)

   This signal is emitted when an UpdateSourceInfo was changed from \a oldInfo to \a newInfo.
*/

using namespace KDUpdater;

namespace KDUpdater
{
struct UpdateSourceInfoPriorityHigherThan
{
    bool operator()( const UpdateSourceInfo& lhs, const UpdateSourceInfo& rhs ) const
    {
        return lhs.priority > rhs.priority;
    }
};
}

UpdateSourceInfo::UpdateSourceInfo()
    : priority( -1 )
{
}

class UpdateSourcesInfo::Private
{
public:
    Private( UpdateSourcesInfo* qq ) :
        q( qq ),
        error(UpdateSourcesInfo::NotYetReadError),
        target( 0 ),
        modified(false)
    {}

    UpdateSourcesInfo* q;

    QString errorMessage;
    UpdateSourcesInfo::Error error;
    Target * target;
    bool modified;
    QString fileName;
    QVector<UpdateSourceInfo> updateSourceInfoList;

    void addUpdateSourceFrom( const QDomElement & element );
    void addChildElement( QDomDocument & doc, QDomElement & parentE, const QString & tagName, const QString & text, bool htmlText=false );
    void setInvalidContentError( const QString& detail );
    void clearError();
    void saveChanges();
};

void UpdateSourcesInfo::Private::setInvalidContentError(const QString& detail)
{
    error = UpdateSourcesInfo::InvalidContentError;
    errorMessage = tr("%1 contains invalid content: %2").arg(fileName, detail);
}

void UpdateSourcesInfo::Private::clearError()
{
    error = UpdateSourcesInfo::NoError;
    errorMessage.clear();
}

/*!
   \internal
*/
UpdateSourcesInfo::UpdateSourcesInfo( Target * target )
    : d( new Private( this ) )
{
    d->target = target;
}

/*!
   \internal
*/
UpdateSourcesInfo::~UpdateSourcesInfo()
{
    d->saveChanges();
    //delete d;
}

/*!
   Returns a pointer to the update target for which this instance manages update sources.
*/
Target * UpdateSourcesInfo::target() const
{
    return d->target;
}

/*!
   \internal
*/
bool UpdateSourcesInfo::isValid() const
{
    return d->error == NoError;
}

/*!
   Contains a human-readable description of the error.

   Read this property's value using %errorString().
 */
QString UpdateSourcesInfo::errorString() const
{
    return d->errorMessage;
}

/*!
   Returns the modified state. The modified state defines if there wehere
   modifications done to the update-sources that need to be written to the
   Updates.xml file that will restore the update-sources on the next run.
*/
bool UpdateSourcesInfo::isModified() const
{
    return d->modified;
}

/*!
   Explicitly set the modified state. See also the \a isModified method.
*/
void UpdateSourcesInfo::setModified(bool modified)
{
    d->modified = modified;
}

/*!
   Contains the last error.

   Read this property's value using %error().
 */
UpdateSourcesInfo::Error UpdateSourcesInfo::error() const
{
    return d->error;
}

void UpdateSourcesInfo::setFileName(const QString& fileName)
{
    if( d->fileName == fileName )
        return;

    d->fileName = fileName;
    refresh(); // load new file
}

/*!
   Specifies the name of the UpdateSources.xml file that this instance refers to.

   Setting this property also issues a call to refresh() to reload package information
   from the XML file.

   Get this property's value using %fileName(), and set it
   using %setFileName().
   
   \sa KDUpdater::Target::updateSourcesXMLFileName
*/
QString UpdateSourcesInfo::fileName() const
{
    return d->fileName;
}

/*!
   Returns the number of update source info structures contained in this instance.
*/
int UpdateSourcesInfo::updateSourceInfoCount() const
{
    return d->updateSourceInfoList.count();
}

/*!
   Returns the update source info structure at \c index. If an invalid index is passed
   the function returns a dummy constructor.
*/
UpdateSourceInfo UpdateSourcesInfo::updateSourceInfo(int index) const
{
    if( index < 0 || index >= d->updateSourceInfoList.count() )
        return UpdateSourceInfo();

    return d->updateSourceInfoList[index];
}

/*!
   Adds an update source info to this class. Upon successful addition, the class emits an
   \ref updateSourceInfoAdded() signal.
*/
void UpdateSourcesInfo::addUpdateSourceInfo(const UpdateSourceInfo& info)
{
    if( d->updateSourceInfoList.contains( info ) )
        return;
    QVector< UpdateSourceInfo > infoList = d->updateSourceInfoList;
    infoList.push_back( info );
    qSort( infoList.begin(), infoList.end(), UpdateSourceInfoPriorityHigherThan() );
    emit aboutToAddUpdateSourceInfo( infoList.indexOf( info ), info );
    d->updateSourceInfoList = infoList;
    emit updateSourceInfoAdded(info);
    d->modified = true;
}

/*!
   Removes an update source info from this class. Upon successful removal, the class emits an
   \ref updateSourceInfoRemoved() signal.
*/
void UpdateSourcesInfo::removeUpdateSourceInfo(const UpdateSourceInfo& info)
{
    if( !d->updateSourceInfoList.contains(info) )
        return;
    emit aboutToRemoveUpdateSourceInfo( info );
    d->updateSourceInfoList.erase( 
        std::remove( d->updateSourceInfoList.begin(), d->updateSourceInfoList.end(), info ), d->updateSourceInfoList.end() );
    emit updateSourceInfoRemoved( info );
    d->modified = true;
}

/*!
   Removes an update source info at \index in this class. Upon successful removal, the class emits an
   \ref updateSourceInfoRemoved() signal.
*/
void UpdateSourcesInfo::removeUpdateSourceInfoAt(int index)
{
    if( index < 0 || index >= d->updateSourceInfoList.count() )
        return;

    const UpdateSourceInfo& info = d->updateSourceInfoList[index];
    removeUpdateSourceInfo( info );
}

/*!
   Changes the update source info at \p index to \p info. If \p index is equal to the number of
   source info structures in this class (\ref updateSourceInfoCount()), then \p info is appended;
   otherwise the existing info at \p index will be changed.

   Depending on what the function does, \ref updateSourceInfoAdded() or \ref updateSourceInfoChanged()
   signal is emitted.
*/
void UpdateSourcesInfo::setUpdateSourceInfoAt(int index, const UpdateSourceInfo& info)
{
    if( index < 0 || index > d->updateSourceInfoList.count() )
        return;

    if( index == d->updateSourceInfoList.count() )
    {
        emit aboutToAddUpdateSourceInfo( index, info );
        d->updateSourceInfoList.append(info);
        emit updateSourceInfoAdded(info);
    }
    else
    {
        UpdateSourceInfo oldInfo = d->updateSourceInfoList[index];
        if( info == oldInfo )
            return;

        d->updateSourceInfoList[index] = info;
        emit updateSourceInfoChanged(info, oldInfo);
    }
    d->modified = true;
}

/*!
   This slot reloads the update source information from UpdateSources.xml.
*/
void UpdateSourcesInfo::refresh()
{
    d->saveChanges(); // save changes done in the previous file
    d->updateSourceInfoList.clear();

    QFile file( d->fileName );
    
    // if the file does not exist then we just skip the reading
    if( !file.exists() )
    {
        d->clearError();
        emit reset();
        return;
    }
    
    // Open the XML file
    if( !file.open(QFile::ReadOnly) )
    {
        d->errorMessage = tr("Could not read \"%1\"").arg(d->fileName);
        d->error = CouldNotReadSourceFileError;
        emit reset();
        return;
    }

    QDomDocument doc;
    QString parseErrorMessage;
    int parseErrorLine;
    int parseErrorColumn;
    if( !doc.setContent( &file, &parseErrorMessage, &parseErrorLine, &parseErrorColumn ) )
    {
        d->error = InvalidXmlError;
        d->errorMessage = tr("XML Parse error in %1 at %2, %3: %4")
                          .arg( d->fileName,
                                QString::number( parseErrorLine ),
                                QString::number( parseErrorColumn ),
                                parseErrorMessage );
        emit reset();
        return;
    }

    // Now parse the XML file.
    const QDomElement rootE = doc.documentElement();
    if( rootE.tagName() != QLatin1String( "UpdateSources" ) )
    {
        d->setInvalidContentError(tr("Root element %1 unexpected, should be \"UpdateSources\"").arg(rootE.tagName()));
        emit reset();
        return;
    }

    for( QDomNode childNode = rootE.firstChild(); !childNode.isNull(); childNode = childNode.nextSiblingElement() )
    {
        const QDomElement childNodeE = childNode.toElement();
        if( childNodeE.isNull() )
            continue;

        if( childNodeE.tagName() == QLatin1String( "UpdateSource" ) )
            d->addUpdateSourceFrom(childNodeE);
    }

    d->clearError();
    emit reset();
}

void UpdateSourcesInfo::Private::saveChanges()
{
    if( !modified || fileName.isEmpty() )
        return;

    const bool hadSaveError = error == UpdateSourcesInfo::CouldNotSaveChangesError; 
        
    QDomDocument doc;

    QDomElement rootE = doc.createElement( QLatin1String( "UpdateSources") );
    doc.appendChild(rootE);

    for( QVector< UpdateSourceInfo >::const_iterator it = updateSourceInfoList.begin(); it != updateSourceInfoList.end(); ++it )
    {
        const UpdateSourceInfo& info = *it;

        QDomElement infoE = doc.createElement( QLatin1String( "UpdateSource" ) );
        rootE.appendChild(infoE);
        addChildElement(doc, infoE, QLatin1String( "Name" ), info.name);
        addChildElement(doc, infoE, QLatin1String( "Title" ), info.title);
        addChildElement(doc, infoE, QLatin1String( "Description" ),  info.description,
                           (info.description.length() && info.description[0] == QLatin1Char( '<' ) ) );
        addChildElement(doc, infoE, QLatin1String( "Url" ),  info.url.toString());
    }

    KDSaveFile file( fileName );
    if ( !file.open( QFile::WriteOnly ) )
    {
        error = UpdateSourcesInfo::CouldNotSaveChangesError;
        errorMessage = tr("Could not save changes to \"%1\": %2").arg(fileName, file.errorString());
        return;
    }
    
    QTextStream stream( &file );
    doc.save( stream, 2 );
    stream.flush();
    file.commit( KDSaveFile::OverwriteExistingFile );

    if ( file.error() != QFile::NoError )
    {
        error = UpdateSourcesInfo::CouldNotSaveChangesError;
        errorMessage = tr("Could not save changes to \"%1\": %2").arg(fileName, file.errorString());
        return;
    }
    
    //if there was a write error before, clear the error, as the write was successful now
    if ( hadSaveError )
        clearError();
    
    modified = false;
}

void UpdateSourcesInfo::Private::addUpdateSourceFrom( const QDomElement & element )
{
    if( element.tagName() != QLatin1String( "UpdateSource" ) )
        return;

    if( !element.hasChildNodes() )
        return;
    const QDomNodeList childNodes = element.childNodes();

    UpdateSourceInfo info;

    for( QDomNode childNode = element.firstChild(); !childNode.isNull(); childNode = childNode.nextSiblingElement() )
    {
        const QDomElement childNodeE = childNode.toElement();
        if( childNodeE.isNull() )
            continue;

        if( childNodeE.tagName() == QLatin1String( "Name" ) )
            info.name = childNodeE.text();
        else if( childNodeE.tagName() == QLatin1String( "Title" ) )
            info.title = childNodeE.text();
        else if( childNodeE.tagName() == QLatin1String( "Description" ) )
            info.description = childNodeE.text();
        else if( childNodeE.tagName() == QLatin1String( "Url" ) )
            info.url = childNodeE.text();
    }

    this->updateSourceInfoList.append(info);
}

void UpdateSourcesInfo::Private::addChildElement( QDomDocument & doc, QDomElement & parentE, const QString & tagName, const QString & text, bool htmlText )
{
    QDomElement childE = doc.createElement(tagName);
    parentE.appendChild(childE);

    if( htmlText )
    {
        const QDomCDATASection textE = doc.createCDATASection(text);
        childE.appendChild(textE);
    }
    else
    {
        const QDomText textE = doc.createTextNode(text);
        childE.appendChild(textE);
    }
}

/*!
   \ingroup kdupdater
   \struct KDUpdater::UpdateSourceInfo kdupdaterupdatesourcesinfo.h KDUpdaterUpdateSourcesInfo
   \brief Describes a single update source

   An update source is a repository that contains updates applicable for the target.
   This structure describes a single update source in terms of name, title, description, url and priority.
*/

/*!
   \var QString KDUpdater::UpdateSourceInfo::name
*/

/*!
   \var QString KDUpdater::UpdateSourceInfo::title
*/

/*!
   \var QString KDUpdater::UpdateSourceInfo::description
*/

/*!
   \var QUrl KDUpdater::UpdateSourceInfo::url
*/

/*!
   \var QUrl KDUpdater::UpdateSourceInfo::priority
*/

bool KDUpdater::operator==( const UpdateSourceInfo & lhs, const UpdateSourceInfo & rhs )
{
    return (lhs.name == rhs.name) && (lhs.title == rhs.title) &&
        (lhs.description == rhs.description) && (lhs.url == rhs.url);
}

bool KDUpdater::operator<( const UpdateSourceInfo & lhs, const UpdateSourceInfo & rhs )
{
    if( lhs.name != rhs.name )
        return lhs.name < rhs.name;
    else if( lhs.title != rhs.title )
        return lhs.title < rhs.title;
    else if( lhs.description != rhs.description )
        return lhs.description < rhs.description;
    else if( lhs.url != rhs.url )
        return lhs.url < rhs.url;
    else
        return false;
}
