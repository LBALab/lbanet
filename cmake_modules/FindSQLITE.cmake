find_package(PkgConfig)
pkg_check_modules(SQLITE QUIET sqlite)
set(SQLITE_DEFINITIONS ${SQLITE_CFLAGS_OTHER})

find_path(SQLITE_INCLUDE_DIR sqlite3.h
	PATHS ${3RD_PARTY_PATH}/sqlite/include
		/usr/include
		/usr/local/include)

find_library(SQLITE_CORE_LIBRARY_RELEASE NAMES sqlite3 libsqlite3
	HINTS ${SQLITE_LIBDIR} ${SQLITE_LIBRARY_DIRS}
	PATHS ${3RD_PARTY_PATH}/sqlite/lib/${COMPILER_NAME}/${PLATFORM_TYPE}
		/usr/lib
		/usr/local/lib)

set(SQLITE_LIBRARIES ${SQLITE_CORE_LIBRARY_RELEASE})

set(SQLITE_INCLUDE_DIRS ${SQLITE_INCLUDE_DIR})
		
		
include(FindPackageHandleStandardArgs)
# handle the QUIETLY and REQUIRED arguments and set SQLITE_FOUND to TRUE
# if all listed variables are TRUE
find_package_handle_standard_args(SQLITE DEFAULT_MSG
	SQLITE_CORE_LIBRARY_RELEASE
	SQLITE_INCLUDE_DIR)

mark_as_advanced(SQLITE DEFAULT_MSG
	SQLITE_CORE_LIBRARY_RELEASE
	SQLITE_INCLUDE_DIR)