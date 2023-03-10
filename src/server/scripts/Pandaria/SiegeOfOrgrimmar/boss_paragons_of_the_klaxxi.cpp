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

#include "siege_of_orgrimmar.hpp"
#include "SpellAuraEffects.h"
#include "Player.h"

// Information:
// 1. There are many spells that have triggers after 'jump' effects.
// Those triggers are handled in the core but not in the 'movementinform' function.
// 2. We don't use 'death from above' jump spells, we use jumps manually to prevent some bugs (targetting, speed and etc.).
// 3. We don't spawn hungry kunchongs randomly, we use const positions because of some bugs in vmaps.

// TODO:
// Use spells instead of manual summons of paragons and the fightstarter.
// Change fist paragons every week.
// Make random spawns of hungry kunchongs
// Make player buffs gained from mantids

enum ScriptedTexts
{
    SAY_KILRUK_AGGRO = 0,
    SAY_KILRUK_DEATH = 1,
    SAY_KILRUK_WIPE = 2,
    SAY_KILRUK_INTRO = 3,
    SAY_KILRUK_KILL = 4,
    SAY_KILRUK_SPELL = 5,

    SAY_XARIL_AGGRO = 0,
    SAY_XARIL_DEATH = 1,
    SAY_XARIL_WIPE = 2,
    SAY_XARIL_INTRO = 3,
    SAY_XARIL_KILL = 4,
    SAY_XARIL_SPELL = 5,

    SAY_KAZTIK_AGGRO = 0,
    SAY_KAZTIK_DEATH = 1,
    SAY_KAZTIK_WIPE = 2,
    SAY_KAZTIK_INTRO = 3,
    SAY_KAZTIK_KILL = 4,
    SAY_KAZTIK_SPELL = 5,

    SAY_KORVEN_AGGRO = 0,
    SAY_KORVEN_DEATH = 1,
    SAY_KORVEN_WIPE = 2,
    SAY_KORVEN_INTRO = 3,
    SAY_KORVEN_KILL = 4,
    SAY_KORVEN_SPELL = 5,

    SAY_IYYOKUK_AGGRO = 0,
    SAY_IYYOKUK_DEATH = 1,
    SAY_IYYOKUK_WIPE = 2,
    SAY_IYYOKUK_INTRO = 3,
    SAY_IYYOKUK_KILL = 4,
    SAY_IYYOKUK_SPELL = 5,

    SAY_KAROZ_AGGRO = 0,
    SAY_KAROZ_DEATH = 1,
    SAY_KAROZ_WIPE = 2,
    SAY_KAROZ_INTRO = 3,
    SAY_KAROZ_KILL = 4,
    SAY_KAROZ_SPELL = 5,

    SAY_SKEER_AGGRO = 0,
    SAY_SKEER_DEATH = 1,
    SAY_SKEER_WIPE = 2,
    SAY_SKEER_INTRO = 3,
    SAY_SKEER_KILL = 4,
    SAY_SKEER_SPELL = 5,

    SAY_RIKKAL_AGGRO = 0,
    SAY_RIKKAL_DEATH = 1,
    SAY_RIKKAL_WIPE = 2,
    SAY_RIKKAL_INTRO = 3,
    SAY_RIKKAL_KILL = 4,
    SAY_RIKKAL_SPELL = 5,

    SAY_HISEK_AGGRO = 0,
    SAY_HISEK_DEATH = 1,
    SAY_HISEK_WIPE = 2,
    SAY_HISEK_INTRO = 3,
    SAY_HISEK_KILL = 4,
    SAY_HISEK_SPELL = 5,
};

enum Spells
{
    SPELL_ACHIEVEMENT = 148512,
    SPELL_ZERO_ENERGY = 72242,

