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

#include "antorus.h"
#include "AreaTriggerAI.h"
#include "SpellAuraDefines.h"
#include "SpellAuraEffects.h"

enum Says
{
    //Shatug
    SAY_WARN_SIPHON_CORRUPTION = 0,

    //Fharg
    SAY_WARN_ENFLAME_CORRUPTION = 0,
    SAY_WARN_DESOLATE_PATH = 1,
};

enum Spells
{
    SPELL_CONVERS_OUTRO = 249152,
    SPELL_DAILY_ESSENCE_FELHOUNDS = 305308,

    SPELL_DESTROYER_BOON = 244049,
    SPELL_DESTROYER_BOON_ALTER = 244050,
    SPELL_SARGERAS_BLESSING = 246057,
    SPELL_FOCUSING_POWER = 251356,

    //Shatug
    SPELL_CORRUPTING_MAW_AURA = 251447,
    SPELL_CORRUPTING_MAW_DMG = 254760,
    SPELL_DECAY = 245098,
    SPELL_DECAY_DMG = 254383,
    SPELL_CONSUMING_SPHERE_FILTER = 244159,
    SPELL_CONSUMING_SPHERE_AT = 244107,
    SPELL_SIPHON_CORRUPTION = 244056,
    SPELL_SIPHONED_MARK = 248819,
    SPELL_SIPHONED_DMG = 244583,

    //Fharg
    SPELL_FHARG_START_LEAP = 253244,
    SPELL_BURNING_MAW_AURA = 251448,
    SPELL_BURNING_MAW_DMG = 254747,
    SPELL_SMOULDERING = 251445,
    SPELL_SMOULDERING_DMG = 254384,
    SPELL_DESOLATE_PATH_UNK = 244442, //unk aura
    SPELL_DESOLATE_PATH_FILTER = 244441,
    SPELL_DESOLATE_PATH_CHANNEL = 244064,
    SPELL_DESOLATE_PATH_MARK = 244768,
    SPELL_DESOLATE_PATH_CAST = 244825,
    SPELL_DESOLATE_PATH_VISUAL = 244831,
    SPELL_DESOLATE_PATH_VISUAL_CHARGE = 244833,
    SPELL_DESOLATE_PATH_AT = 244767,
    SPELL_ENFLAME_CORRUPTION = 244057,
    SPELL_ENFLAME_CORRUPTION_MARK = 248815,
    SPELL_ENFLAME_CORRUPTION_DMG = 244473,

    ///Heroic+

        //Shatug
        SPELL_WEIGHT_OF_DARKNESS_FILTER = 244069,
        SPELL_WEIGHT_OF_DARKNESS_AT = 254429,
        SPELL_WEIGHT_OF_DARKNESS_MOD_SPEED = 244679,
        SPELL_WEIGHT_OF_DARKNESS_FEAR = 244071,

        //Fharg
        SPELL_MOLTEN_TOUCH_FILTER = 244072,
        SPELL_MOLTEN_TOUCH_TELEPORT = 244084,
        SPELL_MOLTEN_TOUCH_PERIODIC_DUMMY = 244086,
        SPELL_MOLTEN_TOUCH_VISUAL = 244099,
        SPELL_MOLTEN_TOUCH_VISUAL_2 = 244100,
        SPELL_MOLTEN_TOUCH_MARK = 249119,
        SPELL_MOLTEN_TOUCH_CHANNEL = 249227,
        SPELL_MOLTEN_TOUCH_STUN = 249241,
        SPELL_MOLTEN_TOUCH_SINGED = 244091,
        SPELL_MOLTEN_FLARE = 244162,
        SPELL_MOLTEN_FLARE_VISUAL = 244169,

        ///Mythic
        SPELL_DARK_RECONSTITUTION = 249113,
        SPELL_SOULTOUCHED = 251444,
        SPELL_SOULTOUCHED_FILTER = 244053,

        SPELL_FLAMETOUCHED = 244054,
        SPELL_BURNING_FLASH = 245021,
        SPELL_BURNING_REMNANT_AT = 245023,

        SPELL_SHADOWTOUCHED = 244055,
        SPELL_SHADOWSCAR_FILTER = 245149,
        SPELL_SHADOWSCAR_DMG = 245100,
        SPELL_SHADOWSCAR_JUMP = 245151,
        SPELL_CONSUMING_DETONATION_AT = 251366,
};

enum eEvents
{
    //Shatug
    EVENT_CORRUPTING = 1,
    EVENT_CORRUPTING_DMG = 2,
    EVENT_CONSUMING_SPHERE = 3,
    EVENT_SIPHON_CORRUPTION = 4,
    EVENT_WEIGHT_OF_DARKNESS = 5,

    //Fharg
    EVENT_BURNING_MAW = 1,
    EVENT_BURNING_MAW_DMG = 2,
    EVENT_DESOLATE_PATH = 3,
    EVENT_ENFLAME_CORRUPTION = 4,
    EVENT_MOLTEN_TOUCH = 5,
};


enum Miscs
{
    ACTION_1 = 1,
    ACTION_2,
    ACTION_3,
    ACTION_4,
    ACTION_5,
};

void AddSC_boss_felhounds()
{
   
}
