/*
 * Copyright 2023 AzgathCore
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 *  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef BLACK_ROOK_HOLD_H_
#define BLACK_ROOK_HOLD_H_

enum eData
{
    DATA_AMALGAM = 0,
    DATA_ILLYSANNA = 1,
    DATA_SMASHSPITE = 2,
    DATA_KURTALOS = 3,
    MAX_ENCOUNTER,

    DATA_KURTALOS_STATE,
    DATA_AMALGAM_OUTRO,
    DATA_ILLYSANNA_INTRO,

    DATA_STAIRS_BOULDER_1,
    DATA_STAIRS_BOULDER_2,

    DATA_SMASHSPITE_FEL_BAT_EVENT
};

enum eCreatures
{
    //Other
    NPC_BOULDER = 111706,
    NPC_FELSPITE_DOMINATOR = 102788,
    NPC_EVENT_FEL_BAT = 102781,

    //Amalgam of Souls
    NPC_SOUL_ECHOES_STALKER = 99090,
    NPC_RESTLESS_SOUL = 99664,

    //Illysanna
    NPC_ILLYSANNA_RAVENCREST = 98696,
    NPC_COMMANDER_SHEMDAHSOHN = 98706,
    NPC_INTRO_RISEN_ARCHER = 98275,
    NPC_INTRO_RISEN_ARCANIST = 98280,
    NPC_INTRP_RISEN_SCOUT = 98691,
    NPC_EYE_BEAM_STALKER = 100436,
    NPC_SOUL_TORN_VANGUARD = 100485,
    NPC_RISEN_ARCANIST = 100486,

    //Smashspite
    NPC_FEL_BAT = 100759,

    //Kurtalos
    NPC_KURTALOS = 98965,
    NPC_LATOSIUS = 98970,
    NPC_DANTALIONAX = 99611,
    NPC_SOUL_KURTALOS = 101054,
    NPC_IMAGE_OF_LATOSIUS = 101028,
    NPC_KURTALOS_BLADE_TRIGGER = 100861, //Cast AT 198782
    NPC_CLOUD_OF_HYPNOSIS = 100994,
    NPC_STINGING_SWARM = 101008,
};

enum eGameObjects
{
    GO_AMALGAM_DOOR_1 = 247403,
    GO_AMALGAM_DOOR_2 = 247404,
    GO_AMALGAM_DOOR_3 = 247405,
    GO_AMALGAM_DOOR_4 = 247406,
    GO_AMALGAM_DOOR_EXIT = 247407,
    GO_ILLYSANNA_DOOR_1 = 247401,
    GO_ILLYSANNA_DOOR_2 = 247399,
    GO_ILLYSANNA_DOOR_3 = 247400,
    GO_ILLYSANNA_DOOR_4 = 245079,
    GO_ILLYSANNA_DOOR_5 = 245080,
    GO_SMASHSPITE_DOOR = 247402,
    GO_SMASH_KURT_DOOR_1 = 245104,
    GO_SMASH_KURT_DOOR_2 = 245105,
    GO_KURTALOS_DOOR = 247498,
};

Position const mashFelBatPos[3] =
{
    {3237.47f, 7324.17f, 232.0f, 1.37f},
    {3240.16f, 7323.82f, 232.0f, 1.48f},
    {3243.01f, 7323.69f, 232.0f, 1.43f}
};

#endif