    // Controller spells
    SPELL_THE_KLAXXI_PARAGONS = 146983,
    SPELL_BERSERK = 146982, // triggered by 146983 after 720 seconds (periodic)
    SPELL_SUMMON_FIGHT_STARTER = 143552,
    SPELL_SUMMON_PARAGONS = 141804,
    SPELL_SUMMON_PARAGON_KILRUK = 141803, // 1589.198, -5701.658, -270.516
    SPELL_SUMMON_PARAGON_XARIL = 141800, // 1602.252, -5765.936, -291.0546
    SPELL_SUMMON_PARAGON_KAZTIK = 141799, // 1561.88, -5608.125, -291.0987
    SPELL_SUMMON_PARAGON_KORVEN = 141798, // 1650.016, -5732.452, -291.0862
    SPELL_SUMMON_PARAGON_IYYOKUK = 141802, // 1570.316, -5674.297, -270.566
    SPELL_SUMMON_PARAGON_KAROZ = 141797, // 1552.964, -5640.806, -291.1562
    SPELL_SUMMON_PARAGON_SKEER = 141795, // 1608.894, -5740.578, -290.9958
    SPELL_SUMMON_PARAGON_RIKKAL = 141801, // 1624.321, -5730.018, -291.0036
    SPELL_SUMMON_PARAGON_HISEK = 141796, // 1519.401, -5637.149, -291.1007
    SPELL_PING_AURA = 144354, // from sniffs
    SPELL_PING = 144353, // triggered by 144354, target players
    SPELL_READY_TO_FIGHT = 143542,
    SPELL_BEEN_CLICKED = 144834, // when a player clicks on

    // Fight Starter
    SPELL_COSMETIC_FOR_FIGHT_STARTER = 143548,

    // Shared spells
    SPELL_MANTID_WINGS = 132441, // triggered by klaxxi auras
    SPELL_JUMP_TO_CENTER = 143545,
    SPELL_PARAGONS_PURPOSE_AURA = 143482,
    SPELL_PARAGONS_PURPOSE_HEAL = 143483,
    SPELL_DEFEATED = 142292,
    SPELL_DESPAWN_AREATRIGGERS = 138175,

    // Kil'ruk the Wind-reaver
    SPELL_KILRUK_THE_WIND_REAVER = 142926,
    SPELL_RAZOR_SHARP_BLADES = 142918,
    SPELL_RAZOR_SHARP_BLADES_DMG = 142922,
    SPELL_EXPOSED_VEINS = 142931,
    SPELL_GOUGE = 143939,
    SPELL_MUTILATE = 143941,
    SPELL_DEATH_FROM_ABOVE_SUMMON = 142263,
    SPELL_DEATH_FROM_ABOVE_JUMP_1 = 142264, // the boss jumps up
    SPELL_DEATH_FROM_ABOVE_JUMP_2 = 142265, // the boss jumps down
    SPELL_DEATH_FROM_ABOVE_DMG = 142232,
    SPELL_DEATH_FROM_ABOVE_MARK = 144126,
    SPELL_REAVE_AOE = 148677, // target players
    SPELL_REAVE = 148681,
    SPELL_REAVE_AURA = 148676,
    SPELL_REAVE_DMG = 142228,

