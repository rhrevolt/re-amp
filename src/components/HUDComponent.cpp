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
#include "components/HUDComponent.h"

#include "components/CarPhysicsComponent.h"
#include <iostream>
#include <sstream>

HUDComponent::HUDComponent(int ID): GameComponent(ID)
{
	time = 0.0f;
	timer = new Ogre::Timer();
	timer->reset();
}	

HUDComponent::~HUDComponent()
{

}


bool HUDComponent::tick(FrameData &fd)
{
	updateSpeed(fd);
	return true;
}


void HUDComponent::init(){
	Ogre::OverlayManager& overlayManager = Ogre::OverlayManager::getSingleton();

	// Create a panel
	Ogre::OverlayContainer* panel = static_cast<Ogre::OverlayContainer*>(
		overlayManager.createOverlayElement("Panel", "PanelName"));
	panel->setMetricsMode(Ogre::GMM_PIXELS);
	panel->setPosition(10, 10);
	panel->setDimensions(100, 100);
	//panel->setMaterialName("MaterialName"); // Optional background material

	// Create a text area
	textArea = static_cast<Ogre::TextAreaOverlayElement*>(
		overlayManager.createOverlayElement("TextArea", "TextAreaName"));
	textArea->setMetricsMode(Ogre::GMM_PIXELS);
	textArea->setPosition(10, 10);
	textArea->setDimensions(100, 100);
	textArea->setCaption("Hello, World!");
	textArea->setCharHeight(32);
	textArea->setFontName("BlueHigh");
	textArea->setColourBottom(Ogre::ColourValue(0.3, 0.5, 0.3));
	textArea->setColourTop(Ogre::ColourValue(0.5, 0.7, 0.5));

	// Create an overlay, and add the panel
	Ogre::Overlay* overlay = overlayManager.create("OverlayName");
	overlay->add2D(panel);

	// Add the text area to the panel
	panel->addChild(textArea);

	// Show the overlay
	overlay->show();
	overlay->setZOrder(500);
	
}

void HUDComponent::updateSpeed(FrameData &fd){
	float speed = ((CarPhysicsComponent*)parentEntity->getComponent(COMPONENT_PHYSICS))->getVehicle()->getBulletVehicle()->getCurrentSpeedKmHour();
	 std::stringstream ss (std::stringstream::in | std::stringstream::out);

     ss << abs(speed);

     std::string speedString = ss.str();
     speedString.append(" km/h");
     
     time = timer->getMilliseconds()/1000.0f;
     speedString.append("                    ");
     ss << abs(time);
     std::string timeString = ss.str();
     speedString.append(timeString);
	 textArea->setCaption(speedString);
}
