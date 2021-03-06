/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * ReAmp
 * Copyright (C)  2011 ReAmp Contributors
 *
 * ReAmp is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * ReAmp is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _WEAPONBLOCKOGRECOMPONENT_H_
#define _WEAPONBLOCKOGRECOMPONENT_H_

#include "components/OgreComponent.h"

class WeaponBlockOgreComponent: public OgreComponent 
{
	public:
		WeaponBlockOgreComponent(int ID): OgreComponent(ID){};
		~WeaponBlockOgreComponent() {};

		virtual void init();

	protected:

	private:

		Ogre::Vector3 blockShift;

		Ogre::SceneNode *mBlockNode;
		
		Ogre::Entity *mBlock;
		
};

#endif // _WEAPONBLOCKOGRECOMPONENT_H_