    // Xaril the Poisoned Mind
    SPELL_XARIL_THE_POISONED_MIND = 142932,
    SPELL_TENDERIZING_STRIKES = 142927,
    SPELL_TENDERIZING_STRIKES_DMG = 142929,
    SPELL_CLEAR_TENDERIZING_STRIKES = 144122, // cannot find in sniffs
    SPELL_CAUSTIC_BLOOD = 142315,
    SPELL_BLOODY_EXPLOSION_DUMMY = 142782,
    SPELL_BLOODY_EXPLOSION_DMG = 142317,
    SPELL_TOXIC_INJECTION = 142528,
    SPELL_TOXIN_BLUE = 142532,
    SPELL_TOXIN_RED = 142533,
    SPELL_TOXIN_YELLOW = 142534,
    SPELL_CATALYST_BLUE = 142725,
    SPELL_CATALYST_RED = 142726,
    SPELL_CATALYST_YELLOW = 142727,
    SPELL_CATALYST_ORANGE = 142728,
    SPELL_CATALYST_GREEN = 142730,
    SPELL_CATALYST_PURPLE = 142729,
    SPELL_REACTION_BLUE = 142735,
    SPELL_REACTION_RED = 142736,
    SPELL_REACTION_YELLOW = 142737,
    SPELL_REACTION_ORANGE = 142738,
    SPELL_REACTION_GREEN = 142740,
    SPELL_REACTION_PURPLE = 142739,
    SPELL_NOXIOUS_VAPORS = 142797,
    SPELL_EERIE_FOG_AURA = 142812,
    SPELL_EERIE_FOG_SUMMON = 142813,
    SPELL_EERIE_FOG_DMG = 142945,
    SPELL_CANNED_HEAT = 143570,
    SPELL_CANNED_HEAT_AURA = 143572,
    SPELL_CANNED_HEAT_AREATRIGGER = 143575,
    SPELL_CANNED_HEAT_DMG = 143576,

    // Kaz'tik the Manipulator
    SPELL_SONIC_PROJECTION_AOE = 143778, // targets players
    SPELL_SONIC_PROJECTION_AREATRIGGER = 143765,
    SPELL_SONIC_PROJECTION_DMG = 143768,
    SPELL_SUMMON_HUNGRY_KUNCHONG = 146891, // is not found in sniffs
    SPELL_MESMERIZE_AOE = 142668, // targets
    SPELL_MESMERIZE = 142671,

    // Hungry Kunchong
    SPELL_SWIPE = 142655,
    SPELL_MOLT = 142651, // after eating players (after devour?)
    SPELL_DEVOUR_1 = 142649,
    SPELL_DEVOUR_2 = 142705,
    SPELL_ENERGIZE = 142645, // triggered by 142649 periodicaly
    SPELL_HUNGRY = 142630,
    SPELL_DEVOUR_KILL = 142638, // triggered by 142630 periodicaly
    SPELL_DEVOUR_AURA = 142636, // marks the target for devour (142638)
    SPELL_THICK_SHELL = 142667,

    // Korven the Prime
    SPELL_ENCASE_IN_AMBER = 142564,
    SPELL_AMBER_REGENERATION = 144119,
    SPELL_AMBER_BARRIER = 144120,
    SPELL_SHIELD_BASH = 143974,
    SPELL_VICIOUS_ASSAULT_PERIODIC = 143977, // triggered by 143974
    SPELL_VICIOUS_ASSAULT_BLEED = 143979,
    SPELL_VICIOUS_ASSAULT_DMG_1 = 143981,
    SPELL_VICIOUS_ASSAULT_DMG_2 = 143982,
    SPELL_VICIOUS_ASSAULT_DMG_3 = 143983,
    SPELL_VICIOUS_ASSAULT_DMG_4 = 143984,
    SPELL_VICIOUS_ASSAULT_DMG_5 = 143985,

    // Iyyokuk the Lucid
    SPELL_GREEN_MANTID_WINGS = 126316,
    SPELL_DIMINISH = 143666,
    SPELL_RED_MANTID = 143620,
    SPELL_PURPLE_MANTID = 143621,
    SPELL_BLUE_MANTID = 143622,
    SPELL_GREEN_MANTID = 143623,
    SPELL_YELLOW_MANTID = 143624,
    SPELL_RED_SWORD = 143605,
    SPELL_PURPLE_SWORD = 143606,
    SPELL_BLUE_SWORD = 143607,
    SPELL_GREEN_SWORD = 143608,
    SPELL_YELLOW_SWORD = 143609,
    SPELL_RED_STAFF = 143627,
    SPELL_PURPLE_STAFF = 143628,
    SPELL_BLUE_STAFF = 143629,
    SPELL_GREEN_STAFF = 143630,
    SPELL_YELLOW_STAFF = 143631,
    SPELL_RED_DRUM = 143610,
    SPELL_PURPLE_DRUM = 143611,
    SPELL_BLUE_DRUM = 143612,
    SPELL_GREEN_DRUM = 143613,
    SPELL_YELLOW_DRUM = 143614,
    SPELL_RED_BOMB = 143615,
    SPELL_PURPLE_BOMB = 143616,
    SPELL_BLUE_BOMB = 143617,
    SPELL_GREEN_BOMB = 143618,
    SPELL_YELLOW_BOMB = 143619,
    SPELL_CALCULATED = 144095,
    SPELL_INSANE_CALCULATION_FIERY_EDGE = 142416,
    SPELL_FIERY_EDGE_DUMMY_1 = 142808, // main beam
    SPELL_FIERY_EDGE_DUMMY_2 = 142811, // prepare for main beam
    SPELL_FIERY_EDGE_DMG = 142809,

