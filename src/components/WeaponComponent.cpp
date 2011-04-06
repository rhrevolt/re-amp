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
#include "components/WeaponComponent.h"
#include "core/Application.h"

WeaponComponent::WeaponComponent(int ID): GameComponent(ID)
{
	srand(time(NULL));
	EventTypeList evts;
	evts.push_back(EVENT_FIRE);
	EventManager::instance()->registerEntity(componentID, evts);
}

WeaponComponent::~WeaponComponent()
{
}

// pickup a random weapon
void WeaponComponent::pickupWeapon()
{
	// TODO: Display weapon on UI
	// DONE: If weapons is empty, pick a random weapon, add it to the list
	if (curWeapon == NO_WEAPON)
	{
		curWeapon = rand() % NUM_WEAPONS + 1;	
	}
	else
	{
		// Already have a weapon
	}
}

void WeaponComponent::fireWeapon()
{
	// TODO: Display no weapon on UI
	// DONE: Push a weaponfired event
	WeaponFiredEvent evt;
	evt.weaponType = curWeapon;
	evt.eventType = EVENT_FIRED;
	EventManager::instance()->pushEvent(evt);

	curWeapon = NO_WEAPON;
}

bool WeaponComponent::tick(FrameData &fd)
{
	// TODO: Get events from entity
	
	// TODO: Check if we have collided with a weapons block
	// TODO: If so, call pickupWeapon()
	
	// TODO: Check if we have pressed the fire button
	// TODO: If so, call fireWeapon()
	return true;
}
