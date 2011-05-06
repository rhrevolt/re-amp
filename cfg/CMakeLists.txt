# Set the path to the resources.cfg to copy
set(RESOURCES_PATH "cfg/resources.cfg")

# Set the PLUGINS_PATH depending on platform
if (WIN32)
        set(PLUGINS_PATH "cfg/plugins.cfg-WIN32")
endif(WIN32)
if (LINUX)
        set(PLUGINS_PATH "cfg/plugins.cfg-LINUX")
endif(LINUX)

# The install target for the plugins
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

install(FILES ${CMAKE_SOURCE_DIR}/cfg/car_config.xml
		DESTINATION bin
		CONFIGURATIONS Release RelWithDebInfo Debug
)
