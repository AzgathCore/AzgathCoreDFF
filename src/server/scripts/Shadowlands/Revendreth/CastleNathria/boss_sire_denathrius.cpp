/*
* Copyright (C) 2021 AzgathCore
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
#include "GameObject.h"
#include "GameObjectAI.h"
#include "AreaTrigger.h"
#include "AreaTriggerAI.h"
#include "InstanceScript.h"
#include "SpellAuraEffects.h"
#include "castle_nathria.h"

enum SireDenathrius
{
    EVENT_GAIN_ENERGY = 1,
    SPELL_MARCH_OF_THE_PENITENT_SEND_EVENT = 328117,
    SPELL_DESOLATION_CREATE_AT = 327982, //pizza
    SPELL_DESOLATION_AT_DAMAGE = 327992,
    SPELL_MASSACRE_CREATE_LINE_AT = 330116,
    SPELL_MASSACRE_CREATE_WEAPON_AT = 330089,
    SPELL_COMMAND_RAVAGE = 327227,
    SPELL_RAVAGE_CAST_DUMMY = 327122,
    SPELL_INEVITABLE_DAMAGE = 328936,
    SPELL_INEVITABLE_TELEPORT = 328934,
    SPELL_FEEDING_TIME_MARK = 327039,
    SPELL_FEEDING_TIME_DRAIN_HEALTH = 327089, // 2 targets
    SPELL_FEEDING_TIME_SUMMON = 327085,
    SPELL_BURDEN_OF_SIN_PERIODIC_DUMMY = 326699,
    SPELL_BURDEN_OF_SIN_DAMAGE = 326700,
    SPELL_CLEANSING_PAIN_ALLLOW_CAST = 327040,
    SPELL_CLEANSING_PAIN = 326707,
    SPELL_PAINFUL_MEMORIES_CHANNEL = 326824,
    SPELL_PAINFUL_MEMORIES_DAMAGE = 326833,
    SPELL_BLOOD_PRICE_CHANNEL = 326994,
    SPELL_BLOOD_PRICE_DAMAGE = 326858,
    SPELL_BLOOD_PRICE_IMMOBILIZE = 326851,
    SPELL_BLOOD_PRICE_SUMMON = 326857,
    SPELL_BLOOD_PRICE_KNOCKBACK = 328527,
    SPELL_BLOOD_PRICE_KNOCKBACK_2 = 339188,
    SPELL_BLOOD_PRICE_EFFECT = 326988,
    //Phase 2
    SPELL_BLOODBOUND = 330580,
    SPELL_CRIMSON_CHORUS = 329711,
    SPELL_WRACKING_PAIN_ALLOW_CAST = 329183,
    SPELL_WRACKING_PAIN = 329181,
    SPELL_CARNAGE = 329875,
    SPEL_CARNAGE_PERIODIC = 329906,
    SPELL_IMPALE_MARK = 329951,
    SPELL_IMPALE_DAMAGE = 329974,
    SPELL_COMMAND_MASSACRE = 330042,
    SPELL_CRIMSON_CHORUS_PERIODIC_DAMAGE = 329785,
    SPEL_HAND_OF_DESTRUCTION_CAST = 333932,
    SPELL_HAND_OF_DESTRUCTION_DAMAGE = 330627,
    SPELL_DUSK_ELEGY = 335875,
    //Phase 3
    SPELL_INDIGNATION = 326005,
    SPELL_INDIGNATION_CREATE_AT = 332746, // 20841
    SPELL_SHATTERING_PAIN_ALLOW_CAST = 333223,
    SPELL_SHATTERING_PAIN_TRIGGER = 332619,
    SPELL_SHATTERING_PAIN_KNOCKBACK_BOSS = 332621,
    SPELL_SHATTERING_PAIN_DAMAGE_KNOCK = 332626,
    SPELL_SHATTER_PAIN_KNOCKBACK_FOR_TARGETS = 339148,
    SPELL_SHATTERING_PAIN_DAMAGE = 332620,
    SPELL_FATAL_FINESSE_PERIODIC_DAMAGE = 332797,
    SPELL_FATAL_FINESSE_SUMMON = 332795,
    SPELL_SINISTER_REFLECTION = 333979,
    SPELL_SINISTER_REFLECTION_CHANGE_MODEL = 332909,
    //Heroic
    SPELL_NIGHT_HUNTER_MISSILE = 334873,
    SPELL_NIGHT_HUNTER_DAMAGE = 327810,
    SPELL_NIGHT_HUNTER_MARK = 327796,
    SPELL_NIGHT_HUNTER_DUMMY = 332213,
    SPELL_RANCOR_CREATE_AREATRIGGER = 335872, //21186
    SPELL_RANCOR_AT_DAMAGE = 335873,
    SPELL_CRESCENDO_MISSILE = 336161,
    SPELL_SMOLDERING_IRE_CREATE_AT = 335997, // 21199, used for dmg?
    SPELL_SMOLDERING_IRE_CREATE_AT_2 = 336000, //21200
    SPELL_SMOLDERING_IRE_SCRIPT_EFFECT = 336004,
    SPELL_SMOLDERING_IRE_DAMAGE = 336008,
    //Mythic
    SPELL_COLLECTIVE_TRAUMA_DAMAGE = 338582,
    SPELL_SPITEFUL = 338510,
    ACTION_INIT_PHASE_2 = 1,
    ACTION_INIT_NIGHTCLOAK,
    ACTION_REMORNIA_EVENTS,
    ACTION_INIT_PHASE_3,
    SPELL_THROUGH_THE_MIRROR_MOD_PHASE = 338738,
    //Sinsear
    SPELL_NATHRIAN_HYMN_SINSEAR_CHANNEL = 341728, //peri dummy
    SPELL_NATHRIAN_HYMN_SINSEAR_DAMAGE = 338683,
    SPELL_NATHRIAN_HYMN_SINSEAR_MOD_DAMAGE_TAKEN = 341730,
    SPELL_NATHRIAN_HYMN_SINSEAR_PERI_DUMMY = 341728,
    SPELL_SINSEAR_SEARING_CENSURE = 341391, //peri dummy
    SPELL_SINSEAR_SEARING_CENSURE_CREATE_AT = 341419, //21707
    SPELL_SINEAR_SEARING_CENSURE_CREATE_AT_TWO = 341733, //21745
    SPELL_SINSEAR_SEARING_CENSURE_DAMAGE_SILENCE = 341732,
    //Evershade
    SPELL_NATHRIAN_HYMN_EVERSHADE_CHANNEL = 338684,
    SPELL_NATHRIAN_HYMN_EVERSHADE_DAMAGE = 338685,
    SPELL_NATHRIAN_HYMN_EVERSHADE_MOD_DAMAGE_TAKEN = 341651,
    SPELL_NATHRIAN_HYMN_EVERSHADE_PERI_DUMMY = 341648,
    SPELL_BALEFUL_SHADOWS_DUMMY = 344313,
    SPELL_EVERSHADE_BALEFUL_SHADOW_SUMMON = 345558,
    SPELL_VENGEFUL_WAIL = 344776,
    //Duskhollow
    SPELL_NATHRIAN_HMYN_DUSKHOLLOW_CHANNEL = 341637,
    SPELL_NATHRIAN_HYMN_DUSKHOLLOW_DAMAGE = 338687,
    SPELL_NATHRIAN_HYMN_DUSKHOLLOW_MOD_DAMAGE_TAKEN = 341638,
    SPELL_NATHRIAN_HYMN_DUSKHOLLOW_PERI_DUMMY = 338686,
    SPELL_HOLLOW_GRASP_DUMMY = 341366,
    //Gloomveil
    SPELL_NATHRIAN_HYMN_GLOOMVEIL_CHANNEL = 341715,
    SPELL_NATHRIAN_HYMN_GLOOMVEIL_DAMAGE = 338689,
    SPELL_NATHRIAN_HYMN_GLOOMVEIL_PERI_DUMMY = 338688,
    SPELL_NATHRIAN_HYMN_GLOOMVEIL_MOD_DAMAGE_TAKEN = 341714,
    SPELL_GLOOM_VEIL_AURA = 340687,
    SPELL_GLOOM_VEIL_CREATE_AT = 340685, //21663
    SPELL_GLOOM_VEIL_CREAT_AT_TWO = 341720, //21744
};

void AddSC_boss_sire_denathrius()
{
    
}