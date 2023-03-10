/*
 * Copyright 2023 AzgathCore
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef WAYCREST_MANOR_H
#define WAYCREST_MANOR_H

#define DataHeader "WM"

uint32 const EncounterCount = 5;

enum EnconterData
{	
    DATA_HEARTSBANE_TRIAD       = 0,
    DATA_SOULBOUND_GOLIATH      = 1,
    DATA_RAAL_THE_GLUTTONOUS    = 2,
    DATA_LORD_AND_LADY_WAYCREST = 3,
    DATA_GORAK_TUL              = 4,
	DATA_INTRO					= 5,
	DATA_INTRO_LORD_AND_LADY	= 6,
};

enum GameObjects
{
	DOODAD_SFX_LORD_AND_LADY_WAYCREST = 297809,
};

enum CreatureIds
{
	NPC_LADY_WAYCREST_INTRO		= 135357,
	NPC_LUCILLE_WAYCREST_INTRO	= 136084,
	NPC_INQUISITOR_MACE			= 136086,
	NPC_INQUISITOR_NOTLEY		= 136094,
	NPC_INQUISITOR_YORRICK		= 136085,
	NPC_INQUISITOR_STERNTIDE	= 136087,
	NPC_SISTER_MALADY_INTRO		= 135358,
	NPC_SISTER_SOLENA_INTRO		= 135359,
	NPC_SISTER_BRIAR_INTRO		= 135360,
	NPC_RUNIC_DISCPILE			= 137033,
	NPC_THISTLE_ACOLYTE			= 137034,
    NPC_SOULBOUND_GOLIATH       = 131667,
    NPC_RAAL_THE_GLUTTONOUS     = 131863,
    NPC_GORAK_TUL               = 131864,
    NPC_LORD_WAYCREST           = 131527,
    NPC_LADY_WAYCREST           = 131545,
    NPC_SISTER_BRIAR            = 131825,
    NPC_SISTER_SOLENA           = 131824,
    NPC_SISTER_MALADY           = 131823,
    NPC_MATRON_BRYNDLE          = 135329,
	NPC_FOCUSING_IRIS			= 132361,
	NPC_WASTING_SERVANT			= 133361,
	NPC_BILE_OOZELING			= 136541,
	NPC_SOUL_THORNS				= 136330,
	NPC_BURNING_SOUL			= 136436,
	NPC_DEATHTOUCHED_SLAVER		= 135552,
	NPC_DRUSTWAR_SUMMONING_PORTAL = 133435,
};

#endif // WAYCREST_MANOR_H
