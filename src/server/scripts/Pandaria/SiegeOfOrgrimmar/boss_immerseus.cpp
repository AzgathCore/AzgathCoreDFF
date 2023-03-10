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
#include "SpellMgr.h"

enum Spells
{
    SPELL_BERSERK = 145525, // don't use 'castspell' because it's aoe spell

    SPELL_ZERO_POWER = 96301,

    SPELL_SHA_BOOLT_AOE = 143290, // targetting
    SPELL_SHA_BOLT_MISSILE = 143293,
    SPELL_SHA_BOLT_DMG = 143295,
    SPELL_SHA_SPLASH = 143297,
    SPELL_SHA_SPLASH_AURA = 143298,

    SPELL_SHA_POOL_AURA = 143462,
    SPELL_SHA_POOL_SCRIPT = 143461,
    SPELL_SHA_POOL_DMG = 143460,

    SPELL_CORROSIVE_BLAST = 143436,

    SPELL_SEEPING_SHA = 143281,
    SPELL_SEEPING_SHA_DMG = 143286,

    SPELL_SWIRL = 143309,
    SPELL_SWIRL_2 = 143410,
    SPELL_SWIRL_DMG = 143412, // main swirl from the boss
    SPELL_SWIRL_DMG_2 = 143413, // errupting swirls on the ground
    SPELL_SWIRL_SCRIPT = 143415,

    SPELL_SHA_CORRUPTION = 143579,

    SPELL_SPLIT = 143020,
    SPELL_SPLIT_MISSILE_1 = 143022, // sha puddle
    SPELL_SPLIT_MISSILE_2 = 143024, // contaminated puddle
    SPELL_SPLIT_SUMMON_1 = 143453,
    SPELL_SPLIT_SUMMON_2 = 143454,

    SPELL_REFORM = 143469,

    SPELL_SHA_RESIDUE = 143459,
    SPELL_ERUPTING_SHA = 143498,

    SPELL_CONGEALING = 143538,
    SPELL_CONGEALING_AURA = 143540,
    SPELL_PUTRIFIED_RESUDUE = 143524,
    SPELL_PURIFIED = 143523,
    SPELL_ERUPTING_WATER = 145377,

    SPELL_SWELLING_CORRUPTION = 143574, // on heroic
    SPELL_SWELLING_CORRUPTION_SCRIPT = 143578, //
    SPELL_SHA_CORRUPTION_MISSILE = 143580,
    SPELL_SWELLING_CORRUPTION_SUMMON = 143581,
    SPELL_SHA_CORRUPTION_DMG = 143579,

    SPELL_ACHIEVEMENT = 145889,

};

enum Adds
{
    NPC_SHA_BOLT = 71544,
    NPC_CONTAMINATED_PUDDLE = 71604,
    NPC_SHA_PUDDLE = 71603,
    NPC_PURIFIED_PUDDLE = 71605,
    NPC_SWIRL = 71548,
    NPC_SHA_POOL = 71611,
    NPC_CONGEALED_SHA = 71642,
};

enum Events
{
    EVENT_SHA_BOLT = 1,
    EVENT_CORROSIVE_BLAST,
    EVENT_SWIRL,
    EVENT_SPLIT,
    EVENT_REFORM,
    EVENT_REFORM_1,
    EVENT_CHECK_MELEE,
    EVENT_BERSERK,
    EVENT_SWELLING_CORRUPTION,
};

enum Timers
{
    TIMER_SWELLING_CORRUPTION_FIRST = 10 * IN_MILLISECONDS,
    TIMER_SWELLING_CORRUPTION_FIRST_2 = 17 * IN_MILLISECONDS, // after reform
    TIMER_SWELLING_CORRUPTION = 75 * IN_MILLISECONDS,
};

enum Actions
{
    ACTION_PUDDLE_DIED = 1,
    ACTION_SPLIT,
    ACTION_REFORM,
    ACTION_MOVE_SWIRL,
    ACTION_MOVE_SHA_BOLT,
    ACTION_SHA_POOL_INCREASE,
    ACTION_SHA_POOL_DECREASE,
};

enum eData
{
    DATA_SHA_POOL = 1,
};

enum Phases
{
    PHASE_IMMERSEUS_BOSS,
    PHASE_IMMERSEUS_ADDS
};

#define MAX_PUDDLE_POINTS 32
#define MAX_PUDDLES_IN_PHASE 25

