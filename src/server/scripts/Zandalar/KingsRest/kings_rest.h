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

#include "GameObject.h"

#ifndef KINGS_REST
#define KINGS_REST

#define DataHeader "KR"

uint32 const EncounterCount = 5;

enum Data
{
    DATA_GOLDEN_SERPENT = 1,
    DATA_MCHIMBA,
    DATA_COUNCIL,
    DATA_DAZAR
};

enum Creatures
{
    NPC_KULA_THE_BUTCHER = 135475,
    NPC_AKALI_THE_CONQUEROR = 135470,
    NPC_ZANAZAL_THE_WISE = 135472,
    NPC_EXPLOSIVE_TOTEM = 135764,
    NPC_THUNDERING_TOTEM = 135761,
    NPC_TORRENT_TOTEM = 135765,
    NPC_EARTHWALL_TOTEM = 135759,
    NPC_SHADOW_OF_ZUL = 138489,
    NPC_MINION_OF_ZUL = 133943,
    NPC_POOL_OF_DARKNESS = 138250,
    NPC_REBAN = 136984,
    NPC_TZALA = 136976,
    NPC_DAZAR = 136160,
};

enum Gameobjects
{
    GO_COFFIN = 289642,
    GO_THE_COUNCILS_CACHE = 288637,
    GO_BOON_OF_THE_FIRST_KING = 288638,
};

#endif // KINGS_REST
