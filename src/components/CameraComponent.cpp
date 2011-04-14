/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * ReAmp
 * Copyright (C)  2011 <>
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
#include "components/CameraComponent.h"
#include "components/CarOgreComponent.h"
#include "core/StateManager.h"
#include "core/Application.h"

CameraComponent::CameraComponent(int ID): GameComponent(ID)
{
}

CameraComponent::~CameraComponent() {
};

void CameraComponent::init()
{
	mSceneMgr = StateManager::getCurrentState()->getSceneMgr();
    
    currentPos = Ogre::Vector3(0, 15, 30);
    
	createCamera();
	createViewports();
}

void CameraComponent::createCamera(void)
{
	mCamera = mSceneMgr->createCamera("CarCam");

    /* Attach the camera to our car and place it in the correct position */
    CarOgreComponent* ogreComp = (CarOgreComponent*)parentEntity->getComponent(COMPONENT_OGRE);
	Ogre::SceneNode* carRootNode = ogreComp->getNode();
    Ogre::SceneNode* camNode = carRootNode->createChildSceneNode("CamNode");
    camNode->translate(currentPos);
    camNode->attachObject(mCamera);
      
    //mCamera->setPosition(Ogre::Vector3(0,15,30));
    mCamera->lookAt(Ogre::Vector3(0,0,0));
    mCamera->setNearClipDistance(5);
	
    //mCameraMan = new OgreBites::SdkCameraMan(mCamera);
}

void CameraComponent::createViewports(void)
{
	Ogre::RenderWindow* mWindow = Application::getInstance()->getWindow();
	
	// Create one viewport, entire window
	Ogre::Viewport* vp = mWindow->addViewport(mCamera);
	vp->setBackgroundColour(Ogre::ColourValue(0,0,0));

	// Alter the camera aspect ratio to match the viewport
	mCamera->setAspectRatio(
		Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));
}

bool CameraComponent::tick(FrameData &fd)
{
	return true;
}