const Position puddlePos[MAX_PUDDLE_POINTS] =
{
    {1455.601318f, 661.137329f, 246.85f, 0.356930f},
    {1461.414551f, 663.377380f, 246.86f, 0.378310f},
    {1474.600830f, 670.615051f, 246.86f, 0.665416f},
    {1488.301758f, 681.498596f, 246.84f, 0.741774f},
    {1507.742065f, 700.772583f, 246.84f, 1.041098f},
    {1513.817261f, 711.771057f, 246.84f, 1.065533f},
    {1519.040283f, 723.025330f, 246.84f, 1.270173f},
    {1522.439209f, 735.315369f, 246.84f, 1.380130f},
    {1523.098755f, 758.624695f, 246.84f, 1.624478f},
    {1522.009155f, 773.242310f, 246.84f, 1.719162f},
    {1518.275269f, 785.543518f, 246.84f, 2.003216f},
    {1511.928223f, 796.272034f, 246.84f, 2.189532f},
    {1491.666260f, 816.293823f, 246.84f, 2.470533f},
    {1481.050903f, 824.383911f, 246.84f, 2.601870f},
    {1469.224731f, 829.512512f, 246.84f, 2.922577f},
    {1459.451416f, 830.224121f, 246.84f, 2.968393f},
    {1447.282104f, 831.876282f, 246.84f, 3.060024f},
    {1432.209229f, 832.271667f, 246.84f, 3.182199f},
    {1415.996948f, 830.680725f, 246.84f, 3.389895f},
    {1400.198120f, 823.627197f, 246.84f, 3.689223f},
    {1377.474243f, 803.850769f, 246.84f, 4.135154f},
    {1368.328491f, 789.614624f, 246.84f, 4.208457f},
    {1364.697388f, 780.012390f, 246.84f, 4.443637f},
    {1361.294556f, 767.282104f, 246.84f, 4.483343f},
    {1360.805664f, 745.632629f, 246.76f, 4.837642f},
    {1361.920898f, 736.954041f, 246.84f, 4.840696f},
    {1365.434937f, 720.942383f, 246.84f, 5.100311f},
    {1372.835083f, 707.264648f, 246.84f, 5.338545f},
    {1391.068726f, 684.659241f, 246.84f, 5.317163f},
    {1397.286499f, 678.322754f, 246.84f, 5.607323f},
    {1409.754395f, 669.343140f, 246.86f, 5.839451f},
    {1420.205566f, 665.879211f, 246.86f, 6.016602f}
};

#define MAX_SWIRL_POINTS 69

