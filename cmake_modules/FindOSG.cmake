find_package(PkgConfig)
pkg_check_modules(OSG QUIET openscenegraph)
set(OSG_DEFINITIONS ${OSG_CFLAGS_OTHER})

find_path(OSG_INCLUDE_DIR osg/Node
          HINTS ${OSG_INCLUDEDIR} ${OSG_INCLUDE_DIRS}
          PATHS dependencies/OSG/include dependencies/OpenSceneGraph/include
          PATH_SUFFIXES osg )          
          
find_library(OSG_CORE_LIBRARY_RELEASE NAMES osg
             HINTS ${OSG_LIBDIR} ${OSG_LIBRARY_DIRS}
             PATHS dependencies/OSG/lib dependencies/OpenSceneGraph/lib )
 
find_library(OSG_UTIL_LIBRARY_RELEASE NAMES osgutil
             HINTS ${OSG_LIBDIR} ${OSG_LIBRARY_DIRS}
             PATHS dependencies/OSG/lib dependencies/OpenSceneGraph/lib ) 
 
find_library(OSG_GA_LIBRARY_RELEASE NAMES osgGA
             HINTS ${OSG_LIBDIR} ${OSG_LIBRARY_DIRS}
             PATHS dependencies/OSG/lib dependencies/OpenSceneGraph/lib )
  
find_library(OSG_VIEWER_LIBRARY_RELEASE NAMES osgViewer
             HINTS ${OSG_LIBDIR} ${OSG_LIBRARY_DIRS}
             PATHS dependencies/OSG/lib dependencies/OpenSceneGraph/lib )      
   
find_library(OSG_DB_LIBRARY_RELEASE NAMES osgDB
             HINTS ${OSG_LIBDIR} ${OSG_LIBRARY_DIRS}
             PATHS dependencies/OSG/lib dependencies/OpenSceneGraph/lib )  
   
find_library(OSG_TEXT_LIBRARY_RELEASE NAMES osgText
             HINTS ${OSG_LIBDIR} ${OSG_LIBRARY_DIRS}
             PATHS dependencies/OSG/lib dependencies/OpenSceneGraph/lib )             
   
find_library(OSG_SHADOW_LIBRARY_RELEASE NAMES osgShadow
             HINTS ${OSG_LIBDIR} ${OSG_LIBRARY_DIRS}
             PATHS dependencies/OSG/lib dependencies/OpenSceneGraph/lib )             
   
find_library(OSG_PARTICLE_LIBRARY_RELEASE NAMES osgParticle
             HINTS ${OSG_LIBDIR} ${OSG_LIBRARY_DIRS}
             PATHS dependencies/OSG/lib dependencies/OpenSceneGraph/lib )             
   
find_library(OSG_MANIPULATOR_LIBRARY_RELEASE NAMES osgManipulator
             HINTS ${OSG_LIBDIR} ${OSG_LIBRARY_DIRS}
             PATHS dependencies/OSG/lib dependencies/OpenSceneGraph/lib )              
    
find_library(OSG_AUDIO_LIBRARY_RELEASE NAMES osgAudio
             HINTS ${OSG_LIBDIR} ${OSG_LIBRARY_DIRS}
             PATHS dependencies/OSG/lib dependencies/OpenSceneGraph/lib )             
    
find_library(OSG_OPENTHREAD_LIBRARY_RELEASE NAMES OpenThreads
             HINTS ${OSG_LIBDIR} ${OSG_LIBRARY_DIRS}
             PATHS dependencies/OSG/lib dependencies/OpenSceneGraph/lib )         

             
find_library(OSG_CORE_LIBRARY_DEBUG NAMES osgd
             HINTS ${OSG_LIBDIR} ${OSG_LIBRARY_DIRS}
             PATHS dependencies/OSG/lib dependencies/OpenSceneGraph/lib )
 
find_library(OSG_UTIL_LIBRARY_DEBUG NAMES osgutild
             HINTS ${OSG_LIBDIR} ${OSG_LIBRARY_DIRS}
             PATHS dependencies/OSG/lib dependencies/OpenSceneGraph/lib ) 
 
find_library(OSG_GA_LIBRARY_DEBUG NAMES osgGAd
             HINTS ${OSG_LIBDIR} ${OSG_LIBRARY_DIRS}
             PATHS dependencies/OSG/lib dependencies/OpenSceneGraph/lib )
  
