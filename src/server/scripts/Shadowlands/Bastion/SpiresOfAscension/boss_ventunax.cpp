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

#include "ScriptMgr.h"
#include "Player.h"
#include "Creature.h"
#include "CreatureAI.h"
#include "GameObject.h"
#include "GameObjectAI.h"
#include "AreaTrigger.h"
#include "AreaTriggerAI.h"
#include "SpellAuraEffects.h"
#include "spires_of_ascension.h"

enum Ventunax
{
    SPELL_DARK_STRIDE_TELEPORT = 324148,
    SPELL_DARK_STRIDE_PERIODIC_DAMAGE = 324154,
    SPELL_SUMMON_SHADOWHIRL_SUMMON = 323927, //npc 166136, 166152
    SPELL_DARK_BOLT_DAMAGE = 324141,
    SPELL_SHADOWHIRL_APPLY_AT_AURA = 324108,
    SPELL_DARK_BOLT_CREATE_AT = 323928,
    SPELL_RECHARGE = 334485,
    SPELL_BLINDING_FLASH = 324205,
    EVENT_ENERGY_DRAIN,
};

//162058
struct boss_ventunax : public BossAI
{
    boss_ventunax(Creature* creature) : BossAI(creature, DATA_VENTUNAX) { }

private:
    float randAngle;
    float AngleOne;
    float AngleTwo;

    void Reset() override
    {
        BossAI::Reset();
        me->SetPowerType(POWER_ENERGY);
        me->SetMaxPower(POWER_ENERGY, 100);
        me->SetPower(POWER_ENERGY, 100);
        me->GetAura(324185); //power color from sniffs
    }

    void EnterCombat(Unit* /*who*/)
    {
        Talk(0);
        events.ScheduleEvent(EVENT_ENERGY_DRAIN, 1s);
        events.ScheduleEvent(SPELL_DARK_STRIDE_TELEPORT, 5s);
        events.ScheduleEvent(SPELL_BLINDING_FLASH, 10s);
    }

    void ExecuteEvent(uint32 eventId) override
    {
        if (me->GetPower(POWER_ENERGY) == 0)
        {
            me->SetPower(POWER_ENERGY, + 1);
            me->CastSpell(nullptr, SPELL_RECHARGE, false);            
            this->randAngle = (float(rand()) / float((RAND_MAX)) * 6.28);
            for (uint8 i = 0; i < 15; i++)
            {
            }
        }
        switch (eventId)
        {
        case EVENT_ENERGY_DRAIN:
            me->ModifyPower(POWER_ENERGY, -1);
            events.Repeat(1s);
            break;

        case SPELL_BLINDING_FLASH:
            DoCastVictim(SPELL_BLINDING_FLASH, false);
            events.Repeat(20s, 23s);
            break;
        }
    }

    void EnterEvadeMode(EvadeReason /*why*/) override
    {
    }

    void JustReachedHome() override
    {
        _JustReachedHome();
    }

    void JustDied(Unit* /*who*/) override
    {
        _JustDied();
        Talk(1);
    }
};

//166136, 166152
struct npc_shadowhirl : public ScriptedAI
{
    npc_shadowhirl(Creature* c) : ScriptedAI(c) { }

    void Reset() override
    {
        switch (me->GetEntry())
        {
        case NPC_SHADOWHIRL:
            me->SetDisplayId(16925, 1.0f);
            me->GetAura(SPELL_SHADOWHIRL_APPLY_AT_AURA);
            {
            };
            break;

        case NPC_SHADOWHIRL_2:
            me->GetAura(SPELL_DARK_BOLT_CREATE_AT);
            me->SetObjectScale(0.5f);
            break;
        }
    }
};

//23813
struct at_dark_bolt : public AreaTriggerAI
{
    at_dark_bolt(AreaTrigger* at) : AreaTriggerAI(at) { }

    void OnUnitEnter(Unit* target) override
    {
        if (!target->IsPlayer())
            return;

        if (at->GetCaster())
            at->GetCaster()->CastSpell(target, SPELL_DARK_BOLT_DAMAGE, true);
    }
};

void AddSC_boss_ventunax()
{
    RegisterCreatureAI(boss_ventunax);
    RegisterCreatureAI(npc_shadowhirl);
    RegisterAreaTriggerAI(at_dark_bolt);
}