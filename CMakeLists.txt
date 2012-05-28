cmake_minimum_required (VERSION 2.8)
project (LBANetClient)

# The version number.
set (Tutorial_VERSION_MAJOR 1)
set (Tutorial_VERSION_MINOR 18)

set(EXECUTABLE_OUTPUT_PATH bin/${CMAKE_BUILD_TYPE})
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake_modules/")

#BOOST stuff
SET(Boost_USE_STATIC_LIBS ON)
SET(Boost_USE_MULTITHREADED ON)
find_path(BOOST_ROOT include/boost/foreach.hpp
          PATHS dependencies/3rdParty)
INCLUDE(FindBoost)
FIND_PACKAGE(Boost 1.43.0 COMPONENTS thread date_time filesystem system REQUIRED)
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})

#OSG stuff
FIND_PACKAGE(OSG REQUIRED)
INCLUDE_DIRECTORIES(${OSG_INCLUDE_DIRS})

#ICE stuff
FIND_PACKAGE(ICE REQUIRED)
INCLUDE_DIRECTORIES(${ICE_INCLUDE_DIRS})


INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/infrastructure/include)
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/dependencies/recast/Recast/Include)
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/dependencies/recast/Detour/Include)
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/dependencies/recast/DetourCrowd/Include)

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
SET(CPACK_DEBIAN_PACKAGE_DEPENDS "libboost-all-dev (>= 1.48.0.2), libcegui-mk2-0.7.5 (>= 0.7.5-8), libfreetype6 (>= 2.4.8-1), libzeroc-ice34 (>= 3.4.2-4), liblua5.1-0 (>= 5.1.4-12), libluabind0.9.1 (>= 0.9.1), libopenscenegraph80 (>= 3.0.1-2), libqt4-opengl (>=4:4.8.1), libvlc5 (>= 2.0.1-4), ice34-services (>= 3.4.2-4)")
INCLUDE(CPack)
ENDIF (UNIX)
	
