find_package(PkgConfig)
pkg_check_modules(VLC QUIET vlc)
set(VLC_DEFINITIONS ${VLC_CFLAGS_OTHER})
             
             
find_path(VLC_INCLUDE_DIR vlc/vlc.h
          HINTS ${VLC_INCLUDEDIR} ${VLC_INCLUDE_DIRS}
          PATHS ${3RD_PARTY_PATH}/VLC/include
		    /usr/include
		    /usr/local/include)

find_library(VLC_CORE_LIBRARY_RELEASE NAMES vlc libvlc
             HINTS ${VLC_LIBDIR} ${VLC_LIBRARY_DIRS}
             PATHS ${3RD_PARTY_PATH}/VLC/lib
		/usr/lib
		/usr/local/lib)      
                            
            
set(VLC_LIBRARIES ${VLC_CORE_LIBRARY_RELEASE})

set(VLC_INCLUDE_DIRS ${VLC_INCLUDE_DIR})
		
		
include(FindPackageHandleStandardArgs)
# handle the QUIETLY and REQUIRED arguments and set VLC_FOUND to TRUE
# if all listed variables are TRUE
find_package_handle_standard_args(VLC DEFAULT_MSG
				VLC_CORE_LIBRARY_RELEASE
                                  VLC_INCLUDE_DIR)

mark_as_advanced(VLC DEFAULT_MSG
			VLC_CORE_LIBRARY_RELEASE
			VLC_INCLUDE_DIR )