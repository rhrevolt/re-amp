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
bool stillFlying = false;


WeaponSoundComponent::WeaponSoundComponent(int ID) : SoundComponent(ID) {
}

WeaponSoundComponent::~WeaponSoundComponent() {
}

bool WeaponSoundComponent::tick(FrameData &fd)
{
    if(stillFlying) {
        pSoundManager->playAudio(audioFiles["SCREECH"], false);
    }
}

void WeaponSoundComponent::explode()
{
    stillFlying = false;
    pSoundManager->stopAudio(audioFiles["SCREECH"]);
    pSoundManager->playAudio(audioFiles["EXPLODE"], false);
}

void WeaponSoundComponent::init()
{
	pSoundManager = SoundManager::getInstance();
    //TODO: Register the explode callback with whatever signal will be fired
	unsigned int weaponScreech = 0, explode = 0;
	pSoundManager->loadAudio("weapon.wav", &weaponScreech, false);
    pSoundManager->loadAudio("explode.wav", &explode, false);
	pSoundManager->registerComponent(this);
	audioFiles.insert(std::pair<std::string, unsigned int>("SCREECH", weaponScreech));
    audioFiles.insert(std::pair<std::string, unsigned int>("EXPLODE", explode));
    stillFlying = true;
}
