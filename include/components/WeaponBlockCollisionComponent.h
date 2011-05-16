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

#ifndef _WEAPONBLOCKCOLLISIONCOMPONENT_H_
#define _WEAPONBLOCKCOLLISIONCOMPONENT_H_

#include <Ogre.h>
#include "components/PhysicsComponent.h"
#include "core/PhysicsManager.h"
#include "core/InputManager.h"


class WeaponBlockCollisionComponent: public PhysicsComponent
{
	public:
		WeaponBlockCollisionComponent(int ID);
		~WeaponBlockCollisionComponent();
		virtual bool tick(FrameData &fd);
		void init();
		void pickupWeapon();
		void createBlock();

		// BOOST signals
		/*
		 * signal_pickup - fires when the car passes through a weapon block
		 * params - none
		 */
		boost::signal<void ()> signal_pickup;
	protected:

	private:
		OgreBulletDynamics::RigidBody *mBox;
		//OgreBulletCollisions::CollisionsWorld* cWorld;
};

#endif // _WEAPONBLOCKCOLLISIONCOMPONENT
