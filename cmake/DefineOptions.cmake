option(WITH_SOUND "Build with sound support" ON)

# Build statically by default on Windows
if(WIN32)
	option(STATIC_BUILD "Build statically" ON)
else(WIN32)
	option(STATIC_BUILD "Build statically" OFF)
endif(WIN32)
