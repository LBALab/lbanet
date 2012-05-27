find_package(PkgConfig)
pkg_check_modules(FMOD QUIET luabind)
set(LUABIND_DEFINITIONS ${FMOD_CFLAGS_OTHER})
             
             
find_path(FMOD_INCLUDE_DIR fmod.h
          HINTS ${FMOD_INCLUDEDIR} ${FMOD_INCLUDE_DIRS}
          PATHS $ENV{LUABIND_HOME}/include
		    /usr/include/fmodex
		    /usr/local/include/fmodex
		    ../dependencies/fmod/include)

find_library(FMOD_CORE_LIBRARY_RELEASE NAMES fmodex_vc fmodex fmodex-4.40.06
             HINTS ${FMOD_LIBDIR} ${FMOD_LIBRARY_DIRS}
             PATHS $ENV{FMOD_HOME}/lib
             	/usr/lib
		/usr/local/lib
		../dependencies/fmod/lib)
                    
                            
            
set(FMOD_LIBRARIES ${FMOD_CORE_LIBRARY_RELEASE})

set(FMOD_INCLUDE_DIRS ${FMOD_INCLUDE_DIR})
		
		
include(FindPackageHandleStandardArgs)
# handle the QUIETLY and REQUIRED arguments and set FMOD_FOUND to TRUE
# if all listed variables are TRUE
find_package_handle_standard_args(FMOD DEFAULT_MSG
				FMOD_CORE_LIBRARY_RELEASE
                                  FMOD_INCLUDE_DIR)

mark_as_advanced(FMOD DEFAULT_MSG
			FMOD_CORE_LIBRARY_RELEASE
                        FMOD_INCLUDE_DIR )