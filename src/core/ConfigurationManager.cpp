/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * re-amp
 * Copyright (C)  2011 <>
 *
 * re-amp is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * re-amp is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <boost/foreach.hpp>
#include <boost/algorithm/string/replace.hpp>

#include "core/ConfigurationManager.h"

ConfigurationManager::ConfigurationManager()
{
}

ConfigurationManager::~ConfigurationManager()
{
	// Close all of the currently open files
	BOOST_FOREACH(ConfigFilePair fh, fhCache) {
		fh.second->close();
	}
}

void ConfigurationManager::init() {
}

/*
   Cleans up the string - removes the file suffix and changes / into .s
 */
std::string prepareString(std::string fileName) 
{
	boost::algorithm::replace_all(fileName, ".ini", "");
	boost::algorithm::replace_all(fileName, "/", ".");
}

bool ConfigurationManager::openConfiguration(std::string configurationFile) {
	// Try to find the string within the file handle cache. 
	std::map<std::string, std::ifstream*>::iterator iter = fhCache.find(prepareString(configurationFile));
	// If the value exists, bail out. 
	if (iter != fhCache.end())
		return true;

	// Open the file, if it exists
	std::ifstream configFile((DEFAULT_CONFIG_PREFIX + configurationFile).c_str());
	if (configFile.is_open()) {
		// Push into the table
		fhCache.insert(ConfigFilePair(prepareString(configurationFile), &configFile));
		return true;
	}

	// The operation must've failed. Close the file and return an error
	configFile.close();
	return false;
}
