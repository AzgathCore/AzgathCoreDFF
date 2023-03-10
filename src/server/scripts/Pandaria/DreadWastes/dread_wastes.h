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

#ifndef DREAD_WASTES_H
#define DREAD_WASTES_H

enum eSpells
{
    SPELL_BANANARANG                    = 125311,
    SPELL_GOING_BANANAS                 = 125363,
    SPELL_TOSS_FILTH                    = 125365,
    SPELL_UNSTABLE_SERUM                = 127373,
    SPELL_SHA_SPIT                      = 126790,
    SPELL_SHA_SPIT_2                    = 126792,
    SPELL_SLICING_STRIKE                = 126799,
    SPELL_WRATH_OF_THE_EMPRESS          = 128395,
    SPELL_DREAD_SLASH                   = 128022,
    SPELL_SEEK_AND_DESTROY              = 127357,
    SPELL_SEEK_AND_DESTROY_2            = 127358,
    SPELL_SEEK_AND_DESTROY_3            = 127359,
    SPELL_SEEK_AND_DESTROY_POWER        = 127859,
    SPELL_SEEK_AND_DESTROY_WISDOM       = 127860,
    SPELL_SEEK_AND_DESTROY_VELOCITY     = 127861,
    SPELL_POUNCE                        = 119579,
    SPELL_POUNCE_DAMAGE                 = 119578,
    SPELL_RAVAGE                        = 126799,
    SPELL_CHARGE                        = 32323,
    SPELL_MONSTROUS_UNDERBITE           = 127905,
    SPELL_REND                          = 13445,
    SPELL_PINCH_LIMB                    = 124800,
    SPELL_VICIOUS_STRIKES               = 124296,
    SPELL_CLAW                          = 127943,
    SPELL_SONIC_SHOCK                   = 124734,
    SPELL_TAIL_STRIKE                   = 127935,
    SPELL_CORROSIVE_RESIN               = 128425,
    SPELL_BURROW                        = 128104,
    SPELL_CRACKING_STONE                = 128135,
    SPELL_RAISE_EARTH                   = 128107,
    SPELL_DREAD_CLAW                    = 128026,
    SPELL_LASH_OUT_IN_FEAR              = 131375,
    SPELL_SHA_BOLT                      = 131376,
    SPELL_RAPID_SHOT                    = 96259,
    SPELL_SHOOT                         = 130414,
    SPELL_TOXIC_SHOT                    = 82844,
    SPELL_SHA_CORRUPTION                = 128099,
    SPELL_CRUSHING_SHADOWS              = 131704,
    SPELL_RUNE_OF_SHADOWS               = 131696,
    SPELL_SHADOW_POWER                  = 131698,
    SPELL_CHI_BURST                     = 125817,
    SPELL_HEALING_MISTS                 = 125802,
    SPELL_SPINNING_CRANE_KICK           = 125799,
    SPELL_SNAPJAW                       = 79442,
    SPELL_WINDSONG                      = 125373,
    SPELL_BLADE_FURRY                   = 125370,
    SPELL_TORNADO                       = 125398,
    SPELL_TORNADO_DMG                   = 131693,
    SPELL_BELLOWING_RAGE                = 124297,
    SPELL_RUSHING_RAGE                  = 124302,
    SPELL_YAUNGOL_STOMP                 = 124289,
    SPELL_RAIN_DANCE                    = 124860,
    SPELL_TORRENT                       = 124935,
    SPELL_WATER_BOLT                    = 124854,
    SPELL_ICE_TRAP                      = 135382,
    SPELL_FLAME_SHOCK                   = 125062,
    SPELL_LIGHTNING_BOLT                = 79085,
    SPELL_RUPTURE                       = 15583,
    SPELL_SPRINT                        = 66060,
    SPELL_CONSUME_FLESH                 = 127872,
    SPELL_CHAIN_LIGHTNING               = 128123,
    SPELL_CRY_OF_THE_SKY                = 128105,
    SPELL_HUNTER_S_MASK                 = 80016,
    SPELL_SHOOT_2                       = 127870,
    SPELL_BLOODY_RAGE                   = 127955,
    SPELL_SKIN_FLAY                     = 127934,
    SPELL_LIGHTNING_BOLT_2              = 56326,
    SPELL_WATER_SHIELD                  = 34828,
    SPELL_WATER_SHIELD_2                = 127939,
    SPELL_HORIFIC_VISAGE                = 138040,
    SPELL_METEOR_SHOWER                 = 138042,
    SPELL_SCARAB_SWARM                  = 138036,
    SPELL_THUNDER_CRUSH                 = 138044,
    SPELL_VENGEFUL_SPIRIT               = 138043
};

