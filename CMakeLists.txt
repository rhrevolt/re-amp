#
# Re-Amp Project
# Build System
# (C) 2011 Re-Amp Project Contributors
# 
project(ReAmp)

# Minimum required CMake version
cmake_minimum_required(VERSION 2.6)

# Set the module search path
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake;${CMAKE_SOURCE_DIR}/cmake/Modules;${CMAKE_MODULE_PATH}")

# Add definitions
include(DefineCMakeDefaults)
include(DefinePlatformDefaults)
include(DefineCompilerFlags)
include(${CMAKE_SOURCE_DIR}/cmake/DefineOptions.cmake)
include(${CMAKE_SOURCE_DIR}/cmake/ProductInformation.cmake)

# Set where to install install things to.
set(CMAKE_INSTALL_PREFIX "${CMAKE_CURRENT_BINARY_DIR}/dist")

# Search for dependencies

# Setup some search paths for Windows
if (WIN32)
	set(FREEALUT_ROOT ${CMAKE_SOURCE_DIR}/contrib/freealutWin32)
	set(OPENAL_ROOT ${CMAKE_SOURCE_DIR}/contrib/OpenALWin32)
	set(BULLET_ROOT ${CMAKE_SOURCE_DIR}/contrib/bulletWin32)
	set(OGREBULLET_ROOT ${CMAKE_SOURCE_DIR}/contrib/OgrebulletWin32)
	set(BOOSTDIR ${CMAKE_SOURCE_DIR}/contrib/boostWin32)
endif()


# Find OGRE and check for 1.7
find_package(OGRE 1.7.0 REQUIRED)

# Find OIS 
find_package(OIS REQUIRED)

# Find Boost
set(Boost_USE_STATIC_LIBS ${STATIC_BUILD})
find_package(Boost 1.40 REQUIRED)

# Find OpenAL, FreeAlut, Bullet, and OgreBullet
find_package(OpenAL REQUIRED)
find_package(FreeAlut REQUIRED)
find_package(Bullet REQUIRED)
find_package(OgreBullet REQUIRED)

# Include the CMakeLists for the remaining directories
add_subdirectory(include)
add_subdirectory(src)
add_subdirectory(cfg)
add_subdirectory(build/dist/media)
