# this module was taken from http://noget.net/cgd/oe/extensions/Sound/conf/cmake/FindFreeAlut.cmake
#
# - Locate FreeAlut
# This module defines
#  FREEALUT_LIBRARY
#  FREEALUT_FOUND, if false, do not try to link to FreeAlut 
#  FREEALUT_LIB_DIR
#  FREEALUT_INCLUDE_DIR, where to find the headers
#   
# $FREEALUTDIR is an environment variable that would

#Todo: Setting up and testing for other platforms than windows
FIND_PATH(FREEALUT_INCLUDE_DIR alut.h
  $ENV{FREEALUTDIR}/include/AL
  
  ~/Library/Frameworks/freealut.framework/Headers
  /Library/Frameworks/freealut.framework/Headers
  /System/Library/Frameworks/freealut.framework/Headers # Tiger
  /usr/local/include/AL
  /usr/local/include/freealut
  /usr/local/include
  /usr/include/AL
  /usr/include/freealut
  /usr/include
  /sw/include/AL # Fink
  /sw/include/freealut
  /sw/include
  /opt/local/include/AL # DarwinPorts
  /opt/local/include/freealut
  /opt/local/include
  /opt/csw/include/AL # Blastwave
  /opt/csw/include/freealut
  /opt/csw/include
  /opt/include/AL
  /opt/include/freealut
  /opt/include

  ${PROJECT_SOURCE_DIR}/libraries/freealut/include/AL
 )

FIND_PATH(FREEALUT_LIB_DIR alut.lib
  ${PROJECT_SOURCE_DIR}/libraries/freealut/lib/
)  
  
# I'm not sure if I should do a special casing for Apple. It is 
# unlikely that other Unix systems will find the framework path.
# But if they do ([Next|Open|GNU]Step?), 
# do they want the -framework option also?
IF(${FREEALUT_INCLUDE_DIR} MATCHES ".framework")
  STRING(REGEX REPLACE "(.*)/.*\\.framework/.*" "\\1" FREEALUT_FRAMEWORK_PATH_TMP ${FREEALUT_INCLUDE_DIR})
  IF("${FREEALUT_FRAMEWORK_PATH_TMP}" STREQUAL "/Library/Frameworks"
      OR "${FREEALUT_FRAMEWORK_PATH_TMP}" STREQUAL "/System/Library/Frameworks"
      )
    # String is in default search path, don't need to use -F
    SET (FREEALUT_LIBRARY "-framework FreeAlut" CACHE STRING "FreeAlut framework for OSX")
  ELSE("${FREEALUT_FRAMEWORK_PATH_TMP}" STREQUAL "/Library/Frameworks"
      OR "${FREEALUT_FRAMEWORK_PATH_TMP}" STREQUAL "/System/Library/Frameworks"
      )
    # String is not /Library/Frameworks, need to use -F
    SET(FREEALUT_LIBRARY "-F${FREEALUT_FRAMEWORK_PATH_TMP} -framework FreeAlut" CACHE STRING "FreeAlut framework for OSX")
  ENDIF("${FREEALUT_FRAMEWORK_PATH_TMP}" STREQUAL "/Library/Frameworks"
    OR "${FREEALUT_FRAMEWORK_PATH_TMP}" STREQUAL "/System/Library/Frameworks"
    )
  # Clear the temp variable so nobody can see it
  SET(FREEALUT_FRAMEWORK_PATH_TMP "" CACHE INTERNAL "")

ELSE(${FREEALUT_INCLUDE_DIR} MATCHES ".framework")
  FIND_LIBRARY(FREEALUT_LIBRARY 
    NAMES alut
    PATHS
    $ENV{FREEALUTDIR}/lib
    $ENV{FREEALUTDIR}/libs
    /usr/local/lib
    /usr/lib
    /sw/lib
    /opt/local/lib
    /opt/csw/lib
    /opt/lib
    ${PROJECT_SOURCE_DIR}/libraries/freealut/lib/
    )    
ENDIF(${FREEALUT_INCLUDE_DIR} MATCHES ".framework")
SET(FREEALUT_FOUND "NO")
IF(FREEALUT_LIBRARY)
  SET(FREEALUT_FOUND "YES")
ENDIF(FREEALUT_LIBRARY)

