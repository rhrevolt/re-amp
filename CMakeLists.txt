#
# -------------------
# Re-Amp Project
# Re-Amp Build System
# -------------------
#

cmake_minimum_required(VERSION 2.6)
### PROJECT VARIABLES ###
project(ReAmp)
set(PRODUCT_NAME "ReAmp")
set(PRODUCT_VERSION_MAJOR 0)
set(PRODUCT_VERSION_MINOR 1)
set(PRODUCT_VERSION_TYPE "git")
set(PRODUCT_VERSION_STRING "${PRODUCT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}-${PRODUCT_VERSION_TYPE}")
set(PRODUCT_STRING "${PRODUCT_NAME} v${PRODUCT_VERSION_STRING}")

###############################
###### PLATFORM VARIABLE ######
###############################
if(WIN32)
	if (MSVC)
		message("WARNING: reamp has not been tested to build with MSVC. MINGW is the only supported compiler on Win32")
	endif(MSVC)
	set(REAMP_PLATFORM "WIN32")
endif(WIN32)

if(UNIX)
	set(REAMP_PLATFORM "LINUX")
endif(UNIX)

#####################################
###### CONFIGURATION VARIABLES ######
#####################################
set(PROJECT_EXEC "reamp")
set(RESOURCES_PATH "cfg/resources.cfg")
set(PLUGINS_PATH "cfg/plugins.cfg-${REAMP_PLATFORM}")
set(REQUIRED_OGRE_VERSION_NUMBER 1.7)
set(REQUIRED_OGRE_VERSION_NAME "Cthugha")

if(WIN32)
	set(CMAKE_MODULE_PATH "$ENV{OGRE_HOME}/CMake/;${CMAKE_MODULE_PATH}")
	set(OGRE_SAMPLES_INCLUDEPATH
		$ENV{OGRE_HOME}/Samples/include
	)
endif(WIN32)

if(UNIX)
	set(CMAKE_MODULE_PATH "/usr/lib/OGRE/cmake/;${CMAKE_MODULE_PATH}")
	set(OGRE_SAMPLES_INCLUDEPATH
		/usr/local/share/OGRE/samples/Common/include/
	)
endif(UNIX)


if (CMAKE_BUILD_TYPE STREQUAL "")
	# Set the default build type to Release w/ Debug info
	set(CMAKE_BUILD_TYPE "RelWithDebInfo" CACHE STRING "Choose the type of build, options are: None (CMAKE_CXX_FLAGS or CMAKE_C_FLAGS used) Debug Release RelWithDebInfo MinSizeRel." FORCE)
endif ()

set(CMAKE_DEBUG_POSTFIX "_d")

set(CMAKE_INSTALL_PREFIX "${CMAKE_CURRENT_BINARY_DIR}/dist")

## C++/headers location
set(SOURCE_DIR ${CMAKE_SOURCE_DIR}/src)
set(HEADER_DIR ${CMAKE_SOURCE_DIR}/include)

include_directories(${HEADER_DIR})