    // Ka'roz the Locust
    SPELL_STORE_KINETIC_ENERGY = 143709,
    SPELL_FLASH_AURA = 143700,
    SPELL_FLASH_CHARGE = 143704,
    SPELL_FLASH_DMG = 148594,
    SPELL_PICK_CHARGE_TARGET = 143710, // triggered by 148594
    SPELL_WHIRLING = 143701,
    SPELL_WHIRLING_DMG = 143702,
    SPELL_DASH = 143722,
    SPELL_LEAP = 143693, // triggered by 143722
    SPELL_HURL_AMBER_PERIODIC = 143759, // triggered by 143693
    SPELL_HURL_AMBER_AOE = 143761, // targets players
    SPELL_HURL_AMBER_MISSILE = 143733,
    SPELL_CAUSTIC_AMBER_AREATRIGGER = 143740,
    SPELL_CAUSTIC_AMBER_DMG = 143735,
    SPELL_STRONG_LEGS_BUFF = 141853,
    SPELL_STRONG_LEGS_OVERRIDE = 143963,
    SPELL_STRONG_LEGS_JUMP_1 = 143964,
    SPELL_STRONG_LEGS_JUMP_2 = 148608,
    SPELL_STRONG_LEGS_DUMMY = 148650, // ?
    // There is a spell '143965' that don't exists in spell.dbc. I think it's used to give 143966 spell to players.
    SPELL_HURL_AMBER_MISSILE_2 = 143966, // used by players
    SPELL_CAUSTIC_AMBER_DMG_2 = 143967,

    // Skeer the Bloodseeker
    SPELL_HEWER_OF_FOES = 143273,
    SPELL_HEW = 143274,
    SPELL_HEWN_DMG = 143275,
    SPELL_CLEAR_HEWN = 144124,
    SPELL_LONG_REACH = 144325,
    SPELL_BLOODLETTING = 143280,
    SPELL_BLOODLETTING_MISSILE_SELF = 143282,
    SPELL_BLOODLETTING_MISSILE_1 = 143284,
    SPELL_BLOODLETTING_MISSILE_2 = 143287,
    SPELL_BLOODLETTING_MISSILE_3 = 143288,
    SPELL_BLOODLETTING_MISSILE_4 = 143289,
    SPELL_BLOODLETTING_SUMMON = 143283,
    SPELL_GROW = 44833, // from sniffs
    SPELL_BLOOD_INFUSION = 143294,

    // Rik'kal the Dissector
    SPELL_MAD_SCIENTIST = 143277,
    SPELL_GENETIC_ALTERATION = 143278,
    SPELL_GENETIC_ALTERATION_DMG = 143279,
    SPELL_CLEAR_GENETIC_ALTERATION = 144123,
    SPELL_INJECTION = 143340,
    SPELL_INJECTION_MISSILE = 143383,
    SPELL_INJECTION_DUMMY = 143339,
    SPELL_BIRTH = 143379, // triggered by 143383
    SPELL_HUNGER = 143358,
    SPELL_FEED = 143362,
    SPELL_GENETIC_MODIFICATIONS = 143355,
    SPELL_REGENERATE = 143356,
    SPELL_MUTATE_AOE = 143336,
    SPELL_MUTATE = 143337,
    SPELL_FAULTY_MUTATION = 148589,
    SPELL_FAULTY_MUTATION_DMG = 148587,
    SPELL_CLAW = 143338,
    SPELL_SWIPE_DMG = 143378,
    SPELL_STING = 143376,
    SPELL_PREY = 144286,

