/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * Re-Amp
 * Copyright (C)  2011 <>
 * 
 * Re-Amp is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * Re-Amp is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _FRAMEDATA_H_
#define _FRAMEDATA_H_

#include <OgreFrameListener.h>

typedef enum {
	FRAME_PRERENDER,
	FRAME_QUEUED,
	FRAME_POSTRENDER
} FrameType;

class FrameData: public Ogre::FrameEvent 
{
public:
	FrameType frameType;

protected:

private:

};

#endif // _FRAMEDATA_H_
