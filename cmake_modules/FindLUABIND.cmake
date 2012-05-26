find_package(PkgConfig)
pkg_check_modules(LUABIND QUIET luabind)
set(LUABIND_DEFINITIONS ${LUABIND_CFLAGS_OTHER})
             
             
find_path(LUABIND_INCLUDE_DIR luabind/version.hpp
          HINTS ${LUABIND_INCLUDEDIR} ${LUABIND_INCLUDE_DIRS}
          PATHS $ENV{LUABIND_HOME}/include
          	../dependencies/luabind/include
		    /usr/include
		    /usr/local/include)

find_library(LUABIND_CORE_LIBRARY_RELEASE NAMES luabind
             HINTS ${LUABIND_LIBDIR} ${LUABIND_LIBRARY_DIRS}
             PATHS $ENV{CEGUI_HOME}/lib
		../dependencies/luabind/lib
		/usr/lib
		/usr/local/lib)
              
             
find_library(LUABIND_CORE_LIBRARY_DEBUG NAMES luabindd
             HINTS ${LUABIND_LIBDIR} ${LUABIND_LIBRARY_DIRS}
             PATHS $ENV{LUA_HOME}/include
		../dependencies/luabind/lib
		/usr/lib
		/usr/local/lib)         
                            
            
set(LUABIND_LIBRARIES debug ${LUABIND_CORE_LIBRARY_DEBUG}
		optimized ${LUABIND_CORE_LIBRARY_RELEASE})

set(LUABIND_INCLUDE_DIRS ${LUABIND_INCLUDE_DIR})
		
		
include(FindPackageHandleStandardArgs)
# handle the QUIETLY and REQUIRED arguments and set CEGUI_FOUND to TRUE
# if all listed variables are TRUE
find_package_handle_standard_args(LUABIND DEFAULT_MSG
				LUABIND_CORE_LIBRARY_DEBUG
                                  LUABIND_CORE_LIBRARY_RELEASE
                                  LUABIND_INCLUDE_DIR)

mark_as_advanced(LUABIND DEFAULT_MSG
			LUABIND_CORE_LIBRARY_DEBUG
			LUABIND_CORE_LIBRARY_RELEASE
			LUABIND_INCLUDE_DIR )