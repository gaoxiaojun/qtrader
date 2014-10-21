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

#ifndef __KDTOOLS_KDUPDATERUPDATEOPERATIONFACTORY_H__
#define __KDTOOLS_KDUPDATERUPDATEOPERATIONFACTORY_H__

#include <KDToolsCore/kdgenericfactory.h>

#include "kdupdater.h"
#include <KDToolsCore/pimpl_ptr.h>

namespace KDUpdater
{
    class Target;
    class UpdateOperation;
    
    typedef KDGenericFactory< UpdateOperation >::FactoryFunction UpdateOperationFactoryFunction;

    class KDTOOLS_UPDATER_EXPORT UpdateOperationFactory : public KDGenericFactory< UpdateOperation >
    {
        KDAB_DISABLE_COPY( UpdateOperationFactory );
    public:
        static UpdateOperationFactory& instance();
        ~UpdateOperationFactory();

        UpdateOperation * create( const QString & name, const QStringList & arguments, Target * target ) const;

        template< class T >
        void registerUpdateOperation( const QString& name )
        {
            registerProduct< T >( name );
        }
        void registerUpdateOperationFactory( const QString& name, UpdateOperationFactoryFunction create  );
        
        void unregisterUpdateOperation( const QString& name );

        int updateOperationCount() const;
        QStringList availableUpdateOperations() const;

    protected:
        UpdateOperationFactory();

    private:
        class Private;
        kdtools::pimpl_ptr< Private > d;
    };
}

#endif
