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

#ifndef _SOUNDCOMPONENT_H_
#define _SOUNDCOMPONENT_H_

#include "core/GameComponent.h"

class SoundComponent: public GameComponent
{
	public:
		SoundComponent(int ID): GameComponent(ID){};
		~SoundComponent() {};
		virtual bool tick(FrameData &fd);

	protected:
        std::map<std::string, unsigned int> audioFiles;

	private:

};

#endif // _SOUNDCOMPONENT_H_