find_library(OSG_VIEWER_LIBRARY_DEBUG NAMES osgViewerd
             HINTS ${OSG_LIBDIR} ${OSG_LIBRARY_DIRS}
             PATHS dependencies/OSG/lib dependencies/OpenSceneGraph/lib )      
   
find_library(OSG_DB_LIBRARY_DEBUG NAMES osgDBd
             HINTS ${OSG_LIBDIR} ${OSG_LIBRARY_DIRS}
             PATHS dependencies/OSG/lib dependencies/OpenSceneGraph/lib )  
   
find_library(OSG_TEXT_LIBRARY_DEBUG NAMES osgTextd
             HINTS ${OSG_LIBDIR} ${OSG_LIBRARY_DIRS}
             PATHS dependencies/OSG/lib dependencies/OpenSceneGraph/lib )             
   
find_library(OSG_SHADOW_LIBRARY_DEBUG NAMES osgShadowd
             HINTS ${OSG_LIBDIR} ${OSG_LIBRARY_DIRS}
             PATHS dependencies/OSG/lib dependencies/OpenSceneGraph/lib )             
   
find_library(OSG_PARTICLE_LIBRARY_DEBUG NAMES osgParticled
             HINTS ${OSG_LIBDIR} ${OSG_LIBRARY_DIRS}
             PATHS dependencies/OSG/lib dependencies/OpenSceneGraph/lib )             
   
find_library(OSG_MANIPULATOR_LIBRARY_DEBUG NAMES osgManipulatord
             HINTS ${OSG_LIBDIR} ${OSG_LIBRARY_DIRS}
             PATHS dependencies/OSG/lib dependencies/OpenSceneGraph/lib )              
    
find_library(OSG_AUDIO_LIBRARY_DEBUG NAMES osgAudiod
             HINTS ${OSG_LIBDIR} ${OSG_LIBRARY_DIRS}
             PATHS dependencies/OSG/lib dependencies/OpenSceneGraph/lib )             
    
find_library(OSG_OPENTHREAD_LIBRARY_DEBUG NAMES OpenThreadsd
             HINTS ${OSG_LIBDIR} ${OSG_LIBRARY_DIRS}
             PATHS dependencies/OSG/lib dependencies/OpenSceneGraph/lib )    
             
# set debug libs to release if no debug libs found    
IF (${OSG_CORE_LIBRARY_RELEASE} AND NOT ${OSG_CORE_LIBRARY_DEBUG})
  SET(OSG_CORE_LIBRARY_DEBUG ${OSG_CORE_LIBRARY_RELEASE})
  SET(OSG_UTIL_LIBRARY_DEBUG ${OSG_UTIL_LIBRARY_RELEASE})
  SET(OSG_GA_LIBRARY_DEBUG ${OSG_GA_LIBRARY_RELEASE})
  SET(OSG_VIEWER_LIBRARY_DEBUG ${OSG_VIEWER_LIBRARY_RELEASE})
  SET(OSG_DB_LIBRARY_DEBUG ${OSG_DB_LIBRARY_RELEASE})
  SET(OSG_TEXT_LIBRARY_DEBUG ${OSG_TEXT_LIBRARY_RELEASE})
  SET(OSG_SHADOW_LIBRARY_DEBUG ${OSG_SHADOW_LIBRARY_RELEASE})
  SET(OSG_PARTICLE_LIBRARY_DEBUG ${OSG_PARTICLE_LIBRARY_RELEASE})
  SET(OSG_MANIPULATOR_LIBRARY_DEBUG ${OSG_MANIPULATOR_LIBRARY_RELEASE})
  SET(OSG_AUDIO_LIBRARY_DEBUG ${OSG_AUDIO_LIBRARY_RELEASE})  
  SET(OSG_OPENTHREAD_LIBRARY_DEBUG ${OSG_OPENTHREAD_LIBRARY_RELEASE})
ENDIF (${OSG_CORE_LIBRARY_RELEASE} AND NOT ${OSG_CORE_LIBRARY_DEBUG})             
          
