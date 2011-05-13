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
 * See the GNU General Public Licenfse for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdio.h>
#include "core/StateManager.h"
#include <OgreSceneQuery.h>
#include "components/WeaponOgreComponent.h"

#define GEOMETRY_QUERY_MASK 0

int numWeaponsInstanced = 0;

void WeaponOgreComponent::init()
{
	OgreComponent::init();

	mEntity = mSceneMgr->createEntity("boxEntity" + Ogre::StringConverter::toString(numWeaponsInstanced++), "ogrehead.mesh");
	//mBlock->setQueryFlags(GEOMETRY_QUERY_MASK);
	//mEntity->setCastShadows(true);

	mRootNode->attachObject (mEntity);
	mRootNode->scale(.04, .04, .04);
}


