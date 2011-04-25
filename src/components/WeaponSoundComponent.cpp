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

#include "components/WeaponSoundComponent.h"


WeaponSoundComponent::WeaponSoundComponent(int ID) : SoundComponent(ID) {
}

WeaponSoundComponent::~WeaponSoundComponent() {
}

bool WeaponSoundComponent::tick(FrameData &fd)
{
	//pSoundManager->playAudio(audioFiles["HONK"], true);
}

void WeaponSoundComponent::init()
{
	pSoundManager = SoundManager::getInstance();
	//unsigned int honkId = 0;
	//pSoundManager->loadAudio("honka.wav", &honkId, false);
	pSoundManager->registerComponent(this);
	//audioFiles.insert(std::pair<std::string, unsigned int>("HONK", honkId));
}
