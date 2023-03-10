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

#include "AreaTrigger.h"
#include "AreaTriggerAI.h"
#include "MoveSplineInit.h"
#include <G3D/Vector3.h>
#include "ScriptMgr.h"
#include "Vehicle.h"

enum Spells
{
	// Wrath of Azshara
	SPELL_ARCANE_BOMB = 192706,
	SPELL_ARCANE_BOMB_DMG = 192708,
	SPELL_ARCANE_BOMB_VISUAL = 192711,
	SPELL_SURGING_WATERS = 192633,
	SPELL_MASSIVE_DELUGE = 192617,
	SPELL_MASSIVE_DELUGE_DMG = 192619,

	SPELL_MYSTIC_TORNADO = 192680,
	SPELL_MYSTIC_TORNADO_SUMMON = 192681,

	SPELL_CRUSHING_DEPTHS = 197365,
	SPELL_CRY_OF_WRATH = 192985,
	SPELL_RAGING_STORMS = 192696,
	SPELL_HEAVING_SANDS = 197165,

	SPELL_TIDAL_WAVE_AURA = 192940,
	SPELL_TIDAL_WAVE_DUMMY = 192793,
	SPELL_LIGHTING_STRIKES_AURA = 192737,
	SPELL_LIGHTING_STRIKES_TARGET = 192966,
	SPELL_LIGHTING_STRIKES_DMG = 192796,

	SPELL_TIDAL_WAVE_AURA_CRY = 197219,
	SPELL_TIDAL_WAVE_CRY_DUMMY = 192797,

	SPELL_LIGHTING_STRIKES_AURA_CRY = 192989,
	SPELL_RIDE_VEHICLE = 46598,

	SPELL_VIOLET_WINDS_AURA = 191805,
	SPELL_VIOLET_WINDS_AURA_CRY = 192649,
	SPELL_VIOLET_WINDS_DEBUFF = 191797,
	SPELL_VIOLET_WINDS_AREA = 191794,

	// Crushing Wave
	SPELL_FROST_RESONANCE = 196666,

	// Mystic Tornado   
	SPELL_MYSTIC_TORNADO_VISUAL = 192673,
	SPELL_MYSTIC_TORNADO_DMG = 192675,
	SPELL_MAGIC_RESONANCE = 196665,

	// Tidal Wave
	SPELL_TIDAL_WAVE_TARGET = 192792,
	SPELL_TIDAL_WAVE_DMG = 192801,
	SPELL_TIDAL_WAVE_VISUAL = 192753,

	// Ritualist Spells
	SPELL_MAGIC_BINDING = 196515,
	SPELL_POLYMORPH_FISH = 197105,
	SPELL_AQUA_SPOT = 196027,
	SPELL_STORM = 196870,
	SPELL_LIGHTING_BLAST = 196516,
	SPELL_STORM_CONDUIT = 193196,
};

enum Events
{
	EVENT_ARCANE_BOMB = 1,
	EVENT_CRUSHING_DEPTHS = 2,
	EVENT_MASSIVE_DELUGE = 3,
	EVENT_MYSTIC_TORNADO = 4,
	EVENT_RAGING_STORMS = 5,

	// Mystic Tornado
	EVENT_CHECK_DISTANCE = 6,
	EVENT_FIND_POSITION = 7,
	EVENT_BORN = 8,

	// Tidal Wave
	EVENT_TIDAL_WAVE = 9,
};

enum Adds
{
	BOSS_WRATH_OF_AZSHARA = 96028,

	NPC_ARCANE_BOMB = 97691,
	NPC_MYSTIC_TORNADO = 97673,
	NPC_TIDAL_WAVE = 97739,
};

enum Timers
{
	TIMER_MYSTIC_TORNADO = 26 * IN_MILLISECONDS,
	TIMER_MYSTIC_TORNADO_WRATH = 15 * IN_MILLISECONDS,

	TIMER_MASSIVE_DELUGE = 27 * IN_MILLISECONDS,

	TIMER_TIDAL_WAVE_WRATH = 8 * IN_MILLISECONDS,
	TIMER_TIDAL_WAVE = 15 * IN_MILLISECONDS,

	TIMER_CRUSHING_DEPTHS = 43 * IN_MILLISECONDS,

	TIMER_ARCANE_BOMB = 24 * IN_MILLISECONDS,

	TIMER_RAGING_STORM_CHECK = 5 * IN_MILLISECONDS,
};

enum Sounds
{
	SOUND_1 = 54212, // intro
	SOUND_2 = 54207, // aggro
	SOUND_3 = 54209, // kill
	SOUND_4 = 54206, //death
	SOUND_5 = 54213, //massive deluge
	SOUND_6 = 54214, // crushing depths
	SOUND_7 = 54215, //arcane bomb
	SOUND_8 = 54208, //cry of wrath
};

#define INTRO_TEXT "THE STORM AWAKENS."
#define AGGRO_TEXT "THE TIDES RISE!"
#define KILL_TEXT "WASHED AWAY!"
#define DEATH_TEXT "WATER... ETERNAL..."
#define MASSIVE_DELUGE_TEXT "CRUSH!"
#define CRUSHING_DEPTHS_TEXT "DROWN!"
#define ARCANE_BOMB_TEXT "SEEK... MAGIC..." 
#define CRY_OF_WRATH_TEXT "TEMPEST!"

const Position SurgingWatersCheck = { -3487.26f, 4385.58f, -3.60f }; // also cheaters check

void AddSC_boss_wrath_of_azshara()
{
	
}
