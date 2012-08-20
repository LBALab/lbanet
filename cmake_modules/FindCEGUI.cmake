find_package(PkgConfig)
pkg_check_modules(CEGUI QUIET cegui-mk2-0.7.5)
set(CEGUI_DEFINITIONS ${CEGUI_CFLAGS_OTHER})


find_path(CEGUI_INCLUDE_DIR CEGUIBase.h
          HINTS ${CEGUI_INCLUDEDIR} ${CEGUI_INCLUDE_DIRS}
          PATHS $ENV{CEGUI_HOME}/include
          	${3RD_PARTY_PATH}/CEGUI/include
		    /usr/include/CEGUI
		    /usr/local/include/CEGUI)

find_library(CEGUI_CORE_LIBRARY_RELEASE NAMES CEGUIBase
             HINTS ${CEGUI_LIBDIR} ${CEGUI_LIBRARY_DIRS}
             PATHS $ENV{CEGUI_HOME}/lib
		${3RD_PARTY_PATH}/CEGUI/lib
		/usr/lib
		/usr/local/lib)
              
find_library(CEGUI_OPENGL_LIBRARY_RELEASE NAMES CEGUIOpenGLRenderer
             HINTS ${CEGUI_LIBDIR} ${CEGUI_LIBRARY_DIRS}
             PATHS $ENV{CEGUI_HOME}/lib
		${3RD_PARTY_PATH}/CEGUI/lib
		/usr/lib
		/usr/local/lib)         
		
              
find_library(CEGUI_CORE_LIBRARY_DEBUG NAMES CEGUIBase_d
             HINTS ${CEGUI_LIBDIR} ${CEGUI_LIBRARY_DIRS}
             PATHS $ENV{CEGUI_HOME}/include
		${3RD_PARTY_PATH}/CEGUI/lib
		/usr/lib
		/usr/local/lib)         
                
find_library(CEGUI_OPENGL_LIBRARY_DEBUG NAMES CEGUIOpenGLRenderer_d
             HINTS ${CEGUI_LIBDIR} ${CEGUI_LIBRARY_DIRS}
             PATHS $ENV{CEGUI_HOME}/lib
		${3RD_PARTY_PATH}/CEGUI/lib
		/usr/lib
		/usr/local/lib)                   

             
# set debug libs to release if no debug libs found    
IF (CEGUI_CORE_LIBRARY_RELEASE AND NOT CEGUI_CORE_LIBRARY_DEBUG)
  SET(CEGUI_CORE_LIBRARY_DEBUG ${CEGUI_CORE_LIBRARY_RELEASE})
  SET(CEGUI_OPENGL_LIBRARY_DEBUG ${CEGUI_OPENGL_LIBRARY_RELEASE})
ENDIF (CEGUI_CORE_LIBRARY_RELEASE AND NOT CEGUI_CORE_LIBRARY_DEBUG)   

            
set(CEGUI_LIBRARIES debug ${CEGUI_CORE_LIBRARY_DEBUG} debug ${CEGUI_OPENGL_LIBRARY_DEBUG}
		optimized ${CEGUI_CORE_LIBRARY_RELEASE} optimized ${CEGUI_OPENGL_LIBRARY_RELEASE})

set(CEGUI_INCLUDE_DIRS ${CEGUI_INCLUDE_DIR})
		
		
include(FindPackageHandleStandardArgs)
# handle the QUIETLY and REQUIRED arguments and set CEGUI_FOUND to TRUE
# if all listed variables are TRUE
find_package_handle_standard_args(CEGUI DEFAULT_MSG
				CEGUI_CORE_LIBRARY_DEBUG CEGUI_OPENGL_LIBRARY_DEBUG
                                  CEGUI_CORE_LIBRARY_RELEASE CEGUI_OPENGL_LIBRARY_RELEASE 
                                  CEGUI_INCLUDE_DIR)

mark_as_advanced(CEGUI_INCLUDE_DIR CEGUI_CORE_LIBRARY_DEBUG CEGUI_OPENGL_LIBRARY_DEBUG
                                  CEGUI_CORE_LIBRARY_RELEASE CEGUI_OPENGL_LIBRARY_RELEASE )

