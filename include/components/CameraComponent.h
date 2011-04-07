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

#ifndef _CAMERACOMPONENT_H_
#define _CAMERACOMPONENT_H_

#include "core/GameComponent.h"
#include <OgreCamera.h>

class CameraComponent: public GameComponent
{
	public:
		CameraComponent(int ID);
		~CameraComponent();
		
		virtual bool tick(FrameData &fd);

		virtual ComponentType getType() {return COMPONENT_CAMERA;};

	protected:
		void createCamera();
		void createViewports(void);

	private:
		Ogre::SceneManager* mSceneMgr;
		Ogre::Camera* mCamera;
};

#endif