enum eEvents
{
    EVENT_BANANARANG                        = 1,
    EVENT_GOING_BANANAS                     = 2,
    EVENT_TOSS_FILTH                        = 3,
    EVENT_UNSTABLE_SERUM                    = 4,
    EVENT_SHA_SPIT                          = 5,
    EVENT_SHA_SPIT_2                        = 6,
    EVENT_SLICING_STRIKE                    = 7,
    EVENT_WRATH_OF_THE_EMPRESS              = 8,
    EVENT_DREAD_SLASH                       = 10,
    EVENT_SEEK_AND_DESTROY                  = 11,
    EVENT_SEEK_AND_DESTROY_2                = 12,
    EVENT_SEEK_AND_DESTROY_3                = 13,
    EVENT_POUNCE                            = 14,
    EVENT_RAVAGE                            = 15,
    EVENT_CHARGE_2                          = 17,
    EVENT_MONSTROUS_UNDERBITE               = 18,
    EVENT_REND                              = 19,
    EVENT_PINCH_LIMB                        = 20,
    EVENT_VICIOUS_STRIKES                   = 21,
    EVENT_CLAW                              = 22,
    EVENT_SONIC_SHOCK                       = 23,
    EVENT_TAIL_STRIKE                       = 24,
    EVENT_DREAD_SLASH_2                     = 25,
    EVENT_TAIL_STRIKE_2                     = 26,
    EVENT_CLAW_2                            = 27,
    EVENT_CORROSIVE_RESIN                   = 28,
    EVENT_BURROW                            = 29,
    EVENT_CRACKING_STONE                    = 30,
    EVENT_RAISE_EARTH                       = 31,
    EVENT_UNAURA_BURROW                     = 32,
    EVENT_DREAD_CLAW                        = 32,
    EVENT_LASH_OUT_IN_FEAR                  = 34,
    EVENT_SHA_BOLT                          = 35,
    EVENT_RAPID_SHOT                        = 36,
    EVENT_SHOOT                             = 37,
    EVENT_TOXIC_SHOT                        = 38,
    EVENT_SHA_CORRUPTION                    = 39,
    EVENT_CRUSHING_SHADOWS                  = 40,
    EVENT_RUNE_OF_SHADOWS                   = 41,
    EVENT_SHADOW_POWER                      = 42,
    EVENT_CHI_BURST                         = 43,
    EVENT_HEALING_MISTS                     = 44,
    EVENT_SPINNING_CRANE_KICK               = 45,
    EVENT_SNAPJAW                           = 46,
    EVENT_SNAPJAW_2                         = 47,
    EVENT_BLADE_FURRY                       = 48,
    EVENT_TORNADO                           = 49,
    EVENT_BELLOWING_RAGE                    = 50,
    EVENT_RUSHING_RAGE                      = 51,
    EVENT_YAUNGOL_STOMP                     = 52,
    EVENT_RAIN_DANCE                        = 53,
    EVENT_TORRENT                           = 54,
    EVENT_WATER_BOLT                        = 55,
    EVENT_ICE_TRAP                          = 56,
    EVENT_START_COMBAT                      = 57,
    EVENT_HISEK_TALK_1                      = 58,
    EVENT_HISEK_TALK_2                      = 59,
    EVENT_HISEK_TALK_3                      = 60,
    EVENT_HISEK_TALK_4                      = 31,
    EVENT_HISEK_TALK_5                      = 62,
    EVENT_TRAITOR_TALK_1                    = 63,
    EVENT_TRAITOR_TALK_2                    = 64,
    EVENT_TRAITOR_TALK_3                    = 65,
    EVENT_TRAITOR_TALK_4                    = 66,
    EVENT_TRAITOR_TALK_5                    = 67,
    EVENT_CHECK_PLAYERS                     = 68,
    EVENT_RUPTURE                           = 69,
    EVENT_SPRINT                            = 70,
    EVENT_UNSTABLE_SERUM_22                 = 71,
    EVENT_CONSUME_FLESH                     = 72,
    EVENT_UNSTABLE_SERUM_23                 = 73,
    EVENT_FLAME_SHOCK                       = 74,
    EVENT_LIGHTNING_BOLT                    = 75,
    EVENT_UNSTABLE_SERUM_24                 = 76,
    EVENT_START_WALKING                     = 77,
    EVENT_CHAIN_LIGHTNING                   = 78,
    EVENT_CRY_OF_THE_SKY                    = 79,
    EVENT_HUNTER_S_MASK                     = 80,
    EVENT_BLOODY_RAGE                       = 81,
    EVENT_SKIN_FLAY                         = 82,
    EVENT_LIGHTNING_BOLT_2                  = 83,
    EVENT_WATER_SHIELD                      = 84,
    EVENT_WATER_SHIELD_2                    = 85,
    EVENT_HORIFIC_VISAGE                    = 86,
    EVENT_METEOR_SHOWER                     = 87,
    EVENT_SCARAB_SWARM                      = 88,
    EVENT_THUNDER_CRUSH                     = 89,
    EVENT_VENGEFUL_SPIRIT                   = 90
};

