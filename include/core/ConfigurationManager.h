
#ifndef _CONFIGURATION_MANAGER_H_
#define _CONFIGURATION_MANAGER_H

#include "OgreConfigFile.h"

#include "core/Singleton.h"

typedef std::pair<std::string, Ogre::ConfigFile> ConfigFilePair;


class ConfigurationManager: public Singleton<ConfigurationManager>
{
	friend class Singleton<ConfigurationManager>;
	public:
	ConfigurationManager();
	~ConfigurationManager();
	protected:
	std::map<std::string, Ogre::ConfigFile> fileCache;
};	
#endif
