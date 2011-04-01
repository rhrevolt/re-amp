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
#include "components/InputComponent.h"
#include "core/InputManager.h"

InputComponent::InputComponent(int ID): GameComponent(ID)
{
	iManager = InputManager::getSingletonPtr();
	iManager->registerComponent(this);
}

InputComponent::~InputComponent() {
	InputManager* iManager = InputManager::getSingletonPtr();
	//iManager->unregisterComponent(this);
};

bool InputComponent::tick(FrameData &fd)
{
    //move the car as dictated by current input
    //PhysicsComponent.alterMoveVector(iManager.bufferedVector);

   // if (iManager->KEY_HORN)
    {
        //SoundComponent.playSound("horn");
    }

    //if (iManager->KEY_FIRE)
    {
        //RenderingComponent.fireWeapon();
    }
    /*
    TODO: Retrieve the input list from iManager
          Process each input, sending commands to the other components
          For movement commands, send action to physicsComponent
          For sounds (horn), send to soundComponent
    */


}
