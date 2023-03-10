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

#include "crucible_of_storms.h"
#include "Position.h"
#include "Common.h"
#include "ScriptedCreature.h"
#include "ScriptMgr.h"
#include "InstanceScript.h"
#include "SpellAuraDefines.h"
#include "AreaTrigger.h"
#include "AreaTriggerTemplate.h"
#include "AreaTriggerAI.h"
#include "SpellAuraEffects.h"

enum Spells
{
	// relic spells
	SPELL_TRIDENT_NPC_VISUAL = 287237,
	SPELL_TRIDENT_OF_DEEP_OCEAN_BUTTON = 284768,
	SPELL_FEEDBACK_OCEAN = 286457,

	SPELL_VOID_NPC_VISUAL = 285885,
	SPELL_VOID_STONE_BUTTON = 284684,
	SPELL_FEEDBACK_VOID = 286459,

	SPELL_VOID_STONE_ALLOW_CLICK = 286764,
	SPELL_TEMPEST_CALLER_ALLOW_CLICK = 286748,
	SPELL_TRIDENT_OF_DEEP_OCEAN_ALLOW_CLICK = 285883, //remove spellvisual

	SPELL_TEMPEST_NPC_VISUAL = 285884,
	SPELL_TEMPEST_CALLER_BUTTON = 286750,
	SPELL_FEEDBACK_STORM = 286458,
	
	// buttons
	SPELL_CUSTODY_OF_THE_DEEP = 284772, // trident of deep ocean
	SPELL_CUSTODY_SHIELD = 284804,
	SPELL_CUSTODY_AT = 286701,
	SPELL_ABYSSAL_COLLAPSE = 282886,

	SPELL_VOID_STONE_EFFECT = 284722,

	SPELL_TEMPEST_CALLER_EFFECT = 286755,
	SPELL_TEMPEST_CALLER_DAMAGE = 286754,
	SPELL_TEMPEST_CALLER_ANNIHILATE = 286753,

	// boss
	SPELL_GIFT_OF_NZOTH_OBSCURITY_CAST = 285453,
	SPELL_GIFT_OF_NZOTH_OBSCURITY_AT_DAMAGE = 285477,
	SPELL_GIFT_OF_NZOTH_OBSCURITY_AT_1 = 285457,
	SPELL_GIFT_OF_NZOTH_OBSCURITY_AT_2 = 285461,
	SPELL_GIFT_OF_NZOTH_OBSCURITY_AT_3 = 285465,
	SPELL_GIFT_OF_NZOTH_OBSCURITY_AT_4 = 285467,

	SPELL_GIFT_OF_NZOTH_HYSTERIA_CAST = 285638,
	SPELL_GIFT_OF_NZOTH_HYSTERIA_AURA = 285642,

	SPELL_GIFT_OF_NZOTH_LUNACY = 285685,

	SPELL_OBLIVION_TEAR_AT = 285210,
	SPELL_OBLIVION_TEAR_MISSILE_PLAYER = 285185,
	SPELL_OBLIVION_TEAR_MISSILE_BOSS = 285225,

	SPELL_MADDENING_EYES_OF_NZOTH_AT = 295737,
	SPELL_MADDENING_EYES_OF_NZOTH = 285345,

	SPELL_PIERCING_GAZE_OF_NZOTH_AT = 285359,
	SPELL_PIERCING_GAZE_OF_NZOTH_AURA = 285367,

	SPELL_TOUCH_OF_THE_END = 284851,
	SPELL_SIGHTLESS_BOND = 287693,
	SPELL_UNNATURAL_REGENERATION = 285333,
	SPELL_SHROUD_OF_WHISPERS = 292590,

	SPELL_UNKNOWABLE_TERROR_CAST = 285562,

	SPELL_INSATIABLE_TORMENT = 285652,
	SPELL_INSATIABLE_TORMENT_RANGE = 300742,
	SPELL_FEED_ON_THE_UNWORTHY_DAMAGE = 285653,
	SPELL_FEED_ON_THE_UNWORTHY_HEAL = 285676,

	SPELL_UNSTABLE_RESONANCE_DAMAGE = 293665,
	SPELL_UNSTABLE_RESONANCE_CAST = 293653,
	SPELL_UNSTABLE_OCEAN = 293662,
	SPELL_UNSTABLE_STORM = 293661,
	SPELL_UNSTABLE_VOID = 293663,

	SPELL_VOID_CRASH_BIG = 293968,
	SPELL_VOID_CRASH_MID = 282405,
	SPELL_VOID_CRASH_LOW = 282418,

	// adds
	SPELL_CONSUME_ESSENCE = 285427,
	SPELL_VOID_ERUPTION = 285431,
	SPELL_HUNGER_FOR_THE_END = 287291,
	SPELL_HUNGER_FOR_THE_END_AURA = 287292,
	SPELL_VOIDSTEP = 287275,
	SPELL_FEED = 285307,

