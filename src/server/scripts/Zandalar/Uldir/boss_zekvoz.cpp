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
#include "InstanceScript.h"
#include "Map.h"
#include "MotionMaster.h"
#include "ObjectAccessor.h"
#include "Player.h"
#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "SpellInfo.h"
#include "SpellScript.h"
#include "TemporarySummon.h"
#include "uldir.h"

enum ZekvozSpells
{
    //Phase 1
    SPELL_PERIODIC_ENERGY_GAIN = 295065,
    SPELL_EYE_BEAM_TRANSFORM = 264738, //well, this is used for bunny controller, just visual
    SPELL_TITAN_SPARK_TARGETS_SELECTOR = 266470,
    SPELL_TITAN_SPARK = 267019,
    SPELL_TITAN_SPARK_SELECTOR = 265061,
    SPELL_TITAN_SPARK_DAMAGE = 264954,
    SPELL_TITAN_SPARK_COSMETIC = 264950,
    SPELL_MIGHT_OF_THE_VOID = 267312,
    SPELL_VOID_LASH_DMG = 265264,
    SPELL_VOID_LASH_TARGET_SELECTOR = 265231,
    SPELL_VOID_LASH_TARGET_SELECTOR_VISION_RANGE = 265268,
    SPELL_VOID_LASH_TARGET_SELECTOR_CONE = 267963,
    SPELL_SHATTER = 265237,
    SPELL_SHATTER_DUMMY = 265248,
    SPELL_EYE_BEAM = 264382,
    SPELL_EYE_BEAM_TARGET_SELECTOR = 264383,
    SPELL_SPAWN_SILITHID_WARRIOR = 266913,
    SPELL_DESPAWN_SILITHID_WARRIOR = 267249,
    SPELL_SKITTERING_SWARM = 275772,
    SPELL_JAGGED_MANDIBLE = 264209,
    SPELL_JAGGED_MANDIBLE_DMG = 261976,
    SPELL_SURGING_DARKNESS_DMG_INT = 265451,
    SPELL_SURGING_DARKNESS_DMG_MID = 265452,
    SPELL_SURGING_DARKNESS_DMG_EXT = 265454,
    SPELL_SURGING_DARKNESS_DMG_EXT_N = 275084,
    SPELL_SURGING_DARKNESS_CIRCLE_INT = 265558,
    SPELL_SURGING_DARKNESS_CIRCLE_MID = 265559,
    SPELL_SURGING_DARKNESS_CIRCLE_EXT_N = 275925,
    SPELL_SURGING_DARKNESS_CIRCLE_INT_N = 271030,//same size
    SPELL_SURGING_DARKNESS_CIRCLE_MID_N = 271032,
    SPELL_SURGING_DARKNESS_CIRCLE_EXT_H = 271035,
    SPELL_SURGING_DARKNESS_ENERGIZE = 267629,
    SPELL_SURGING_DARKNESS_ENERGY_BAR = 267625,
    SPELL_SURGING_DARKNESS_DMG = 267350,
    //Phase 2
    SPELL_ROILING_DECEIT_TARGET_SELECTOR = 265437,
    SPELL_ROILING_DECEIT = 265358,
    SPELL_ROILING_DECEIT_AT = 265361,
    SPELL_ROILING_DECEIT_AURA = 265360,
    SPELL_ROILING_DECEIT_SUMMON = 265369,
    SPELL_ROILING_DECEIT_SUMMON_GUARD = 265363,
    SPELL_ROILING_DECEIT_DUMMY = 265402,
    SPELL_ROILING_DECEIT_TRANSFORM_SELECTOR = 265434,
    SPELL_ROILING_DECEIT_TRANSFORM = 265435,
    SPELL_ROILING_DECEIT_AURA_DAMAGE = 281473,
    SPELL_ENERGY_FILL = 265249,
    SPELL_JAGGED_MANDIBLE_AURA = 264210,
    SPELL_JAGGED_MANDIBLE_PROC_TRIGGER = 264209,
    SPELL_SHADOW_NOVA_DAMAGE = 265374,
    SPELL_VOID_BOLT = 267180,
    SPELL_SHADOWBIND_VISUAL = 270954,
    SPELL_VOID_WALL = 270589,
    //Phase 3
    SPELL_OVERLOAD = 61878,
    SPELL_OF_CORRUPTION_CREATE_AT = 265672,
    SPELL_ORB_OF_CORRUPTION_IMPACT_VISUAL = 269113,
    SPELL_ORB_OF_CORRUPTION_DUMMY = 267334,
    SPELL_ORB_OF_CORRUPTION = 267239,
    SPELL_ORB_OF_CORRUPTION_TARGET_SELECTOR = 267234,
    SPELL_CORRUPTORS_PATH_MAIN = 265662,
    SPELL_CORRUPTORS_PATH_SCREEN_EFFECT = 272023,
    SPELL_WILL_OF_THE_CORRUPTOR = 265646,
    SPELL_WILL_OF_THE_CORRUPTOR_BEAM = 270717,
    SPELL_PSIONIC_BLAST = 270620,
};

enum ZekvozEvents
{
    EVENT_TITAN_SPARK = 1,
    EVENT_MIGHT_OF_THE_VOID,
    EVENT_SURGING_DARKNESS,
    EVENT_EYE_BEAM,
    EVENT_SUMMON_SILITHID_WARRIOR,
    EVENT_ROILING_DECEIT,    
    EVENT_SURGING_DARKNESS_INT,
    EVENT_SURGING_DARKNESS_MID,
    EVENT_SURGING_DARKNESS_EXT,
    EVENT_SURGING_DARKNES_DMG_INT,
    EVENT_SURGING_DARKNES_DMG_MID,
    EVENT_SURGING_DARKNES_DMG_EXT,
    EVENT_NERUBIANS,
    EVENT_ORB_OF_CORRUPTION,
    EVENT_VOID_BOLT,
    EVENT_WILL_OF_THE_CORRUPTOR,
    EVENT_VOID_WAIL,
    EVENT_CORRUPTORS_PACT,
    EVENT_PSIONIC_BLAST,
};

enum ZekvozTexts
{
    SAY_AGGRO = 0,
    SAY_AGGRO_WHISPER = 7,
    SAY_SURGING_DARKNESS = 1,
    SAY_SURGING_DARKNESS_WHISPER = 2,
    SAY_WIPE_WHISPER = 3,
    SAY_DEATH = 4,
    SAY_DEATH_WHISPER = 8,
    SAY_WIPE = 5,
    SAY_KILL = 6,
};

enum Misc
{
    ACHIEVEMENT_MYTHIC_ZEKVOZ = 12529,
};

void AddSC_boss_zekvoz()
{
    
}
