
#ifndef _CONFIGURATION_MANAGER_H_
#define _CONFIGURATION_MANAGER_H

#include "OgreConfigFile.h"

#include "core/Singleton.h"

typedef std::pair<std::string, std::ifstream*> ConfigFilePair;

class ConfigurationManager: public Singleton<ConfigurationManager>
{
	friend class Singleton<ConfigurationManager>;
	public:
	ConfigurationManager();
	~ConfigurationManager();
	void init();
	bool openConfiguration(std::string);
	protected:
	std::map<std::string, std::ifstream*> fhCache;
	std::ifstream fh;
};	
#endif