    // Hisek the Swarmkeeper
    SPELL_MULTI_SHOT = 144839,
    SPELL_AIM_AOE = 142948,
    SPELL_POINT_BLANK_SHOT = 143505,
    SPELL_AIM_ROOT = 143505,
    SPELL_FIRE = 142950,
    SPELL_RAPID_FIRE = 143243,
    SPELL_SONIC_PULSE_32 = 143226, // with 32 sec duration
    SPELL_SONIC_PULSE_30 = 143227,
    SPELL_SONIC_PULSE_28 = 143228,
    SPELL_SONIC_PULSE_26 = 143229,
    SPELL_SONIC_PULSE_24 = 143230,
    SPELL_SONIC_PULSE_22 = 143231,
    SPELL_SONIC_PULSE_20 = 143232,
    SPELL_SONIC_PULSE_18 = 143233,
    SPELL_SONIC_PULSE_16 = 143234,
    SPELL_SONIC_PULSE_14 = 143236,
    SPELL_SONIC_PULSE_12 = 143237,
    SPELL_SONIC_PULSE_10 = 143238,
    SPELL_SONIC_PULSE_DMG = 143240,
};

#define FIERY_EDGE_DAMAGE_MIN 30000
#define FIERY_EDGE_DAMAGE_MAX 100000
#define FIERY_EDGE_DAMAGE_DIST_MAX 30.f

enum Adds
{
    NPC_MANTID_AMBER = 71628, // is used as fight starter
    NPC_IMPACT_JUMP_TARGET = 71309, // is used as the target for 'Death From Above'
    NPC_HUNGRY_KUNCHONG = 71420, // is spawned by 'Summon Hungry Kunchong'
    NPC_AMBER = 71407, // is spawned by 'Encase In Amber'
    NPC_BLOOD = 71542, // is spawned by 'Bloodletting'
    NPC_AMBER_PARASITE = 71578, // is spawned by 'Birth'
    NPC_AMBER_BOMB = 71691, // used to be thrown by players
    NPC_EERIE_FOG = 71453,
};

enum Events
{
    EVENT_CHECK_PLAYERS = 1,

    // Kil'ruk the Wind-reaver
    EVENT_GOUGE,
    EVENT_DEATH_FROM_ABOVE,
    EVENT_REAVE,

    // Xaril the Poisoned Mind
    EVENT_CATALYST,

    // Kaz'tik the Manipulator
    EVENT_SONIC_PROJECTION,
    EVENT_KUNCHONGS,
    EVENT_MESMERIZE,
    EVENT_SWIPE,

    // Korven the Prime
    EVENT_SHIELD_BASH,
    EVENT_ENCASE_IN_AMBER,

    // Iyyokuk the Lucid
    EVENT_DIMINISH,
    EVENT_INSANE_CALCULATION,

    // Ka'roz the Locust
    EVENT_FLASH,
    EVENT_HURL_AMBER,
    EVENT_HURL_AMBER_END,

    // Skeer the Bloodseeker
    EVENT_BLOODLETTING,
    EVENT_CHANGE_TARGET,

    // Rik'kal the Dissector
    EVENT_HUNGER,
    EVENT_FEED,
    EVENT_MUTATE,

    // Hisek the Swarmkeeper
    EVENT_MULTI_SHOT,
    EVENT_AIM,
    EVENT_RAPID_FIRE,
};

enum Timers
{
    TIMER_CHECK_PLAYERS = 10 * IN_MILLISECONDS,
    PARAGONS_PURPOSE_TIMER = 50 * IN_MILLISECONDS, // for heroic

