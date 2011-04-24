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

#include "core/ConfigurationManager.h"

ConfigurationManager::ConfigurationManager()
{
}

ConfigurationManager::~ConfigurationManager()
{
}

void ConfigurationManager::init() {
	// Open the main, which includes paths to other configuration files
	const char* configurationName = "config.ini";
	fh.open(configurationName);
}

void ConfigurationManager::openConfiguration(std::string configurationFile) {
	// TODO: Look in the configuration cache. If the file isn't open, go
	// ahead and search the main config paths for the file, open it and put 
	// it in the file handle cache
}
