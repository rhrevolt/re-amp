# Build the includes
if (WITH_SOUND)
	set(REAMP_LIB_INCLUDES 
		${REAMP_LIB_INCLUDES}
		${OPENAL_INCLUDE_DIR} 
		${FREEALUT_INCLUDE_DIR} 
	)
	set(REAMP_LINK_LIBRARIES
		${REAMP_LINK_LIBRARIES}
		${OPENAL_LIBRARY}
		${FREEALUT_LIBRARY}
	)
endif(WITH_SOUND)

# The remaining libraries
set(REAMP_LIB_INCLUDES
	${REAMP_LIB_INCLUDES} 
	${OGRE_INCLUDE_DIRS} 
	${OIS_INCLUDE_DIRS} 
	${BULLET_INCLUDE_DIRS} 
	${OGREBULLET_INCLUDE_DIRS} 
	${Boost_INCLUDE_DIRS} 
)

set(REAMP_LINK_LIBRARIES
	${REAMP_LINK_LIBRARIES} 
	${Boost_LIBRARIES} 
	${OGREBULLET_LIBRARIES}
	${BULLET_LIBRARIES}
	${OGRE_LIBRARIES} 
	${OIS_LIBRARIES} 
)

# The sources included..
FILE(GLOB_RECURSE REAMP_SRCS ${CMAKE_SOURCE_DIR}/src/*.cpp)
FILE(GLOB_RECURSE REAMP_HDRS ${CMAKE_SOURCE_DIR}/include/*.h)

include_directories(${CMAKE_SOURCE_DIR}/include
	${REAMP_LIB_INCLUDES}
	${CMAKE_BINARY_DIR}/include
)	

# Build the executable
add_executable(${PROJECT_EXEC} WIN32 ${REAMP_HDRS} ${REAMP_SRCS})
set_target_properties(${PROJECT_EXEC} PROPERTIES DEBUG_POSTFIX _d)
target_link_libraries(${PROJECT_EXEC} ${REAMP_LINK_LIBRARIES})

# Create a few directories
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/dist/bin)
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/dist/media)

# Set the output path
if(MINGW OR UNIX)
        set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/dist/bin)
endif(MINGW OR UNIX)

# The install target for the bin
install(TARGETS ${PROJECT_EXEC}
        RUNTIME DESTINATION bin
        CONFIGURATIONS All
)

# Some library copy crap for Windows
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

