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

#ifndef _CARSOUNDCOMPONENT_H_
#define _CARSOUNDCOMPONENT_H_

#include "components/SoundComponent.h"
#include "core/SoundManager.h"
#include "core/GameEntity.h"
#include "core/InputManager.h"


class CarSoundComponent: public SoundComponent
{
	public:
		CarSoundComponent(int id);
		~CarSoundComponent();
		virtual bool tick(FrameData &fd);
		virtual void init();
		virtual void honk(bool honk);
		virtual void updatePositions();
		virtual void fire();
	protected:

	private:
		SoundManager* pSoundManager;
};

#endif
