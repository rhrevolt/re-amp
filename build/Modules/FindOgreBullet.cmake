# - Find OgreBullet
# Find the native OgreBullet includes and library
#
#   OGREBULLET_FOUND       - True if OgreBullet found.
#   OGREBULLET_INCLUDE_DIR - where to find includes
#   OGREBULLET_LIBRARIES   - List of libraries when using OgreBullet.
#

IF( OGREBULLET_INCLUDE_DIR )
    # Already in cache, be silent
    SET( OgreBullet_FIND_QUIETLY TRUE )
ENDIF( OGREBULLET_INCLUDE_DIR )

FIND_PATH( OGREBULLET_INCLUDE_DIR "Dynamics/OgreBulletDynamicsRigidBody.h"
           PATH_SUFFIXES "OgreBullet" )

FIND_LIBRARY( OGREBULLET_COL_LIB "OgreBulletCol")
FIND_LIBRARY( OGREBULLET_DYN_LIB "OgreBulletDyn")

SET(OGREBULLET_INCLUDE_DIRS "${OGREBULLET_INCLUDE_DIR}/Collisions" "${OGREBULLET_INCLUDE_DIR}/Dynamics")
#SET(OGREBULLET_LIBRARIES ${OGREBULLET_COL_LIB} ${OGREBULLET_DYN_LIB})
SET(OGREBULLET_LIBRARIES OgreBulletDyn OgreBulletCol)

# handle the QUIETLY and REQUIRED arguments and set OGREBULLET_FOUND to TRUE if
# all listed variables are TRUE
INCLUDE( "FindPackageHandleStandardArgs" )
FIND_PACKAGE_HANDLE_STANDARD_ARGS( "OgreBullet" DEFAULT_MSG OGREBULLET_INCLUDE_DIR OGREBULLET_LIBRARIES )

MARK_AS_ADVANCED( OGREBULLET_INCLUDE_DIR OGREBULLET_LIBRARIES )
