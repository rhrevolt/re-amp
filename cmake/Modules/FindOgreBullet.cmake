# - Find OgreBullet
# Find the native OgreBullet includes and library
#
#   OGREBULLET_FOUND       - True if OgreBullet found.
#   OGREBULLET_INCLUDE_DIR - where to find includes
#   OGREBULLET_LIBRARIES   - List of libraries when using OgreBullet.
#

find_package(PkgConfig)
if(PKG_CONFIG_FOUND)
	pkg_check_modules(PC_OGREBULLET OgreBullet)
	set(OGREBULLET_DEFINITIONS ${PC_OGREBULLET_CFLAGS_OTHER})
endif(PKG_CONFIG_FOUND)

find_path(OGREBULLET_INCLUDE_DIR Dynamics/include/OgreBulletDynamicsRigidBody.h
	HINTS ${PC_OGREBULLET_INCLUDEDIR} ${PC_OGREBULLET_INCLUDE_DIRS} 
	PATHS ${OGREBULLET_ROOT}/
	PATH_SUFFIXES OgreBullet )

find_library(OGREBULLET_LIBRARIES 
	NAMES OgreBulletCol.a OgreBulletDyn.a
	HINTS ${PC_OGREBULLET_LIBDIR} ${PC_OGREBULLET_LIBRARY_DIRS} 
	PATHS ${OGREBULLET_ROOT}/lib/Debug 
	PATH_SUFFIXES OgreBullet
)

set(OGREBULLET_INCLUDE_DIRS "${OGREBULLET_INCLUDE_DIR}/Collisions/include" "${OGREBULLET_INCLUDE_DIR}/Dynamics/include")

# handle the QUIETLY and REQUIRED arguments and set OGREBULLET_FOUND to TRUE if
# all listed variables are TRUE
INCLUDE( "FindPackageHandleStandardArgs" )
FIND_PACKAGE_HANDLE_STANDARD_ARGS( OgreBullet DEFAULT_MSG OGREBULLET_INCLUDE_DIR OGREBULLET_LIBRARIES )

MARK_AS_ADVANCED( OGREBULLET_INCLUDE_DIR OGREBULLET_LIBRARIES )
