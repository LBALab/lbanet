find_package(PkgConfig)
pkg_check_modules(PHYSX QUIET physx-2.8.3_3)
set(PHYSX_DEFINITIONS ${PHYSX_CFLAGS_OTHER})

find_path(PHYSX_INCLUDE_DIR Foundation/include/NxFoundation.h
          HINTS ${PHYSX_INCLUDEDIR} ${PHYSX_INCLUDE_DIRS}
             PATHS ${3RD_PARTY_PATH}/PhysX/include
    		/usr/include/PhysX/v2.8.3/SDKs
    		/usr/local/include/PhysX/v2.8.3/SDKs)

find_library(PHYSX_CORE_LIBRARY NAMES PhysXCore
             HINTS ${PHYSX_LIBDIR} ${PHYSX_LIBRARY_DIRS}
             ${3RD_PARTY_PATH}/PhysX/lib/${COMPILER_NAME}/${PLATFORM_TYPE}
	    /usr/lib/PhysX/v2.8.3
	    /usr/local/lib/PhysX/v2.8.3)

 find_library(PHYSX_COOKING_LIBRARY NAMES PhysXCooking NxCooking
             HINTS ${PHYSX_LIBDIR} ${PHYSX_LIBRARY_DIRS}
             PATHS ${3RD_PARTY_PATH}/PhysX/lib/${COMPILER_NAME}/${PLATFORM_TYPE}
	    /usr/lib/PhysX/v2.8.3
	    /usr/local/lib/PhysX/v2.8.3)

 find_library(PHYSX_LOADER_LIBRARY NAMES PhysXLoader
             HINTS ${PHYSX_LIBDIR} ${PHYSX_LIBRARY_DIRS}
             PATHS ${3RD_PARTY_PATH}/PhysX/lib/${COMPILER_NAME}/${PLATFORM_TYPE}
	    /usr/lib/PhysX/v2.8.3
	    /usr/local/lib/PhysX/v2.8.3)
	    
 find_library(PHYSX_CHARACTER_LIBRARY NAMES NxCharacter
             HINTS ${PHYSX_LIBDIR} ${PHYSX_LIBRARY_DIRS}
             PATHS ${3RD_PARTY_PATH}/PhysX/lib/${COMPILER_NAME}/${PLATFORM_TYPE}
	    /usr/lib/PhysX/v2.8.3
	    /usr/local/lib/PhysX/v2.8.3)
	    
	    
	    
	    
set(PHYSX_LIBRARIES ${PHYSX_CORE_LIBRARY} ${PHYSX_COOKING_LIBRARY} ${PHYSX_LOADER_LIBRARY} ${PHYSX_CHARACTER_LIBRARY})

set(PHYSX_INCLUDE_DIRS ${PHYSX_INCLUDE_DIR}/Foundation/include ${PHYSX_INCLUDE_DIR}/Physics/include ${PHYSX_INCLUDE_DIR}/Cooking/include ${PHYSX_INCLUDE_DIR}/PhysXLoader/include ${PHYSX_INCLUDE_DIR}/NxCharacter/include ${PHYSX_INCLUDE_DIR}/../Tools/NxuStream2)

include(FindPackageHandleStandardArgs)
# handle the QUIETLY and REQUIRED arguments and set PHYSX_FOUND to TRUE
# if all listed variables are TRUE
find_package_handle_standard_args(PHYSX DEFAULT_MSG
				PHYSX_CORE_LIBRARY PHYSX_COOKING_LIBRARY PHYSX_LOADER_LIBRARY PHYSX_CHARACTER_LIBRARY
                                  PHYSX_INCLUDE_DIR)

mark_as_advanced(PHYSX_INCLUDE_DIR PHYSX_CORE_LIBRARY PHYSX_COOKING_LIBRARY PHYSX_LOADER_LIBRARY PHYSX_CHARACTER_LIBRARY)