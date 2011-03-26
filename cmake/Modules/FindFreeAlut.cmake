# This module defines
#  FREEALUT_LIBRARY
#  FREEALUT_FOUND, if false, do not try to link to FreeAlut 
#  FREEALUT_LIB_DIR
#  FREEALUT_INCLUDE_DIR, where to find the headers
#   

find_package(PkgConfig)
if (PKG_CONFIG_FOUND)
	pkg_check_modules(PC_FREEALUT freealut)
	set(FREEALUT_DEFINITIONS ${PC_FREEALUT_CFLAGS_OTHER})
endif(PKG_CONFIG_FOUND)

find_path(FREEALUT_INCLUDE_DIR 
	NAMES alut.h
	HINTS ${PC_FREEALUT_INCLUDEDIR} ${PC_FREEALUT_INCLUDE_DIRS} 
	PATHS ${FREEALUT_ROOT}/include/AL 
	PATH_SUFFIXES AL Al OpenAL
)

find_path(FREEALUT_LIB_DIR alut.lib
	HINTS ${PC_FREEALUT_LIBDIR} ${PC_FREEALUT_INCLUDE_DIRS} 
	PATHS ${FREEALUT_ROOT}/lib
)  

find_library(FREEALUT_LIBRARY
	NAMES alut.lib
	HINTS ${PC_FREEALUT_LIBDIR} ${PC_FREEALUT_LIBRARY_DIRS}
	PATHS ${FREEALUT_ROOT}/lib
)

find_package_handle_standard_args(FreeAlut DEFAULT_MSG FREEALUT_LIBRARY FREEALUT_INCLUDE_DIR)
mark_as_advanced(FREEALUT_INCLUDE_DIR FREEALUT_LIBRARY)
