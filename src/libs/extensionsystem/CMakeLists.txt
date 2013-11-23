set(library_name extensionsystem)

project( ${library_name} )

cmake_minimum_required( VERSION 2.8.9 )

set( LIB_SRC_FILES
     aggregate.h
     aggregate.cpp
     invoker.cpp
     optionsparser.cpp	
     plugindetailsview.cpp	
     pluginerrorview.cpp	
     pluginspec.cpp
     iplugin.cpp		
     plugincollection.cpp	
     pluginerroroverview.cpp	
     pluginmanager.cpp	
     pluginview.cpp 
     iplugin.h 
     plugindetailsview.h    
     pluginerrorview.h  
     pluginmanager_p.h  
     pluginspec_p.h
     pluginerroroverview.h  
     pluginmanager.h    
     pluginview.h
)

file (GLOB LIB_UI_FILES  RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} [^.]*.ui)
file (GLOB LIB_QRC_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} [^.]*.qrc)

set(LIB_EXPORT_DIRECTIVE "EXTENSIONSYSTEM_EXPORT")

set(LIB_DEPEND_LIBS QtCore QtWidgets)

MacroBuildLib(
    NAME ${library_name}
    EXPORT_DIRECTIVE ${LIB_EXPORT_DIRECTIVE}
    SRC_FILES ${LIB_SRC_FILES}
    UI_FILES ${LIB_UI_FILES}
    QRC_FILES ${LIB_QRC_FILES}
    DEPEND_LIBS ${LIB_DEPEND_LIBS}
    INCLUDE_DIRECTORIES ${PROJECT_LIBS_INCLUDE_DIR}
)
