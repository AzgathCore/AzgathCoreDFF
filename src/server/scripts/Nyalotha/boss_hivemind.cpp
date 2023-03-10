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

#include "ScriptMgr.h"
#include "Creature.h"
#include "CreatureAI.h"
#include "InstanceScript.h"
#include "SpellAuras.h"
#include "SpellScript.h"
#include "SpellAuraEffects.h"
#include "AreaTrigger.h"
#include "AreaTriggerAI.h"
#include "nyalotha.h"

enum Texts
{
	SAY_KAZIR_SPAWN_ACIDIC = 0,
	SAY_KAZIR_HIVEMIND_CONTROL,
	SAY_KAZIR_SHADOWS,
	SAY_KAZIR_BLISTER,
	SAY_TEKRIS_FALL = 0,
	SAY_TEKRIS_GIVE,
	SAY_TEKRIS_HIVE_CONTROL,
	SAY_TEKRIS_ECHOING_VOID,
	SAY_TEKRIS_VOID,
	SAY_TEKRIS_KILL
};

enum Spells
{
	SPELL_HIVEMIND_ENERGY_MANAGEMENT = 313732,
	SPELL_TEKRIS_HIVEMIND_CONTROL = 307213,
	SPELL_TEKRIS_HIVEMIND_CONTROL_DAMAGE_REDUCTION = 315884,
	SPELL_KAZIR_HIVEMIND_CONTROL = 307201,
	SPELL_KAZIR_HIVEMIND_CONTROL_DAMAGE_REDUCTION = 315889,
	SPELL_SHADOW_VEIL = 307202,
	SPELL_VOID_INFUSION = 307334,
	SPELL_REGENERATION = 307227,
	SPELL_REGENERATION_HEAL = 306974,
	SPELL_DARK_RECONSTRUCTION = 307569,
	SPELL_NULLIFICATION_BLAST = 307968,
	SPELL_NULLIFICATIOB_BLAST_DEBUFF = 313460,
	SPELL_ECHOING_VOID = 307232,
	SPELL_ECHOING_VOID_PULSE = 317022,
	SPELL_SPAWN_ACIDIC_AQUIR = 313441,
	SPELL_SPAWN_ACIDIC_AQUIR_SUMMON = 310340,
	SPELL_ACIDIC_AQUIR_VISUAL = 310343,
	SPELL_CORROSION = 313461,
	SPELL_MIND_NUMBING_NOVA = 313652,
	SPELL_MIND_NUMBING_TOXIN = 314593,
	
	SPELL_PSIONIC_RESONANCE = 307217,
	
	SPELL_RAVAGE = 315311,
	
	SPELL_DEVOURING_FRENZY_VISUAL = 310402,
	SPELL_DEVOURING_FRENZY_DAMAGE = 310403,
	SPELL_DEVOURING_FRENZY_MOD_DAMAGE = 313720,
	SPELL_ACIDIC_BLOOD_CREATE_AT = 313671,
	SPELL_ACIDIC_BLOOD_AT_DAMAGE = 307560,
	SPELL_ACCELERATED_EVOLUTION_MISSILE = 308227,
	SPELL_ACCELERATED_EVOLUTION = 307637,
	SPELL_VOLATILE_ERUPTION = 307582,
	
	SPELL_ACID_POOL_AT_DAMAGE = 316049,
	SPELL_ENTROPIC_ECHO_MISSILE = 313689,
	SPELL_ENTROPIC_ECHO_DAMAGE = 313692,	
};

enum Events
{
	EVENT_POWER_GAIN = 1,
	EVENT_AQIR_DRONES,
	EVENT_AQIR_DARTERS,
	EVENT_NULLIFICATION_BLAST,
	EVENT_ECHOING_VOID,
	EVENT_SPAWN_ACIDIC_AQIR,
	EVENT_MIND_NUMBING_NOVA,
	
	EVENT_DEVOURING_FRENZY,
	EVENT_ACCELERATED_EVOLUTION,
	EVENT_VOLATILE_ERUPTION,
};

enum Actions
{
	ACTION_TEKRIS_CONTROL,
	ACTION_KAZIR_CONTROL
};

const Position middle_of_the_room = { -290.083f, 227.152f, -294.551f, 2.512f };

void AddSC_hivemind()
{
	
};

