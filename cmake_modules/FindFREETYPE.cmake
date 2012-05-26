find_package(PkgConfig)
pkg_check_modules(FREETYPE QUIET freetype)
set(FREETYPE_DEFINITIONS ${FREETYPE_CFLAGS_OTHER})
             
             
find_path(FREETYPE_INCLUDE_DIR freetype/freetype.h
          HINTS ${FREETYPE_INCLUDEDIR} ${FREETYPE_INCLUDE_DIRS}
          PATHS $ENV{FREETYPE_HOME}/include
          	../dependencies/3rdParty/include
		    /usr/include
		    /usr/local/include)

find_library(FREETYPE_CORE_LIBRARY_RELEASE NAMES freetype244
             HINTS ${FREETYPE_LIBDIR} ${FREETYPE_LIBRARY_DIRS}
             PATHS $ENV{FREETYPE_HOME}/lib
		../dependencies/3rdParty/lib
		/usr/lib
		/usr/local/lib)
              
             
find_library(FREETYPE_CORE_LIBRARY_DEBUG NAMES freetype244d
             HINTS ${FREETYPE_LIBDIR} ${FREETYPE_LIBRARY_DIRS}
             PATHS $ENV{FREETYPE_HOME}/include
		../dependencies/3rdParty/lib
		/usr/lib
		/usr/local/lib)         
                            
            
set(FREETYPE_LIBRARIES debug ${FREETYPE_CORE_LIBRARY_DEBUG}
		optimized ${FREETYPE_CORE_LIBRARY_RELEASE})

set(FREETYPE_INCLUDE_DIRS ${FREETYPE_INCLUDE_DIR})
		
		
include(FindPackageHandleStandardArgs)
# handle the QUIETLY and REQUIRED arguments and set FREETYPE_FOUND to TRUE
# if all listed variables are TRUE
find_package_handle_standard_args(FREETYPE DEFAULT_MSG
				FREETYPE_CORE_LIBRARY_DEBUG
                                  FREETYPE_CORE_LIBRARY_RELEASE
                                  FREETYPE_INCLUDE_DIR)

mark_as_advanced(FREETYPE DEFAULT_MSG
			FREETYPE_CORE_LIBRARY_DEBUG
			FREETYPE_CORE_LIBRARY_RELEASE
			FREETYPE_INCLUDE_DIR )