    // Kil'ruk the Wind-reaver
    TIMER_GOUGE_FIRST = 10 * IN_MILLISECONDS,
    TIMER_GOUGE = 20 * IN_MILLISECONDS,
    TIMER_DEATH_FROM_ABOVE_FIRST = 20 * IN_MILLISECONDS,
    TIMER_DEATH_FROM_ABOVE = 34 * IN_MILLISECONDS,
    TIMER_REAVE_FIRST = 33 * IN_MILLISECONDS,
    TIMER_REAVE = 38 * IN_MILLISECONDS,

    // Xaril the Poisoned Mind
    TIMER_CATALYST_FIRST = 20 * IN_MILLISECONDS,
    TIMER_CATALYST = 33 * IN_MILLISECONDS,

    // Kaz'tik the Manipulator
    TIMER_KUNCHONGS = 2 * IN_MILLISECONDS,
    TIMER_SONIC_PROJECTION_FIRST = 8 * IN_MILLISECONDS,
    TIMER_SONIC_PROJECTION = 20 * IN_MILLISECONDS,
    TIMER_MESMERIZE_FIRST = 20 * IN_MILLISECONDS,
    TIMER_MESMERIZE = 34 * IN_MILLISECONDS,
    TIMER_SWIPE_FIRST = 8 * IN_MILLISECONDS,
    TIMER_SWIPE = 25 * IN_MILLISECONDS,

    // Korven the Prime
    TIMER_SHIELD_BASH_FIRST = 20 * IN_MILLISECONDS,
    TIMER_SHIELD_BASH = 17 * IN_MILLISECONDS,
    TIMER_ENCASE_IN_AMBER_FIRST = 30 * IN_MILLISECONDS,
    TIMER_ENCASE_IN_AMBER = 30 * IN_MILLISECONDS,

    // Iyyokuk the Lucid
    TIMER_DIMINISH_FIRST = 15 * IN_MILLISECONDS,
    TIMER_DIMINISH = 20 * IN_MILLISECONDS,
    TIMER_INSANE_CALCULATION_MIN = 25 * IN_MILLISECONDS,
    TIMER_INSANE_CALCULATION_MAX = 50 * IN_MILLISECONDS,

    // Ka'roz the Locust
    TIMER_FLASH_FIRST = 15 * IN_MILLISECONDS,
    //TIMER_FLASH                     = 62 * IN_MILLISECONDS,
    //TIMER_HURL_AMBER_FIRST          = 40 * IN_MILLISECONDS,
    //TIMER_HURL_AMBER                = 62 * IN_MILLISECONDS,
    TIMER_FLASH = 30 * IN_MILLISECONDS,
    TIMER_HURL_AMBER = 30 * IN_MILLISECONDS,
    TIMER_HURL_AMBER_END = 5 * IN_MILLISECONDS,

    // Skeer the Bloodseeker
    TIMER_BLOODLETTING_FIRST = 6 * IN_MILLISECONDS,
    TIMER_BLOODLETTING = 35 * IN_MILLISECONDS,

    // Rik'kal the Dissector
    TIMER_HUNGER = 1 * IN_MILLISECONDS,
    TIMER_FEED_FIRST = 1 * IN_MILLISECONDS,
    TIMER_FEED = 10 * IN_MILLISECONDS,
    TIMER_MUTATE_FIRST = 23 * IN_MILLISECONDS,
    TIMER_MUTATE = 32 * IN_MILLISECONDS,

    // Hisek the Swarmkeeper
    TIMER_MULTI_SHOT_FIRST = 2 * IN_MILLISECONDS,
    TIMER_MULTI_SHOT = 5 * IN_MILLISECONDS,
    TIMER_AIM_FIRST = 32 * IN_MILLISECONDS,
    TIMER_AIM = 40 * IN_MILLISECONDS,
    TIMER_RAPID_FIRE = 47 * IN_MILLISECONDS,
};

