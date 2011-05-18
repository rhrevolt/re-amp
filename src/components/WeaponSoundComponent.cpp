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
bool fire = false;


WeaponSoundComponent::WeaponSoundComponent(int ID) : SoundComponent(ID) {
}

WeaponSoundComponent::~WeaponSoundComponent() {
}

bool WeaponSoundComponent::tick(FrameData &fd)
{
    // TODO: Get the current position of the weapon
	printf("\n\nScreeching.\n\n");
    if(fire) {
        pSoundManager->playAudio(audioFiles["SCREECH"], false);
		fire = false;
        //pSoundManager->setSoundPosition(audioFiles["SCREECH"], position);
    }
}

void WeaponSoundComponent::fireWeapon()
{
	fire = true;
}

void WeaponSoundComponent::init()
{
	pSoundManager = SoundManager::getInstance();
	InputManager::getInstance()->signal_weapon.connect(boost::bind(&WeaponSoundComponent::fireWeapon,this));
    //TODO: Register the explode callback with whatever signal will be fired
	printf("\n\nscreech?\n\n");
	unsigned int weaponScreech = 0, explode = 0;
	pSoundManager->loadAudio("screech.wav", &weaponScreech, false);
    pSoundManager->loadAudio("explode.wav", &explode, false);
	pSoundManager->registerComponent(this);
	audioFiles.insert(std::pair<std::string, unsigned int>("SCREECH", weaponScreech));
}