	SPELL_VOID_SHIELD = 286310,
};

enum Events
{
	// Adds
	EVENT_SIGHTLESS_BOND = 1,
	EVENT_ENERGY_REGEN,
	EVENT_FIXATE_TANK,
	EVENT_VOIDSTEP,
	EVENT_CONSUME_ESSENCE,

	EVENT_ABYSSAL_COLLAPSE,
	EVENT_ADD_FRAME,
	EVENT_REMOVE_FRAME,
	EVENT_RELIC_REGEN,

	// UUnat
	EVENT_VOID_CRASH,
	EVENT_SUMMON_GUARDIANS,
	EVENT_SUMMON_PRIMORDIAL_MINDBENDER,
	EVENT_INSATIABLE_TORMENT,
	EVENT_UNSTABLE_RESONANCE,
	EVENT_PIERCING_GAZE,
	EVENT_MADDENING_EYE,
	EVENT_TOUCH_OF_THE_END,
	EVENT_OBLIVION_TEAR,
	EVENT_UNKNOWABLE_TERROR,

	EVENT_GIFT_OF_NZOTH_LUNACY,
	EVENT_GIFT_OF_NZOTH_HYSTERIA,
	EVENT_GIFT_OF_NZOTH_OBSCURITY,
};

enum Timers
{
	TIMER_VOIDSTEP = 10 * IN_MILLISECONDS,
	TIMER_ENERGY_REGEN = 3 * IN_MILLISECONDS,

	TIMER_VOID_CRASH = 35 * IN_MILLISECONDS,
	TIMER_SUMMON_GUARDIANS = 30 * IN_MILLISECONDS,
	TIMER_SUMMON_PRIMORDIAL_MINDBENDER = 60 * IN_MILLISECONDS,
	TIMER_INSATIABLE_TORMENT = 50 * IN_MILLISECONDS,
	TIMER_UNSTABLE_RESONANCE = 35 * IN_MILLISECONDS,
	TIMER_PIERCING_GAZE = 40 * IN_MILLISECONDS,
	TIMER_MADDENING_EYE = 45 * IN_MILLISECONDS,
	TIMER_TOUCH_OF_THE_END = 10 * IN_MILLISECONDS,
	TIMER_OBLIVION_TEAR = 25 * IN_MILLISECONDS,
	TIMER_UNKNOWABLE_TERROR = 60 * IN_MILLISECONDS,
};

enum Creatures
{
	BOSS_UUNAT = 145371,
	
	NPC_PRIMORDIAL_MINDBENDER = 146940,
	NPC_SWARMING_VOIDSPAWN = 146945,
	NPC_UNDYING_GUARDIAN = 146829,
	NPC_MADDENING_EYE_TRIGGER = 146912,
	NPC_PIERCING_GAZE_TRIGGER = 146913,

	NPC_OCEAN_RUNE = 146642,
	NPC_VOID_RELIC = 144804,
	NPC_TEMPEST_RELIC = 144808,
	NPC_TRIDENT_RELIC = 147574,
};

const Position centerPos = { 3487.13f, -1077.65f, -381.98f };

Position addsSummonPos[3] =
{
	{ 3470.77f, -1065.60f, -382.78f },
	{ 3507.61f, -1067.70f - 382.98f },
	{ 3492.80f, -1099.37f, -383.25f },
};

class notAvailableTarget
{
public:
	bool operator()(Player* target) const
	{
		return target && !target->HasAura(SPELL_TOUCH_OF_THE_END);
	}
};

class noResonanceStorm
{
public:
	bool operator()(Player* target) const
	{
		return target && target->HasAura(SPELL_UNSTABLE_STORM);
	}
};

class noResonanceVoid
{
public:
	bool operator()(Player* target) const
	{
		return target && target->HasAura(SPELL_UNSTABLE_VOID);
	}
};

class noResonanceOcean
{
public:
	bool operator()(Player* target) const
	{
		return target && target->HasAura(SPELL_UNSTABLE_OCEAN);
	}
};

enum Points
{
	POINT_VOID_SHIELD = 200,
};

enum Actions
{
	ACTION_REGEN_RELIC = 1,
};

#define AGGRO_TEXT "Pay the price for your defiance!"
#define INTRO_TEXT "His eyes behold every truth.... every unnumbered crime!" // ?!
#define GIFT_OBSCURITY_TEXT "His wrath has awakened!"
#define PHASE2_TEXT "His devoted outnumber the sands... the stars!"
#define GIFT_HISTERYA_TEXT "Taste his true power!"
#define PHASE3_TEXT "His gaze falls upon every path... every dream given form!"
#define GIFT_LUNACY_TEXT "Aid your faithful servant, o mighty N'Zoth!"
#define DIED_TEXT "All... shall be... awakened..."
#define KILLED_TARGET "All glory to the master"

void AddSC_bfa_boss_uunat()
{
	
}