enum Actions
{
    ACTION_BEGIN_BATTLE = 1,
    ACTION_NEXT_BATTLE,
    ACTION_RESET_BATTLE,
    ACTION_FINISH_BATTLE,
    ACTION_MARK_NEXT_PARAGON,
    ACTION_PARAGON_DEFEATED,

    ACTION_MESMERIZE,
    ACTION_DEVOUR,
};

enum eData : int
{
    DATA_PARAGON_IN_FIGHT = 1,
    DATA_DEATH_FROM_ABOVE_GUID,
    DATA_ENCASE_AMBER_GUID,
    DATA_ENCASE_AMBER_TARGET_ENABLE,
    DATA_ALL_PARAGONS_DIED,
};

enum Points : int
{
    POINT_DEATH_FROM_ABOVE_1 = 1,
    POINT_DEATH_FROM_ABOVE_2,
    POINT_HURL_AMBER,
};

enum ParagonTypes
{
    PARAGON_KILRUK,
    PARAGON_XARIL,
    PARAGON_KAZTIK,
    PARAGON_KORVEN,
    PARAGON_IYYOKUK,
    PARAGON_KAROZ,
    PARAGON_SKEER,
    PARAGON_RIKKAL,
    PARAGON_HISEK,

    PARAGON_COUNT,
};

// TODO: maybe need to make random sequence
// http://wow.gamepedia.com/Paragons_of_the_Klaxxi#Activation_Order
const ParagonTypes paragonsSequence[PARAGON_COUNT] =
{
    PARAGON_SKEER,
    PARAGON_RIKKAL,
    PARAGON_HISEK,
    PARAGON_KAROZ,
    PARAGON_KORVEN,
    PARAGON_IYYOKUK,
    PARAGON_XARIL,
    PARAGON_KAZTIK,
    PARAGON_KILRUK
};

const uint32 paragonsEntries[PARAGON_COUNT] =
{
    NPC_KILRUK_THE_WIND_REAVER,
    NPC_XARIL_THE_POISONED_MIND,
    NPC_KAZTIK_THE_MANIPULATOR,
    NPC_KORVEN_THE_PRIME,
    NPC_IYYOKUK_THE_LUCID,
    NPC_KAROZ_THE_LOCUST,
    NPC_SKEER_THE_BLOODSEEKER,
    NPC_RIKKAL_THE_DISSECTOR,
    NPC_HISEK_THE_SWARMKEEPER
};

#define INSANE_CALCULATION_SPELLS_COUNT 25
const uint32 insaneCalculationSpells[INSANE_CALCULATION_SPELLS_COUNT] =
{
    SPELL_RED_MANTID,
    SPELL_PURPLE_MANTID,
    SPELL_BLUE_MANTID,
    SPELL_GREEN_MANTID,
    SPELL_YELLOW_MANTID,
    SPELL_RED_SWORD,
    SPELL_PURPLE_SWORD,
    SPELL_BLUE_SWORD,
    SPELL_GREEN_SWORD,
    SPELL_YELLOW_SWORD,
    SPELL_RED_STAFF,
    SPELL_PURPLE_STAFF,
    SPELL_BLUE_STAFF,
    SPELL_GREEN_STAFF,
    SPELL_YELLOW_STAFF,
    SPELL_RED_DRUM,
    SPELL_PURPLE_DRUM,
    SPELL_BLUE_DRUM,
    SPELL_GREEN_DRUM,
    SPELL_YELLOW_DRUM,
    SPELL_RED_BOMB,
    SPELL_PURPLE_BOMB,
    SPELL_BLUE_BOMB,
    SPELL_GREEN_BOMB,
    SPELL_YELLOW_BOMB
};

#define SONIC_PULSE_SPELLS_COUNT 12
const uint32 sonicPulseSpells[SONIC_PULSE_SPELLS_COUNT] =
{
    SPELL_SONIC_PULSE_32,
    SPELL_SONIC_PULSE_30,
    SPELL_SONIC_PULSE_28,
    SPELL_SONIC_PULSE_26,
    SPELL_SONIC_PULSE_24,
    SPELL_SONIC_PULSE_22,
    SPELL_SONIC_PULSE_20,
    SPELL_SONIC_PULSE_18,
    SPELL_SONIC_PULSE_16,
    SPELL_SONIC_PULSE_14,
    SPELL_SONIC_PULSE_12,
    SPELL_SONIC_PULSE_10,
};