set(OSG_LIBRARIES debug ${OSG_CORE_LIBRARY_DEBUG} debug ${OSG_UTIL_LIBRARY_DEBUG} debug ${OSG_GA_LIBRARY_DEBUG} debug ${OSG_VIEWER_LIBRARY_DEBUG} debug ${OSG_DB_LIBRARY_DEBUG} debug ${OSG_TEXT_LIBRARY_DEBUG} debug ${OSG_SHADOW_LIBRARY_DEBUG} debug ${OSG_PARTICLE_LIBRARY_DEBUG} debug ${OSG_MANIPULATOR_LIBRARY_DEBUG} debug ${OSG_AUDIO_LIBRARY_DEBUG} debug ${OSG_OPENTHREAD_LIBRARY_DEBUG}
		optimized ${OSG_CORE_LIBRARY_RELEASE} optimized ${OSG_UTIL_LIBRARY_RELEASE} optimized ${OSG_GA_LIBRARY_RELEASE} optimized ${OSG_VIEWER_LIBRARY_RELEASE} optimized ${OSG_DB_LIBRARY_RELEASE} optimized ${OSG_TEXT_LIBRARY_RELEASE} optimized ${OSG_SHADOW_LIBRARY_RELEASE} optimized ${OSG_PARTICLE_LIBRARY_RELEASE} optimized ${OSG_MANIPULATOR_LIBRARY_RELEASE} optimized ${OSG_AUDIO_LIBRARY_RELEASE} optimized ${OSG_OPENTHREAD_LIBRARY_RELEASE})

set(OSG_INCLUDE_DIRS ${OSG_INCLUDE_DIR})

include(FindPackageHandleStandardArgs)
# handle the QUIETLY and REQUIRED arguments and set OSG_FOUND to TRUE
# if all listed variables are TRUE
find_package_handle_standard_args(OSG DEFAULT_MSG
				OSG_CORE_LIBRARY_DEBUG OSG_UTIL_LIBRARY_DEBUG OSG_GA_LIBRARY_DEBUG OSG_VIEWER_LIBRARY_DEBUG OSG_DB_LIBRARY_DEBUG OSG_TEXT_LIBRARY_DEBUG OSG_SHADOW_LIBRARY_DEBUG OSG_PARTICLE_LIBRARY_DEBUG OSG_MANIPULATOR_LIBRARY_DEBUG OSG_AUDIO_LIBRARY_DEBUG OSG_OPENTHREAD_LIBRARY_DEBUG
                                  OSG_CORE_LIBRARY_RELEASE OSG_UTIL_LIBRARY_RELEASE OSG_GA_LIBRARY_RELEASE OSG_VIEWER_LIBRARY_RELEASE OSG_DB_LIBRARY_RELEASE OSG_TEXT_LIBRARY_RELEASE OSG_SHADOW_LIBRARY_RELEASE OSG_PARTICLE_LIBRARY_RELEASE OSG_MANIPULATOR_LIBRARY_RELEASE OSG_AUDIO_LIBRARY_RELEASE OSG_OPENTHREAD_LIBRARY_RELEASE
                                  OSG_INCLUDE_DIR)

mark_as_advanced(OSG_INCLUDE_DIR 
				OSG_CORE_LIBRARY_DEBUG OSG_UTIL_LIBRARY_DEBUG OSG_GA_LIBRARY_DEBUG OSG_VIEWER_LIBRARY_DEBUG OSG_DB_LIBRARY_DEBUG OSG_TEXT_LIBRARY_DEBUG OSG_SHADOW_LIBRARY_DEBUG OSG_PARTICLE_LIBRARY_DEBUG OSG_MANIPULATOR_LIBRARY_DEBUG OSG_AUDIO_LIBRARY_DEBUG OSG_OPENTHREAD_LIBRARY_DEBUG
                                  OSG_CORE_LIBRARY_RELEASE OSG_UTIL_LIBRARY_RELEASE OSG_GA_LIBRARY_RELEASE OSG_VIEWER_LIBRARY_RELEASE OSG_DB_LIBRARY_RELEASE OSG_TEXT_LIBRARY_RELEASE OSG_SHADOW_LIBRARY_RELEASE OSG_PARTICLE_LIBRARY_RELEASE OSG_MANIPULATOR_LIBRARY_RELEASE OSG_AUDIO_LIBRARY_RELEASE OSG_OPENTHREAD_LIBRARY_RELEASE )