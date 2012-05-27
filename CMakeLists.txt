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
	
