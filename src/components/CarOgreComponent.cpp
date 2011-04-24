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

#include <stdio.h>
#include "core/StateManager.h"
#include <OgreSceneQuery.h>
#include "components/CarOgreComponent.h"

#define GEOMETRY_QUERY_MASK 0

int numEntitiesInstanced = 0;

void CarOgreComponent::init()
{		
    OgreComponent::init();
	chassisShift = Ogre::Vector3(0, 0.8, 0);

	mChassis = mSceneMgr->createEntity(
			"chassis" + Ogre::StringConverter::toString(numEntitiesInstanced++),
			"chassis.mesh");
	mChassis->setQueryFlags(GEOMETRY_QUERY_MASK);
	mChassis->setCastShadows(true);

	mChassisNode = mRootNode->createChildSceneNode();
	mChassisNode->attachObject (mChassis);
	mChassisNode->setPosition (chassisShift);

	for (size_t i = 0; i < 4; i++)
	{
		mWheels[i] = mSceneMgr->createEntity(
				"wheel" + Ogre::StringConverter::toString(numEntitiesInstanced++),
				"wheel.mesh");

		mWheels[i]->setQueryFlags (GEOMETRY_QUERY_MASK);
		mWheels[i]->setCastShadows(true);

		mWheelNodes[i] = mSceneMgr->getRootSceneNode()->createChildSceneNode();
		mWheelNodes[i]->attachObject (mWheels[i]);
	}
}