FILE(GLOB HDRS ${HEADER_DIR}/*.h)

FILE(GLOB SRCS ${SOURCE_DIR}/*.cpp)

###################################
###### REQUIRED DEPENDENCIES ######
###################################

# Find OGRE and check for 1.7
find_package(OGRE REQUIRED)

if(NOT "${OGRE_VERSION_NAME}" STREQUAL ${REQUIRED_OGRE_VERSION_NAME})
  message(SEND_ERROR "Failed to find OGRE '${REQUIRED_OGRE_VERSION_NAME}'.")
endif()

# Find OIS 
find_package(OIS REQUIRED)

if(NOT OIS_FOUND)
	message(SEND_ERROR "Failed to find OIS.")
endif()

# Find Boost
if (NOT OGRE_BUILD_PLATFORM_IPHONE)
	if (WIN32 OR APPLE)
		set(Boost_USE_STATIC_LIBS TRUE)
	else ()
		# Statically linking boost to a dynamic Ogre build doesn't work on Linux 64bit
		set(Boost_USE_STATIC_LIBS ${OGRE_STATIC})
	endif ()
	if (MINGW)
		# this is probably a bug in CMake: the boost find module tries to look for
		# boost libraries with name libboost_*, but CMake already prefixes library
		# search names with "lib". This is the workaround.
		set(CMAKE_FIND_LIBRARY_PREFIXES ${CMAKE_FIND_LIBRARY_PREFIXES} "")
	endif ()
	set(Boost_ADDITIONAL_VERSIONS "1.44" "1.44.0" "1.42" "1.42.0" "1.41.0" "1.41" "1.40.0" "1.40" "1.39.0" "1.39" "1.38.0" "1.38" "1.37.0" "1.37" )
	# Components that need linking (NB does not include header-only components like bind)
	set(OGRE_BOOST_COMPONENTS thread date_time)
	find_package(Boost COMPONENTS ${OGRE_BOOST_COMPONENTS} QUIET)
	if (NOT Boost_FOUND)
		# Try again with the other type of libs
		set(Boost_USE_STATIC_LIBS NOT ${Boost_USE_STATIC_LIBS})
		find_package(Boost COMPONENTS ${OGRE_BOOST_COMPONENTS} QUIET)
	endif()
	find_package(Boost QUIET)

    # Set up referencing of Boost
	include_directories(${Boost_INCLUDE_DIR})
	add_definitions(-DBOOST_ALL_NO_LIB)
	set(OGRE_LIBRARIES ${OGRE_LIBRARIES} ${Boost_LIBRARIES})
endif()

##################
## BUILD TARGET ##
##################

include_directories( ${OIS_INCLUDE_DIRS}
	${OGRE_INCLUDE_DIRS}
	${OGRE_SAMPLES_INCLUDEPATH}
)

add_executable(${PROJECT_EXEC} WIN32 ${SRCS})

set_target_properties(${PROJECT_EXEC} PROPERTIES DEBUG_POSTFIX _d)

target_link_libraries(${PROJECT_EXEC} ${OGRE_LIBRARIES} ${OIS_LIBRARIES})

file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/dist/bin)
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/dist/media)

if(MINGW OR UNIX)
	set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/dist/bin)
endif(MINGW OR UNIX)

###############################
####### "install" TARGET ######
###############################

install(TARGETS ${PROJECT_EXEC}
	RUNTIME DESTINATION bin
	CONFIGURATIONS All)

install(DIRECTORY ${CMAKE_SOURCE_DIR}/build/dist/media
	DESTINATION ./
	CONFIGURATIONS Release RelWithDebInfo Debug
)

install(FILES ${CMAKE_SOURCE_DIR}/${PLUGINS_PATH}
	DESTINATION bin
	CONFIGURATIONS Release RelWithDebInfo Debug
	RENAME plugins.cfg
)

install(FILES ${CMAKE_SOURCE_DIR}/${RESOURCES_PATH}
	DESTINATION bin
	CONFIGURATIONS Release RelWithDebInfo Debug
	RENAME resources.cfg
)

if(WIN32)
	################################################
	## Copy some libraries required for Windows. ###
	## Ogre, render plugins, BOOST, and OIS      ###
	################################################
	install(FILES ${OGRE_PLUGIN_DIR_REL}/OgreMain.dll
		${OGRE_PLUGIN_DIR_REL}/RenderSystem_Direct3D9.dll
		${OGRE_PLUGIN_DIR_REL}/RenderSystem_GL.dll
		${OGRE_PLUGIN_DIR_REL}/libOIS.dll
		DESTINATION bin
		CONFIGURATIONS Release RelWithDebInfo
	)

	# Debug DLLs
	install(FILES ${OGRE_PLUGIN_DIR_DBG}/OgreMain_d.dll
		${OGRE_PLUGIN_DIR_DBG}/RenderSystem_Direct3D9_d.dll
		${OGRE_PLUGIN_DIR_DBG}/RenderSystem_GL_d.dll
		${OGRE_PLUGIN_DIR_DBG}/libOIS_d.dll
		DESTINATION bin
		CONFIGURATIONS Debug
	)

	# Copy BOOST DLLs
	install(FILES ${Boost_DATE_TIME_LIBRARY_RELEASE}
		${Boost_THREAD_LIBRARY_RELEASE}
		DESTINATION bin
		CONFIGURATIONS Release RelWithDebInfo
	)

	install(FILES ${Boost_DATE_TIME_LIBRARY_DEBUG}
		${Boost_THREAD_LIBRARY_DEBUG}
		DESTINATION bin
		CONFIGURATIONS Debug
	)
endif(WIN32)
