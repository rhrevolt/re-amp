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

bool doHonk = false;

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
	else {
		if(!pSoundManager->stopAudio(audioFiles["HONK"])) {
			printf("Failed to stop sound\n");
		}
	}
	return true;
}

void CarSoundComponent::updatePositions()
{
//	TODO: Get position from CarOgreComponent? or CarPhysicsComponent
//	BOOST_FOREACH(std::pair<std::string, unsigned int>* pair, audioFiles) {
//		pSoundManager->setSoundPosition(pair->second, position);
//	}
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
	unsigned int honkId = 0;
	pSoundManager->loadAudio("honka.wav", &honkId, false);
	pSoundManager->registerComponent(this);
	audioFiles.insert(std::pair<std::string, unsigned int>("HONK", honkId));
}