const Position swirlPos[MAX_SWIRL_POINTS] =
{
    {1487.464111f, 820.573914f, 246.843847f, 2.851097f},
    {1483.964111f, 821.693237f, 246.843847f, 2.817499f},
    {1468.896118f, 826.547729f, 246.844167f, 2.909131f},
    {1456.378662f, 828.710266f, 246.844213f, 2.979382f},
    {1439.406494f, 830.934082f, 246.844213f, 3.119882f},
    {1428.211304f, 830.142212f, 246.844213f, 3.263438f},
    {1418.107788f, 828.381470f, 246.844213f, 3.382557f},
    {1402.880737f, 823.863464f, 246.844213f, 3.452806f},
    {1399.085571f, 818.854919f, 246.844213f, 5.294566f},
    {1411.434082f, 808.112427f, 246.844213f, 0.178134f},
    {1422.152222f, 809.762329f, 246.844213f, 6.183375f},
    {1436.858887f, 807.700134f, 246.844213f, 6.088694f},
    {1444.952026f, 805.963623f, 246.844213f, 6.055098f},
    {1456.801147f, 795.857666f, 246.844213f, 4.103389f},
    {1444.532104f, 794.825623f, 246.844213f, 3.352025f},
    {1429.040283f, 790.880737f, 246.844213f, 3.461982f},
    {1410.085205f, 775.187012f, 246.845495f, 4.023979f},
    {1393.301880f, 765.024414f, 246.845495f, 3.208473f},
    {1391.872559f, 772.953552f, 246.845495f, 1.217052f},
    {1386.915649f, 784.558105f, 246.845495f, 2.457110f},
    {1377.011108f, 773.724792f, 246.845495f, 4.243890f},
    {1364.892334f, 769.258484f, 246.845495f, 2.915258f},
    {1365.610352f, 785.148743f, 246.845495f, 1.482780f},
    {1358.791992f, 738.885864f, 246.844656f, 4.736073f},
    {1360.505127f, 726.221008f, 246.844656f, 4.946821f},
    {1368.800781f, 712.329407f, 246.844656f, 5.569902f},
    {1375.536621f, 717.005432f, 246.844656f, 1.611060f},
    {1373.879883f, 730.299927f, 246.844656f, 1.507213f},
    {1381.795410f, 733.744568f, 246.844656f, 5.582122f},
    {1392.619751f, 728.715088f, 246.844656f, 0.435146f},
    {1400.361694f, 737.273865f, 246.844656f, 0.899404f},
    {1418.521362f, 716.076782f, 246.845510f, 5.438570f},
    {1423.970337f, 703.457825f, 246.852407f, 4.885737f},
    {1415.678589f, 699.607605f, 246.851675f, 2.845447f},
    {1407.067871f, 695.299500f, 246.848837f, 4.436752f},
    {1412.809814f, 687.349426f, 246.849600f, 5.649319f},
    {1417.447632f, 678.563110f, 246.852484f, 4.546707f},
    {1403.742798f, 676.551514f, 246.853964f, 3.004273f},
    {1455.166992f, 669.881775f, 246.856405f, 5.796364f},
    {1469.832886f, 668.007324f, 246.852448f, 0.218726f},
    {1481.525024f, 673.573853f, 246.858358f, 0.542484f},
    {1485.030884f, 685.873596f, 246.845449f, 1.868062f},
    {1475.905518f, 689.903992f, 246.845999f, 3.285270f},
    {1461.079590f, 687.039856f, 246.851873f, 3.227237f},
    {1456.446899f, 695.258850f, 246.853765f, 1.281632f},
    {1463.775757f, 702.528687f, 246.852346f, 0.609680f},
    {1466.321899f, 710.755859f, 246.847708f, 2.054377f},
    {1456.144287f, 712.550476f, 246.851980f, 3.062304f},
    {1473.011597f, 730.861023f, 246.845693f, 1.052557f},
    {1477.371216f, 738.282532f, 246.845693f, 0.936493f},
    {1486.354492f, 740.582092f, 246.845693f, 6.141500f},
    {1488.745972f, 732.226196f, 246.845693f, 4.516599f},
    {1489.199829f, 722.414978f, 246.845693f, 5.325995f},
    {1494.694580f, 719.655029f, 246.845693f, 0.362278f},
    {1500.481445f, 725.311035f, 246.845693f, 0.930383f},
    {1507.764038f, 733.761292f, 246.845693f, 0.365333f},
    {1514.580200f, 730.206177f, 246.845693f, 4.822032f},
    {1512.615112f, 717.166931f, 246.845693f, 4.504382f},
    {1524.565308f, 764.396484f, 246.844824f, 1.431730f},
    {1524.019897f, 777.253967f, 246.844824f, 1.813523f},
    {1516.852417f, 789.461365f, 246.844824f, 2.864211f},
    {1511.241699f, 781.535645f, 246.844824f, 4.608231f},
    {1504.731567f, 777.073181f, 246.844824f, 2.320541f},
    {1494.234131f, 781.758850f, 246.844824f, 3.218513f},
    {1487.912109f, 779.528564f, 246.844824f, 3.948496f},
    {1485.296631f, 766.771729f, 246.844824f, 4.492164f},
    {1478.048706f, 765.134338f, 246.844824f, 2.363299f},
    {1461.304810f, 787.290466f, 246.845510f, 2.552668f},
    {1453.450806f, 791.219910f, 246.845510f, 2.833669f}
};

#define MAX_SWIRL_TARGET_POS 16

G3D::Vector3 const swirlTargetPos[MAX_SWIRL_TARGET_POS] =
{
    { 1470.927f, 784.5482f, 246.9319f },
    { 1455.533f, 792.9921f, 247.8354f },
    { 1438.079f, 794.902f,  247.8354f },
    { 1421.223f, 789.9871f, 247.8354f },
    { 1407.53f,  778.9958f, 247.8406f },
    { 1399.086f, 763.6014f, 247.8356f },
    { 1397.177f, 746.1475f, 247.8355f },
    { 1402.091f, 729.2913f, 247.8355f },
    { 1413.083f, 715.5989f, 247.8353f },
    { 1428.477f, 707.1551f, 247.8472f },
    { 1445.931f, 705.2451f, 246.932f  },
    { 1462.787f, 710.16f,   247.84f   },
    { 1476.479f, 721.1512f, 247.5257f },
    { 1484.923f, 736.5457f, 247.8356f },
    { 1486.833f, 753.9997f, 246.9326f },
    { 1481.918f, 770.8559f, 247.8356f },
};

enum DisplayIds
{
    DISPLAY_CORRUPTED = 49056,
    DISPLAY_PURGED = 49807
};

Creature* GetImmerseus(Creature* p_Creature)
{
    if (InstanceScript* l_Instance = p_Creature->GetInstanceScript())
        return l_Instance->instance->GetCreature(l_Instance->GetObjectGuid(DATA_IMMERSEUS));

    return nullptr;
}

void AddSC_boss_immerseus()
{
   
}
