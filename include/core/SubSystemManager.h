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

#ifndef _SUBSYSTEM_MANAGER_H_
#define _SUBSYSTEM_MANAGER_H_

// Our includes
#include "core/EventManager.h"
#include "core/StateManager.h"
#include "core/Singleton.h"


class SubSystemManager
{
friend class Singleton<SubSystemManager>;
public:
	SubSystemManager(void);
	~SubSystemManager(void);

	void init();	
	bool tick(FrameData &fd);
	bool registerComponent(GameComponent* component);
	
protected:
	;

private:
	std::list<GameComponent*> componentList; 

};

#endif // _SUBSYSTEM_MANAGER_H_