#define SONIC_PULSE_COUNT 5
const uint32 sonicPulseTriggers[SONIC_PULSE_COUNT] =
{
    1012, 1014, 1015, 1026, 1027
};

const Position paragonsPos[PARAGON_COUNT] =
{
    { 1589.198f, -5701.658f, -270.516f, 3.497437f },
    { 1602.252f, -5765.936f, -291.0546f, 1.814512f },
    { 1561.88f, -5608.125f, -291.0987f, 4.969732f },
    { 1650.016f, -5732.452f, -291.0862f, 2.539645f },
    { 1570.316f, -5674.297f, -270.566f, 6.128078f },
    { 1552.964f, -5640.806f, -291.1562f, 5.289442f },
    { 1608.894f, -5740.578f, -290.9958f, 2.023022f },
    { 1624.321f, -5730.018f, -291.0036f, 2.331927f },
    { 1519.401f, -5637.149f, -291.1007f, 5.62359f }
};

#define KUNCHONG_POSITION_COUNT 7
const Position kunchongPos[KUNCHONG_POSITION_COUNT] =
{
    { 1557.860718f, -5662.815918f, -314.76f, 4.002026f },
    { 1604.425415f, -5708.747070f, -314.76f, 1.634913f },
    { 1576.648926f, -5648.898926f, -314.76f, 3.482789f },
    { 1546.280640f, -5681.856934f, -314.72f, 4.548748f },
    { 1609.594849f, -5659.476074f, -314.65f, 2.251890f },
    { 1594.268555f, -5647.822266f, -314.72f, 3.073507f },
    { 1617.234131f, -5680.670898f, -314.70f, 1.439438f }
};

const Position fightstarterPos = { 1582.37f, -5685.979f, -314.4391f, 0.0f };

const Position jumpToCenterPos = { 1582.877f, -5696.859f, -314.6728f, 0.0f };

#define IMPACT_JUMP_TARGET_OFFSET 20.0f

const Position jumpToHurlAmberPos = { 1552.96f, -5640.80f, -291.14f, 5.28f };

#define BLOODLETTING_COUNT 4
#define BLOODLETTING_10 2
#define BLOODLETTING_25 3
#define BLOODLETTING_10H 3
#define BLOODLETTING_25H 4
const Position bloodlettingPos[BLOODLETTING_COUNT] =
{
    { 1590.69f, -5631.69f, -313.679f, 0.0f },
    { 1634.86f, -5697.51f, -313.696f, 0.0f },
    { 1575.19f, -5738.07f, -313.713f, 0.0f },
    { 1531.34f, -5672.67f, -313.68f, 0.0f }
};

#define AMBER_PARASITE_COUNT 3

#define AMBER_BOMB_COUNT 7
const Position amberBombPos[AMBER_BOMB_COUNT] =
{
    { 1544.156f, -5760.478f, -298.9232f, 0.f },
    { 1576.061f, -5745.816f, -294.7451f, 0.f },
    { 1641.865f, -5701.819f, -294.7451f, 0.f },
    { 1621.507f, -5609.722f, -298.9232f, 0.f },
    { 1667.226f, -5677.514f, -298.9232f, 0.f },
    { 1498.604f, -5692.389f, -298.9232f, 0.f },
    { 1589.493f, -5624.198f, -294.7452f, 0.f }
};

bool IsAmberBombNear(WorldObject* searcher)
{
    if (searcher->FindNearestCreature(NPC_AMBER_BOMB, 2.0f))
    {
        return true;
    }

    return false;
}

void AddSC_boss_paragons_of_the_klaxxi()
{
   
}
