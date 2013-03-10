cmake_minimum_required (VERSION 2.8)
project (LBANetClient)


# are we in a 64bit system?
IF(${CMAKE_SIZEOF_VOID_P} EQUAL 4)
	SET( PLATFORM_TYPE "x86" CACHE STRING "architecture")
ELSE()
	SET( PLATFORM_TYPE "x64" CACHE STRING "architecture")
ENDIF()

# What's our compiler
IF(MSVC)
	IF(MSVC80)
		SET(COMPILER_NAME "vc80" CACHE STRING "Compiler name")
	ENDIF()
	IF(MSVC90)
		SET(COMPILER_NAME "vc90" CACHE STRING "Compiler name")
	ENDIF()
	IF(MSVC10)
		SET(COMPILER_NAME "vc100" CACHE STRING "Compiler name")
	ENDIF()
	IF(NOT COMPILER_NAME)
		MESSAGE(FATAL " TOOLSET NOT SUPPORTED! Please use either vc80 or vc90 or vc10")
	ENDIF()
ELSE()
	SET(COMPILER_NAME "gcc" CACHE STRING "Compiler name")
ENDIF(MSVC)



IF(MSVC)
    SET(CMAKE_CXX_FLAGS_DEBUG "/D_DEBUG /MDd /Zi /Ob0 /Od /RTC1 /DLUABIND_DYNAMIC_LINK /D_CRT_SECURE_NO_WARNINGS /MP" CACHE STRING
        "Flags used by the compiler during debug builds." FORCE)

    SET(CMAKE_CXX_FLAGS_RELEASE "/MD /O2 /Ob2 /D NDEBUG /DLUABIND_DYNAMIC_LINK /D_CRT_SECURE_NO_WARNINGS /MP" CACHE STRING
        "Flags used by the compiler during release builds." FORCE)
        
    SET(CMAKE_CXX_FLAGS_RELWITHDEBINFO "/MD /Zi /O2 /Ob1 /D NDEBUG /DLUABIND_DYNAMIC_LINK /D_CRT_SECURE_NO_WARNINGS /MP" CACHE STRING
        "Flags used by the compiler during Release with Debug Info builds." FORCE)
        
    SET(CMAKE_EXE_LINKER_FLAGS_RELEASE "/INCREMENTAL:NO /SUBSYSTEM:WINDOWS" CACHE STRING
        "Flags for linker in release mode." FORCE)                
ENDIF(MSVC)


# The version number.
set (Tutorial_VERSION_MAJOR 1)
set (Tutorial_VERSION_MINOR 18)

set(EXECUTABLE_OUTPUT_PATH bin/${CMAKE_BUILD_TYPE})
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake_modules/")

SET(3RD_PARTY_PATH "${CMAKE_CURRENT_SOURCE_DIR}/3rd_party" CACHE PATH "3rd party directory")

#BOOST stuff
SET(Boost_USE_STATIC_LIBS ON)
SET(Boost_USE_MULTITHREADED ON)
find_path(BOOST_ROOT include/boost/foreach.hpp PATHS ${3RD_PARTY_PATH}/Boost)
SET(BOOST_LIBRARYDIR ${BOOST_ROOT}/lib/${COMPILER_NAME}/${PLATFORM_TYPE})

INCLUDE(FindBoost)
FIND_PACKAGE(Boost 1.43.0 COMPONENTS thread date_time filesystem system chrono REQUIRED)
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})

#OSG stuff
FIND_PACKAGE(OSG REQUIRED)
INCLUDE_DIRECTORIES(${OSG_INCLUDE_DIRS})

#ICE stuff
FIND_PACKAGE(ICE REQUIRED)
INCLUDE_DIRECTORIES(${ICE_INCLUDE_DIRS})

#opengl stuff
FIND_PACKAGE(OpenGL REQUIRED)

INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/infrastructure/include)
INCLUDE_DIRECTORIES(${3RD_PARTY_PATH}/recast/Recast/Include)
INCLUDE_DIRECTORIES(${3RD_PARTY_PATH}/recast/Detour/Include)
INCLUDE_DIRECTORIES(${3RD_PARTY_PATH}/recast/DetourCrowd/Include)

ADD_SUBDIRECTORY(infrastructure)
ADD_SUBDIRECTORY(shared)
ADD_SUBDIRECTORY(Client)


# create package on linux systems
if (UNIX)
ADD_SUBDIRECTORY(DistributedShared)

SET(CPACK_PACKAGE_VERSION_MAJOR "1")
SET(CPACK_PACKAGE_VERSION_MINOR "18")
SET(CPACK_GENERATOR "DEB")
SET(CPACK_DEBIAN_PACKAGE_MAINTAINER "Vivien Delage") #required
SET(CPACK_DEBIAN_PACKAGE_DEPENDS "libboost-all-dev (>= 1.48.0.2), libcegui-mk2-0.7.5 (>= 0.7.5-8), libfreetype6 (>= 2.4.8-1), libzeroc-ice34 (>= 3.4.2-4), liblua5.1-0 (>= 5.1.4-12), libluabind0.9.1 (>= 0.9.1), libopenscenegraph80 (>= 3.0.1-2), libqt4-opengl (>=4:4.8.1), libvlc5 (>= 2.0.1-4), ice34-services (>= 3.4.2-4), vlc (>= 2.0.1-4)")
INCLUDE(CPack)
ENDIF (UNIX)
	
