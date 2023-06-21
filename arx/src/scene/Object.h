/*
 * Copyright 2011-2012 Arx Libertatis Team (see the AUTHORS file)
 *
 * This file is part of Arx Libertatis.
 *
 * Arx Libertatis is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Arx Libertatis is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Arx Libertatis.  If not, see <http://www.gnu.org/licenses/>.
 */
/* Based on:
===========================================================================
ARX FATALIS GPL Source Code
Copyright (C) 1999-2010 Arkane Studios SA, a ZeniMax Media company.

This file is part of the Arx Fatalis GPL Source Code ('Arx Fatalis Source Code'). 

Arx Fatalis Source Code is free software: you can redistribute it and/or modify it under the terms of the GNU General Public 
License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

Arx Fatalis Source Code is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied 
warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with Arx Fatalis Source Code.  If not, see 
<http://www.gnu.org/licenses/>.

In addition, the Arx Fatalis Source Code is also subject to certain additional terms. You should have received a copy of these 
additional terms immediately following the terms and conditions of the GNU General Public License which accompanied the Arx 
Fatalis Source Code. If not, please request a copy in writing from Arkane Studios at the address below.

If you have questions concerning this license or the applicable additional terms, you may contact in writing Arkane Studios, c/o 
ZeniMax Media Inc., Suite 120, Rockville, Maryland 20850 USA.
===========================================================================
*/
// Code: Cyril Meynier
//
// Copyright (c) 1999 ARKANE Studios SA. All rights reserved

#ifndef ARX_SCENE_OBJECT_H
#define ARX_SCENE_OBJECT_H

#include "graphics/GraphicsTypes.h"

enum ActionType {
	ACT_FIRE = 1,
	ACT_FIREOFF = 2,
	ACT_FIRE2 = 3,
	ACT_FIRE2OFF = 4
};

struct ACTIONSTRUCT {
	EERIE_LIGHT light;
	Vec3f pos;
	long dl;
	ActionType type;
	short exist;
};

const size_t MAX_ACTIONS = 100;

extern TexturedVertex	vert_list[4];
extern ACTIONSTRUCT actions[MAX_ACTIONS];

#ifdef BUILD_EDIT_LOADSAVE
EERIE_MULTI3DSCENE * PAK_MultiSceneToEerie(const res::path & dir);
void ReleaseMultiScene(EERIE_MULTI3DSCENE * ms);
#endif

void MakeUserFlag(TextureContainer * tc);
long EERIE_OBJECT_GetGroup(const EERIE_3DOBJ * obj, const std::string & groupname);
long EERIE_OBJECT_GetSelection(const EERIE_3DOBJ * obj, const std::string & selname);
 
long GetGroupOriginByName(const EERIE_3DOBJ * eobj, const std::string & text);
long GetActionPointIdx(const EERIE_3DOBJ * eobj, const std::string & text);
long GetActionPointGroup(const EERIE_3DOBJ * eobj, long idx);

/*!
 * Load a possibly cached 3D object using the default texture path.
 * 
 * @param pbox true if the object should have a physics box.
 */
EERIE_3DOBJ * loadObject(const res::path & file, bool pbox = true);

/*!
 * @param texpath texture path relative to file
 */
EERIE_3DOBJ * LoadTheObj(const res::path & file, const res::path & texpath = res::path());

EERIE_ANIM * TheaToEerie(const char * adr, size_t size, const res::path & fic);

void ReleaseAnim(EERIE_ANIM * ea);

EERIE_3DOBJ * Eerie_Copy(const EERIE_3DOBJ * obj);
void EERIE_Object_Precompute_Fast_Access(EERIE_3DOBJ * obj);
void EERIE_3DOBJ_RestoreTextures(EERIE_3DOBJ * eobj);
void EERIE_OBJECT_CenterObjectCoordinates(EERIE_3DOBJ * ret);
void EERIE_CreateCedricData(EERIE_3DOBJ * eobj);
void RemoveAllBackgroundActions();

#endif // ARX_SCENE_OBJECT_H
