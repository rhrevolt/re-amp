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

#ifndef _WEAPONPHYSICSCOMPONENT_H_
#define _WEAPONPHYSICSCOMPONENT_H_

#include <Ogre.h>
#include "components/PhysicsComponent.h"
#include "core/PhysicsManager.h"
#include "core/InputManager.h"

class CarOgreComponent; // forward declaration

class WeaponPhysicsComponent: public PhysicsComponent
{
	public:
		WeaponPhysicsComponent(int ID);
		~WeaponPhysicsComponent();
		virtual bool tick(FrameData &fd);
		void init();
		void createMissile(CarOgreComponent *source);

		// BOOST signals
		boost::signal<void (CarOgreComponent source)> signal_targetHit;
	protected:

	private:
		Ogre::Vector3 direction;
		CarOgreComponent *carComponent;
};

#endif // _WEAPONPHYSICSCOMPONENT_H_
