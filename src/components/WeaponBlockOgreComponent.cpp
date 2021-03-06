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
#include "components/WeaponBlockOgreComponent.h"

#define GEOMETRY_QUERY_MASK 0

int numBlocks = 0;

void WeaponBlockOgreComponent::init()
{		
    OgreComponent::init();
	blockShift = Ogre::Vector3(parentEntity->getProperties()->get<float>("<xmlattr>.pos_x"), parentEntity->getProperties()->get<float>("<xmlattr>.pos_z"), parentEntity->getProperties()->get<float>("<xmlattr>.pos_y"));

	mBlock = mSceneMgr->createEntity(
			"block" + Ogre::StringConverter::toString(numBlocks++),
			"ogrehead.mesh");
	//mBlock->setQueryFlags(GEOMETRY_QUERY_MASK);
	mBlock->setCastShadows(true);

	mBlockNode = mRootNode->createChildSceneNode();
	mBlockNode->attachObject (mBlock);
	mBlockNode->setPosition (blockShift);
	mBlockNode->scale(.04, .04, .04);
	mBlockNode->translate(Ogre::Vector3 (-blockShift));
}
