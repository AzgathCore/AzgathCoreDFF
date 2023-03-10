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

#ifndef THRONE_OF_THUNDER_H
#define THRONE_OF_THUNDER_H

#include "ScriptMgr.h"
#include "SpellScript.h"
#include "Map.h"
#include "Creature.h"
#include "CreatureAIImpl.h"
#include "ScriptMgr.h"

enum DataTypes
{
    DATA_JINROKH,
    DATA_HORRIDON,
    DATA_COUNCIL_OF_ELDERS,
    DATA_TORTOS,
    DATA_MEGAERA,
    DATA_JI_KUN,
    DATA_DURUMU_THE_FORGOTTEN,
    DATA_PRIMORDIUS,
    DATA_DARK_ANIMUS,
    DATA_IRON_QON,
    DATA_TWIN_CONSORTS,
    DATA_LEI_SHEN,
    DATA_RA_DEN,
    MAX_DATA
};

enum SaveData
{
    TYPE_JINROKH,
    TYPE_HORRIDON,
    TYPE_COUNCIL,
    TYPE_TORTOS,
    TYPE_MEGAERA,
    TYPE_JI_KUN,
    TYPE_DURUMU,
    TYPE_PRIMORDIUS,
    TYPE_DARK_ANIMUS,
    TYPE_IRON_QON,
    TYPE_TWIN_CONSORTS,
    TYPE_LEI_SHEN,
    TYPE_RA_DEN,
    TYPE_JINROKH_INTRO,
    TYPE_TORTOS_INTRO,
    TYPE_BELLS_RUNG,
    TYPE_PRIMORDIUS_INTRO,
    MAX_TYPES
};

enum InstanceEvents : uint32
{
    EVENT_NONE,
    EVENT_JINROKH_DOOR,
    EVENT_MOGU_BELLS,
    EVENT_PRIMORDIUS_INTRO
};

enum GlobalToTSpells : uint32
{
    SPELL_BERSERK = 26662,
    SPELL_FOCUSED_LIGHTNING_FIXATE = 137422,
    SPELL_FOCUSED_LIGHTNING_VISUAL = 137425,
};

class notPlayerPredicate
{
public:
    bool operator()(WorldObject* target) const
    {
        return target && (target->GetTypeId() != TYPEID_PLAYER || target->ToPlayer() && target->ToPlayer()->IsGameMaster());
    }
};

enum GlobalActions : int32
{
    ACTION_START_INTRO = 16
};

enum CreaturesIds
{
    /* Encounters */

    BOSS_JINROKH = 69465,
    BOSS_HORRIDON = 68476,

    BOSS_COUNCIL_KAZRAJIN = 69134,
    BOSS_COUNCIL_SUL_THE_SANDCRAWLER = 69078,
    BOSS_COUNCIL_FROST_KING_MALAKK = 69131,
    BOSS_COUNCIL_HIGH_PRIESTESS_MARLI = 69132,

    BOSS_TORTOS = 67977,
    BOSS_MEGAERA = 68065,
    BOSS_JI_KUN = 69712,

    BOSS_DURUMU_THE_FORGOTTEN = 68036,
    BOSS_PRIMORDIUS = 69017,
    BOSS_DARK_ANIMUS = 69427,

    BOSS_IRON_QON = 68078,

    BOSS_LULIN = 68905,
    BOSS_SUEN = 68904,

    BOSS_LEI_SHEN = 68397,
    BOSS_RA_DEN = 69473,

    MOB_WAR_GOD_JALAK = 69374,
    NPC_HORRIDON_EVENT_HELPER = 662203,

    MOB_GARA_JAL = 69135,
    MOB_GARA_JALS_SOUL = 69182,
    NPC_COUNCIL_EVENT_HELPER = 662203,
    NPC_TWISTED_FATE_HELPER = 662204,
    NPC_JINROKH_STATUE = 69467,
    NPC_LEI_SHEN_TRIGGER = 70437,
    NPC_AREATRIGGER_ANIMA = 999288,
    NPC_LULIN = 68905,
    NPC_IRON_QON = 68078,
    NPC_LEI_SHEN = 68397,
};

enum ObjectsIds
{
    GOB_JIN_ROKH_ENTRANCE = 218664,
    GOB_JIN_ROKH_PREDOOR = 218665,
    GOB_JIN_ROKH_EXIT = 218667,
    GOB_HORRIDON_ENTRANCE = 218663,
    GOB_HORRIDON_PREDOOR = 218669,
    GOB_HORRIDON_EXIT = 218666,
    GOB_COUNCIL_ENTRANCE1 = 218655,
    GOB_COUNCIL_ENTRANCE2 = 218656,
    GOB_COUNCIL_EXIT = 218657,
    GOB_TORTOS_DOOR = 218980,
    GOB_TORTOS_COLLISION = 218987,
    GOB_MEGAERA_EXIT = 218746,
    GOB_PRIMORDIUS_ENTRANCE = 218584,
    GOB_PRIMORDIUS_EXIT = 218585,

    GOB_TRIBAL_DOOR_GURUBASHI = 218670,
    GOB_TRIBAL_DOOR_DRAKKARI = 218671,
    GOB_TRIBAL_DOOR_FARRAKI = 218672,
    GOB_TRIBAL_DOOR_AMANI = 218673,

    GOB_MOGU_STATUE_1 = 218675,
    GOB_MOGU_STATUE_2 = 218676,
    GOB_MOGU_STATUE_3 = 218677,
    GOB_MOGU_STATUE_4 = 218678,

    GOB_JIKUN_FEATHER = 218543,
    GOB_MEGAERA_CHEST = 218805,

    GOB_MOGU_BELL = 218723
};

#endif
