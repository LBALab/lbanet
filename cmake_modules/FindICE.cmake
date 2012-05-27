find_package(PkgConfig)
pkg_check_modules(ICE QUIET zeroc-ice34)
set(ICE_DEFINITIONS ${ICE_CFLAGS_OTHER})

find_path(ICE_INCLUDE_DIR Ice/Ice.h
          HINTS ${ICE_INCLUDEDIR} ${ICE_INCLUDE_DIRS}
          PATHS $ENV{ICE_HOME}/include
          PATH_SUFFIXES Ice )

find_library(ICE_CORE_LIBRARY_RELEASE NAMES ice
             HINTS ${ICE_LIBDIR} ${ICE_LIBRARY_DIRS}
             PATHS $ENV{ICE_HOME}/lib
		/usr/lib
		/usr/local/lib)
              
find_library(ICE_UTIL_LIBRARY_RELEASE NAMES iceutil
             HINTS ${ICE_LIBDIR} ${ICE_LIBRARY_DIRS}
             PATHS $ENV{ICE_HOME}/lib
		/usr/lib
		/usr/local/lib)               
               
find_library(ICE_GLACIER_LIBRARY_RELEASE NAMES glacier2
             HINTS ${ICE_LIBDIR} ${ICE_LIBRARY_DIRS}
             PATHS $ENV{ICE_HOME}/lib
		/usr/lib
		/usr/local/lib)   
               
find_library(ICE_PATCH_LIBRARY_RELEASE NAMES icepatch2
             HINTS ${ICE_LIBDIR} ${ICE_LIBRARY_DIRS}
             PATHS $ENV{ICE_HOME}/lib
		/usr/lib
		/usr/local/lib)   
             
find_library(ICE_CORE_LIBRARY_DEBUG NAMES iced
             HINTS ${ICE_LIBDIR} ${ICE_LIBRARY_DIRS}
             PATHS $ENV{ICE_HOME}/lib
		/usr/lib
		/usr/local/lib)
              
find_library(ICE_UTIL_LIBRARY_DEBUG NAMES iceutild
             HINTS ${ICE_LIBDIR} ${ICE_LIBRARY_DIRS}
             PATHS $ENV{ICE_HOME}/lib
		/usr/lib
		/usr/local/lib)               
               
find_library(ICE_GLACIER_LIBRARY_DEBUG NAMES glacier2d
             HINTS ${ICE_LIBDIR} ${ICE_LIBRARY_DIRS}
             PATHS $ENV{ICE_HOME}/lib
		/usr/lib
		/usr/local/lib)   
               
find_library(ICE_PATCH_LIBRARY_DEBUG NAMES icepatch2d
             HINTS ${ICE_LIBDIR} ${ICE_LIBRARY_DIRS}
             PATHS $ENV{ICE_HOME}/lib
		/usr/lib
		/usr/local/lib)        
     
             
# set debug libs to release if no debug libs found    
IF (ICE_CORE_LIBRARY_RELEASE AND NOT ICE_CORE_LIBRARY_DEBUG)
  SET(ICE_CORE_LIBRARY_DEBUG ${ICE_CORE_LIBRARY_RELEASE})
  SET(ICE_UTIL_LIBRARY_DEBUG ${ICE_UTIL_LIBRARY_RELEASE})
  SET(ICE_GLACIER_LIBRARY_DEBUG ${ICE_GLACIER_LIBRARY_RELEASE})
  SET(ICE_PATCH_LIBRARY_DEBUG ${ICE_PATCH_LIBRARY_RELEASE})
ENDIF (ICE_CORE_LIBRARY_RELEASE AND NOT ICE_CORE_LIBRARY_DEBUG)      
     
     
     
     
set(ICE_LIBRARIES debug ${ICE_CORE_LIBRARY_DEBUG} debug ${ICE_UTIL_LIBRARY_DEBUG} debug ${ICE_GLACIER_LIBRARY_DEBUG} debug ${ICE_PATCH_LIBRARY_DEBUG}
		optimized ${ICE_CORE_LIBRARY_RELEASE} optimized ${ICE_UTIL_LIBRARY_RELEASE} optimized ${ICE_GLACIER_LIBRARY_RELEASE} optimized ${ICE_PATCH_LIBRARY_RELEASE})

set(ICE_INCLUDE_DIRS ${ICE_INCLUDE_DIR})
		
		
include(FindPackageHandleStandardArgs)
# handle the QUIETLY and REQUIRED arguments and set ZEROC_ICE_FOUND to TRUE
# if all listed variables are TRUE
find_package_handle_standard_args(ICE DEFAULT_MSG
				ICE_CORE_LIBRARY_DEBUG ICE_UTIL_LIBRARY_DEBUG ICE_GLACIER_LIBRARY_DEBUG ICE_PATCH_LIBRARY_DEBUG
                                  ICE_CORE_LIBRARY_RELEASE ICE_UTIL_LIBRARY_RELEASE ICE_GLACIER_LIBRARY_RELEASE ICE_PATCH_LIBRARY_RELEASE 
                                  ICE_INCLUDE_DIR)

mark_as_advanced(ICE_INCLUDE_DIR ICE_CORE_LIBRARY_DEBUG ICE_UTIL_LIBRARY_DEBUG ICE_GLACIER_LIBRARY_DEBUG ICE_PATCH_LIBRARY_DEBUG
                                  ICE_CORE_LIBRARY_RELEASE ICE_UTIL_LIBRARY_RELEASE ICE_GLACIER_LIBRARY_RELEASE ICE_PATCH_LIBRARY_RELEASE )