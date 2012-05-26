find_package(PkgConfig)
pkg_check_modules(LUA QUIET lua5.1)
set(LUA_DEFINITIONS ${LUA_CFLAGS_OTHER})
             
             
find_path(LUA_INCLUDE_DIR lua.h
          HINTS ${LUA_INCLUDEDIR} ${LUA_INCLUDE_DIRS}
          PATHS $ENV{LUA_HOME}/include
          	../dependencies/LUA/include
		    /usr/include
		    /usr/local/include)

find_library(LUA_CORE_LIBRARY_RELEASE NAMES lua51
             HINTS ${LUA_LIBDIR} ${LUA_LIBRARY_DIRS}
             PATHS $ENV{LUA_HOME}/lib
		../dependencies/LUA/lib
		/usr/lib
		/usr/local/lib)
              
             
find_library(LUA_CORE_LIBRARY_DEBUG NAMES lua51d
             HINTS ${LUA_LIBDIR} ${LUA_LIBRARY_DIRS}
             PATHS $ENV{LUA_HOME}/include
		../dependencies/LUA/lib
		/usr/lib
		/usr/local/lib)         
                            
            
set(LUA_LIBRARIES debug ${LUA_CORE_LIBRARY_DEBUG}
		optimized ${LUA_CORE_LIBRARY_RELEASE})

set(LUA_INCLUDE_DIRS ${LUA_INCLUDE_DIR})
		
		
include(FindPackageHandleStandardArgs)
# handle the QUIETLY and REQUIRED arguments and set CEGUI_FOUND to TRUE
# if all listed variables are TRUE
find_package_handle_standard_args(LUA DEFAULT_MSG
				LUA_CORE_LIBRARY_DEBUG
                                  LUA_CORE_LIBRARY_RELEASE
                                  LUA_INCLUDE_DIR)

mark_as_advanced(LUA DEFAULT_MSG
			LUA_CORE_LIBRARY_DEBUG
			LUA_CORE_LIBRARY_RELEASE
			LUA_INCLUDE_DIR )