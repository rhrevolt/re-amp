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
#include "components/OgreComponent.h"
#include "core/StateManager.h"

bool OgreComponent::tick(FrameData &fd)
{
}
void OgreComponent::init()
{
	mSceneMgr = StateManager::getInstance()->inGameState->getSceneMgr();
	mRootNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
}

void OgreComponent::setInitialPosition(Ogre::Vector3& pos)
{
	mRootNode->setPosition(pos);
}

