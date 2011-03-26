#
# Locate OpenAL
# This module defines
# OPENAL_LIBRARY
# OPENAL_FOUND
# OPENAL_INCLUDE_DIR
#

find_package(PkgConfig)
if(PKG_CONFIG_FOUND)
	pkg_check_modules(PC_OPENAL openal)
	set(OPENAL_DEFINITIONS ${PC_OPENAL_CFLAGS_OTHER})
endif(PKG_CONFIG_FOUND)

find_path(OPENAL_INCLUDE_DIR 
	NAMES al.h
	HINTS ${PC_OPENAL_INCLUDEDIR} ${PC_OPENAL_INCLUDE_DIRS}
	PATHS ${OPENAL_ROOT}
	PATH_SUFFIXES AL Al OpenAl openal
)

find_library(OPENAL_LIBRARY
	NAMES NAMES OpenAL al openal OpenAL32 OpenAL32.lib
	HINTS ${PC_OPENAL_LIBDIR} ${PC_OPENAL_LIBRARY_DIRS}
	PATHS ${OPENAL_ROOT} ${OPENAL_ROOT}/libs ${OPENAL_ROOT}/libs/Win32 
	PATH_SUFFIXES lib64 lib libs64 libs libs/Win32 libs/Win6
)


include( "FindPackageHandleStandardArgs" )
find_package_handle_standard_args(OpenAL DEFAULT_MSG OPENAL_LIBRARY OPENAL_INCLUDE_DIR)
mark_as_advanced(OPENAL_LIBRARY OPENAL_INCLUDE_DIR)

