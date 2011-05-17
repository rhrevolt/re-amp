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
#include "components/CarWeaponComponent.h"
#include <iostream>
#include <sstream>
#include "core/StateManager.h"

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

	Ogre::OverlayContainer* panel2 = static_cast<Ogre::OverlayContainer*>(
			overlayManager.createOverlayElement("Panel", "PanelName2"));
	panel2->setMetricsMode(Ogre::GMM_PIXELS);
	panel2->setPosition(StateManager::getInstance()->width/2, 10);
	panel2->setDimensions(100, 100);

	Ogre::OverlayContainer* panel3 = static_cast<Ogre::OverlayContainer*>(
			overlayManager.createOverlayElement("Panel", "PanelName3"));
	panel3->setMetricsMode(Ogre::GMM_PIXELS);
	panel3->setPosition(10, StateManager::getInstance()->height-40);
	panel3->setDimensions(100, 100);
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

	textArea2 = static_cast<Ogre::TextAreaOverlayElement*>(
			overlayManager.createOverlayElement("TextArea", "TextAreaName2"));
	textArea2->setMetricsMode(Ogre::GMM_PIXELS);
	textArea2->setPosition(70, 10);
	textArea2->setDimensions(100, 100);
	textArea2->setCaption("Hello, World!");
	textArea2->setCharHeight(32);
	textArea2->setFontName("BlueHigh");
	textArea2->setColourBottom(Ogre::ColourValue(0.3, 0.5, 0.3));
	textArea2->setColourTop(Ogre::ColourValue(0.5, 0.7, 0.5));

	textArea3 = static_cast<Ogre::TextAreaOverlayElement*>(
			overlayManager.createOverlayElement("TextArea", "TextAreaName3"));
	textArea3->setMetricsMode(Ogre::GMM_PIXELS);
	textArea3->setPosition(10, 10);
	textArea3->setDimensions(100, 100);
	textArea3->setCaption("Hello, World!");
	textArea3->setCharHeight(32);
	textArea3->setFontName("BlueHigh");
	textArea3->setColourBottom(Ogre::ColourValue(0.3, 0.5, 0.3));
	textArea3->setColourTop(Ogre::ColourValue(0.5, 0.7, 0.5));

	// Create an overlay, and add the panel
	Ogre::Overlay* overlay = overlayManager.create("OverlayName");
	overlay->add2D(panel);
	overlay->add2D(panel2);
	overlay->add2D(panel3);

	// Add the text area to the panel
	panel->addChild(textArea);
	panel2->addChild(textArea2);
	panel3->addChild(textArea3);
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
	std::stringstream ss2 (std::stringstream::in | std::stringstream::out);
	std::stringstream ss3 (std::stringstream::in | std::stringstream::out);
	time = timer->getMilliseconds()/1000.0f;
	int minutes = (int)time / 60;
	float seconds = (int)time % 60;
	std::string colon = ":";
	//speedString.append("                     ");
	ss2 << abs(minutes);
	ss3 << abs(seconds);
	std::string minString = ss2.str();
	std::string secString = ss3.str();
	if(minString=="0")
		minString = " ";
	minString.append(colon);
	if(seconds < 10){
		std::string zero = "0";
		secString = zero.append(secString);
	}
	minString.append(secString);

	int numWeap;
	CarWeaponComponent* weapComp = ((CarWeaponComponent*)parentEntity->getComponent(COMPONENT_WEAPON));
	if(weapComp == NULL)
		numWeap = 0;
	else
		numWeap = weapComp->getNumWeapons();
	std::stringstream ss4 (std::stringstream::in | std::stringstream::out);
	ss4 << numWeap;
	std::string weaponsString = ss4.str();
	std::string w = "Weapons: ";
	w.append(weaponsString);
	//speedString.append(timeString);
	textArea->setCaption(speedString);
	textArea2->setCaption(minString);
	textArea3->setCaption(w);
}