enum eQuests
{
    QUEST_CORRUPTION_RUNS_DEEP       = 31441,
    QUEST_DROPPING_OUR_SIGNAL        = 31439,
    QUEST_PRESERVED_IN_AMBER         = 31004,
    QUEST_SKEER_THE_BLOODSEEKER      = 31175,
    QUEST_IN_HER_CLUTCH              = 31010,
    QUEST_EXTENDING_OUR_COVERAGE     = 31087,
    QUEST_BY_THE_SEA_NEVERMORE       = 31682,
    QUEST_BY_THE_SEA_NEVERMORE_2     = 31089,
    QUEST_FREE_FROM_HER_CLUTCHES     = 31494,
    QUEST_REUNITED                   = 31091,
    QUEST_THE_SCENT_OF_BLOOD         = 31179
};

enum eActions
{
    ACTION_START_SPEAKING = 1,
    ACTION_START_COMBAT   = 2,
    ACTION_SPAWNS         = 3
};

enum eCreatures
{
    MOB_TORNADO                           = 64267,
    MOB_HISEK_THE_SWARMKEEPER             = 64705,
    MOB_SECOND_HISEK_THE_SWARMKEEPER      = 64672,
    MOB_KLAXXI_TRAITOR                    = 64583,
    MOB_HISEK_THE_SWARMKEEPER_KILL_CREDIT = 64645,
    MOB_KIL_RUK_THE_WIND_REAVER           = 62357,
    MOB_SKEER_THE_BLOODSEEKER             = 63359,
    MOB_MALIK_THE_UNSCATHED               = 62752,
    MOB_DISCOVER_AMBERGLOW_BUNNY          = 65328,
    MOB_KAZ_TIK_THE_MANIPULATOR           = 64013,
    MOB_SECOND_KAZ_TIK_THE_MANIPULATOR    = 62540,
    MOB_KUNCHONG_HATCHLING                = 64849,
    MOB_MUCKSCALE_RIPPER                  = 64197,
    MOB_THIRD_KAZ_TIK_THE_MANIPULATOR     = 63876,
    MOB_KOVOK                             = 62542,
    MOB_MUCKSCALE_FLESHEATER              = 63465,
    MOB_MUCKSCALE_SERPENTUS               = 63466
};

#endif
