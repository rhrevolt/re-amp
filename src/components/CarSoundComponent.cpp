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

#include <boost/foreach.hpp>

#include "core/SoundManager.h"
#include "core/InputManager.h"
#include "components/CarSoundComponent.h"
#include "components/CarPhysicsComponent.h"

bool doHonk = false;
bool doFire = false;
float THRESHOLD = 0.5;
float MAXSPEED = 20;
float MID = 15;
float LOW = 10;

CarSoundComponent::CarSoundComponent(int ID) : SoundComponent(ID) {
}

CarSoundComponent::~CarSoundComponent() {
}

bool CarSoundComponent::tick(FrameData &fd)
{
	if(doHonk) {
		printf("HONK!\n");
		if(!pSoundManager->playAudio(audioFiles["HONK"], false))
			printf("Failed to play sound\n");
	}
	CarPhysicsComponent* physComp = (CarPhysicsComponent*)parentEntity->getComponent(COMPONENT_PHYSICS);
	if(!pSoundManager->playAudio(audioFiles["ENGINE"], false))
		printf("Failed to play sound\n");
	float currSpeed = physComp->getCurrentSpeed();
	if(currSpeed < 0) currSpeed *= -1;
	if(currSpeed<THRESHOLD) {
		pSoundManager->changePitch(0.0f, audioFiles["ENGINE"]);
	}
	else if (currSpeed > MAXSPEED) {
		pSoundManager->changePitch(1.2f, audioFiles["ENGINE"]);
	}
	else if (currSpeed > MID) {
		pSoundManager->changePitch(1.1f, audioFiles["ENGINE"]);
	}
	else {
		pSoundManager->changePitch(1.0f, audioFiles["ENGINE"]);
	}
	printf("Speed: %f\n",currSpeed);
	return true;
}

void CarSoundComponent::updatePositions()
{
//	TODO: Get position from CarOgreComponent? or CarPhysicsComponent
//	BOOST_FOREACH(std::pair<std::string, unsigned int>* pair, audioFiles) {
//		pSoundManager->setSoundPosition(pair->second, position);
//	}
}

void CarSoundComponent::fire()
{
	if(!pSoundManager->playAudio(audioFiles["FIRE"], false))
		printf("Failed to play sound\n");
}

void CarSoundComponent::honk(bool honk)
{
	doHonk = honk;
	printf("Honking!!\n");
}

void CarSoundComponent::init()
{
	pSoundManager = SoundManager::getInstance();
	InputManager::getInstance()->signal_honk.connect(boost::bind(&CarSoundComponent::honk,this, _1));
	InputManager::getInstance()->signal_weapon.connect(boost::bind(&CarSoundComponent::fire,this));
	unsigned int honkId = 0, fireId=0, engineId=0;
	if(!pSoundManager->loadAudio("honk.wav", &honkId, false))
		printf("Failed to load audio!\n");
	if(!pSoundManager->loadAudio("fire.wav", &fireId, false))
		printf("Failed to load audio!\n");
	if(!pSoundManager->loadAudio("engine.wav", &engineId, true))
		printf("Failed to load audio!\n");
	pSoundManager->registerComponent(this);
	audioFiles.insert(std::pair<std::string, unsigned int>("HONK", honkId));
	audioFiles.insert(std::pair<std::string, unsigned int>("FIRE", fireId));
	audioFiles.insert(std::pair<std::string, unsigned int>("ENGINE", engineId));
}
