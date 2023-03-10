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

#include "AreaTriggerAI.h"
#include "antorus.h"
#include "AreaTrigger.h"
#include "AreaTriggerTemplate.h"
#include "SpellAuraDefines.h"
#include "SpellAuraEffects.h"
#include "GameObject.h"

enum Says
{
    SAY_AGGRO = 0,
    SAY_RUINER = 1,
    SAY_REVERBERATING_STRIKE = 2,
    SAY_WARN_PHASE_2 = 3,
    SAY_PHASE_2 = 4,
    SAY_PHASE_2_PREPARE_TRAP = 5,
    SAY_PHASE_2_END = 6,
    SAY_DEATH = 7,
    SAY_WARN_EMPOWERED_RUINER = 8,
    SAY_WARN_EMPOWERED_REVERBERATING = 9,
    SAY_WARN_EMPOWERED_DIABOLIC_BOMB = 10,
};

enum Spells
{
    SPELL_OUTRO_CONV = 249807,
    SPELL_ENERGIZE_PERIODIC = 248303,
    SPELL_FORGING_STRIKE = 254919,
    SPELL_FORGING_STRIKE_LFR = 257978,
    SPELL_REVERBERATING_STRIKE = 254926,
    SPELL_REVERBERATING_STRIKE_LFR = 257997,
    SPELL_DIABOLIC_BOMB = 248214,
    SPELL_RUINER_FILTER = 246793,
    SPELL_RUINER_SUMMON = 246798,
    SPELL_RUINER_CHANNEL = 246833,
    SPELL_SHATTERING_STRIKE_1 = 248375,
    SPELL_SHATTERING_STRIKE_2 = 254900,
    SPELL_DAILY_ESSENCE_KINGAROTH = 305313,

    //Phase 2
    SPELL_APOCALYPSE_PROTOCOL = 246516,
    SPELL_REAVER_SPAWN = 246511,
    SPELL_INITIALIZING = 246504,
    SPELL_FEEDBACK_OVERLOAD = 258643,
    SPELL_APOCALYPSE_BLAST_FILTER = 246599,
    SPELL_APOCALYPSE_BLAST_MISSILE = 246629,

    //Mythic
    SPELL_WEAPONS_UPGRADE = 249920,
    SPELL_EMPOWERED_REVERBERATING = 254795,
    SPELL_EMPOWERED_DIABOLIC_BOMB = 254796,
    SPELL_EMPOWERED_RUINER = 254797,
    SPELL_OVERCHARGE = 249740,
    SPELL_RUINATION_SUMMON = 249425,
    SPELL_RUINATION_AT = 249429,
    SPELL_RUINATION_IN_AT = 249430,
    SPELL_RUINATION_MISSILE = 249453,
    SPELL_RUINATION_DMG = 249455,
    SPELL_RUINATION_BLAST = 249458,
    SPELL_REVER_DECIMATION_FILTER = 249680,
    SPELL_REVER_DECIMATION_MISSILE = 249686,
    SPELL_DEMOLISHED = 249535,

    // NPC_DETONATION_CHARGE
    SPELL_FIRE_MINE_VISUAL = 244313,
    SPELL_FLAME_REVERBERATION = 244328,

    // NPC_INCINERATOR_STALKER
    SPELL_PURGING_PROTOCOL = 248048,
    SPELL_PURGING_PROTOCOL_2 = 258020,

    // NPC_GAROTHI_ANNIHILATOR
    SPELL_ANNIHILATION = 246657,
    SPELL_ANNIHILATION_SUMMON = 246659,
    SPELL_ANNIHILATION_MISSILE = 246661,
    SPELL_ANNIHILATION_DMG = 246664,
    SPELL_ANNIHILATION_BLAST = 246666,
    SPELL_ANNIHILATION_AT = 246667,
    SPELL_ANNIHILATION_IN_AT = 246670,

    // NPC_GAROTHI_DECIMATOR
    SPELL_DECIMATION_FILTER = 246686,
    SPELL_DECIMATION_MARK = 246687,
    SPELL_DECIMATION_MISSILE = 246689,

    // NPC_GAROTHI_DEMOLISHER
    SPELL_DEMOLISH_FILTER = 246692,
    SPELL_DEMOLISH_MARK = 246698,
    SPELL_DEMOLISH_DMG = 246706,
};

enum eEvents
{
    EVENT_FORGING_STRIKE = 1,
    EVENT_REVERBERATING_STRIKE = 2,
    EVENT_DIABOLIC_BOMB = 3,
    EVENT_RUINER = 4,
    EVENT_CHECK_NEAREST_PLAYER = 5,
    EVENT_PHASE_2 = 6,
};

Position const summonPos[11] =
{
    {-10574.7f, 8028.3f, 1873.67f, 1.57f}, // NPC_INCINERATOR_STALKER
    {-10632.0f, 8140.1f, 1873.67f, 5.67f},
    {-10517.4f, 8140.1f, 1873.67f, 3.75f},

    {-10574.8f, 8023.36f, 1873.18f, 0.0f}, // NPC_INFERNAL_TOWER_1
    {-10637.3f, 8142.35f, 1873.18f, 4.12f},
    {-10512.4f, 8144.02f, 1873.18f, 2.16f},

    // Garothi
    {-10635.07f, 8142.42f, 1873.17f, 5.65f}, // Left Side
    {-10514.54f, 8142.44f, 1873.17f, 3.76f}, // Right Side
    {-10574.77f, 8024.12f, 1873.14f, 1.57f}, // Back Side

    {-10612.7f, 8025.21f, 1915.17f, 0.0f}, // NPC_APOCALYPSE_BLAST_STALKER
    {-10535.1f, 8025.50f, 1916.21f, 0.0f}
};

enum Misc
{
    ACTION_1 = 1,
    ACTION_2,

    EVENT_1,
    EVENT_2,
    EVENT_3,
};

void AddSC_boss_kingaroth()
{
   
}
