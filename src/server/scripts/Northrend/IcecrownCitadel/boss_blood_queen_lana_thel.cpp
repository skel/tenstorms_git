/* Copyright (C) 2009 - 2010 TrinityCore <http://www.trinitycore.org/>
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 2 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program; if not, write to the Free Software
* Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
*/

#include "ScriptPCH.h"
#include "icecrown_citadel.h"

enum Yells
{
    SAY_AGGRO            = -1666054,
    SAY_VAMP_BITE_1      = -1666055,
    SAY_VAMP_BITE_2      = -1666056,
    SAY_SWARM_SHADOWS    = -1666057,
    SAY_PACT_DARKFALLEN  = -1666058,
    SAY_MIND_CONTROLL    = -1666059,
    SAY_AIR_PHASE        = -1666060,
    SAY_BERSERK          = -1666061,
    SAY_DEATH            = -1666062
};

enum Spells
{
    SPELL_PRESENCE_OF_DARKFALLEN    = 71952,
    SPELL_SHROUD_OF_SORROW          = 72981,
    SPELL_DELIRIOUS_SLASH           = 71623,
    SPELL_BLOOD_MIRROR_1            = 70821,
    SPELL_BLOOD_MIRROR_2            = 71510,
    SPELL_VAMPIRIC_BITE             = 71726,
    SPELL_PACT_OF_THE_DARKFALLEN_1  = 71340,
    SPELL_PACT_OF_THE_DARKFALLEN_2  = 71341,
    SPELL_SWARMING_SHADOWS          = 71264,
    SPELL_TWILIGHT_BLOODBOLT        = 71446,
    SPELL_BLOODBOLT_WHIRL           = 71899,
    SPELL_BLOODBOLT_SPLASH          = 71447,
    SPELL_INCITE_TERROR             = 73070,
    SPELL_SWARMING_SHADOWS_VISUAL   = 71267,
    SPELL_SWARMING_SHADOW           = 71267,
    SPELL_ESSENCE_OF_BLOOD_QWEEN    = 70867,
    SPELL_FRENZIED_BLOODTHIRST      = 70877,
    SPELL_UNCONTROLLABLE_FRENZY     = 70923
};

const Position SpawnLoc[]=
{
    {4595.640f, 2769.195f, 400.137f, 0.0f}, //phase 2 pos
    {4595.904f, 2769.315f, 421.838f, 0.0f} //fly pos
};

class boss_blood_queen_lanathel : public CreatureScript
{
    public:
        boss_blood_queen_lanathel() : CreatureScript("boss_blood_queen_lanathel") { }

        struct boss_blood_queen_lanathelAI : public BossAI
        {
            boss_blood_queen_lanathelAI(Creature* pCreature) : BossAI(pCreature, DATA_BLOOD_QUEEN_LANATHEL)
            {
                pInstance = me->GetInstanceScript();
            }

            void Reset()
            {
<<<<<<< HEAD
                m_uiPhase = 1;
                m_uiPhaseTimer = 90000;
                m_uiTwilightBloodboltTimer = 10000;
                m_uiVampBiteTimer  = 15000;
                m_uiSwarmingShadowsTimer = 30000;
                m_uiPactofDarkfallenTimer  = 5000;
                m_uiSetHoverTimer = 90000;
                m_uiBloodboldSplashTimer = 900000;
                m_uiLandingTimer = 900000;
                m_uiFlyingFalseTimer = 900000;
                m_uiBerserkTimer = 330000;

                memset(&Darkfallen, 0, sizeof(Darkfallen));

                if (pInstance && me->isAlive())
                    pInstance->SetData(DATA_BLOOD_QUEEN_LANATHEL_EVENT, NOT_STARTED);
=======
                _Reset();
                events.ScheduleEvent(EVENT_BERSERK, 330000);
                events.ScheduleEvent(EVENT_VAMPIRIC_BITE, 15000);
                events.ScheduleEvent(EVENT_BLOOD_MIRROR, 2500, EVENT_GROUP_CANCELLABLE);
                events.ScheduleEvent(EVENT_DELIRIOUS_SLASH, urand(20000, 24000), EVENT_GROUP_NORMAL);
                events.ScheduleEvent(EVENT_PACT_OF_THE_DARKFALLEN, 15000, EVENT_GROUP_NORMAL);
                events.ScheduleEvent(EVENT_SWARMING_SHADOWS, 30500, EVENT_GROUP_NORMAL);
                events.ScheduleEvent(EVENT_TWILIGHT_BLOODBOLT, urand(20000, 25000), EVENT_GROUP_NORMAL);
                events.ScheduleEvent(EVENT_AIR_PHASE, 124000 + uint32(Is25ManRaid() ? 3000 : 0));
                me->SetSpeed(MOVE_FLIGHT, 0.642857f, true);
                offtank = NULL;
                vampires.clear();
            }

            void EnterCombat(Unit* who)
            {
                if (!instance->CheckRequiredBosses(DATA_BLOOD_QUEEN_LANA_THEL, who->ToPlayer()))
                {
                    EnterEvadeMode();
                    instance->DoCastSpellOnPlayers(LIGHT_S_HAMMER_TELEPORT);
                    return;
                }

                me->setActive(true);
                DoZoneInCombat();
                Talk(SAY_AGGRO);
                instance->SetBossState(DATA_BLOOD_QUEEN_LANA_THEL, IN_PROGRESS);

                DoCast(me, SPELL_SHROUD_OF_SORROW, true);
                DoCast(me, SPELL_FRENZIED_BLOODTHIRST_VISUAL, true);
            }

            void JustDied(Unit* /*killer*/)
            {
                _JustDied();
                Talk(SAY_DEATH);
                instance->DoRemoveAurasDueToSpellOnPlayers(ESSENCE_OF_BLOOD_QUEEN);
                instance->DoRemoveAurasDueToSpellOnPlayers(ESSENCE_OF_BLOOD_QUEEN_PLR);
                instance->DoRemoveAurasDueToSpellOnPlayers(FRENZIED_BLOODTHIRST);
                instance->DoRemoveAurasDueToSpellOnPlayers(SPELL_UNCONTROLLABLE_FRENZY);
                instance->DoRemoveAurasDueToSpellOnPlayers(SPELL_BLOOD_MIRROR_DAMAGE);
                instance->DoRemoveAurasDueToSpellOnPlayers(SPELL_BLOOD_MIRROR_VISUAL);
                instance->DoRemoveAurasDueToSpellOnPlayers(SPELL_BLOOD_MIRROR_DUMMY);
                instance->DoRemoveAurasDueToSpellOnPlayers(SPELL_DELIRIOUS_SLASH);
                instance->DoRemoveAurasDueToSpellOnPlayers(SPELL_PACT_OF_THE_DARKFALLEN);
>>>>>>> b28881f6485f4bc7052b552d46acdfa3bf3d713a
            }

            void EnterCombat(Unit* /*who*/)
            {
<<<<<<< HEAD
                DoScriptText(SAY_AGGRO, me);
                DoCast(SPELL_SHROUD_OF_SORROW);
=======
                _JustReachedHome();
                Talk(SAY_WIPE);
                instance->SetBossState(DATA_BLOOD_QUEEN_LANA_THEL, FAIL);
            }
>>>>>>> b28881f6485f4bc7052b552d46acdfa3bf3d713a

                if (pInstance)
                    pInstance->SetData(DATA_BLOOD_QUEEN_LANATHEL_EVENT, IN_PROGRESS);
            }

            void KilledUnit(Unit* pVictim)
            {
                pVictim->RemoveAllAuras();
            }

            void JustDied(Unit* /*Killer*/)
            {
                DoScriptText(SAY_DEATH, me);

<<<<<<< HEAD
                if (pInstance)
                    pInstance->SetData(DATA_BLOOD_QUEEN_LANATHEL_EVENT, DONE);
=======
                switch (id)
                {
                    case POINT_CENTER:
                        DoCast(me, SPELL_INCITE_TERROR);
                        events.ScheduleEvent(EVENT_AIR_PHASE, 100000 + uint32(Is25ManRaid() ? 0 : 20000));
                        events.RescheduleEvent(EVENT_SWARMING_SHADOWS, 30500, EVENT_GROUP_NORMAL);
                        events.RescheduleEvent(EVENT_PACT_OF_THE_DARKFALLEN, 25500, EVENT_GROUP_NORMAL);
                        events.ScheduleEvent(EVENT_AIR_START_FLYING, 5000);
                        break;
                    case POINT_AIR:
                        DoCast(me, SPELL_BLOODBOLT_WHIRL);
                        Talk(SAY_AIR_PHASE);
                        events.ScheduleEvent(EVENT_AIR_FLY_DOWN, 10000);
                        break;
                    case POINT_GROUND:
                        me->RemoveUnitMovementFlag(MOVEMENTFLAG_LEVITATING);
                        me->RemoveByteFlag(UNIT_FIELD_BYTES_1, 3, 0x01);
                        me->SetFlying(false);
                        me->SetReactState(REACT_AGGRESSIVE);
                        if (Unit *victim = me->SelectVictim())
                            AttackStart(victim);
                        events.ScheduleEvent(EVENT_BLOOD_MIRROR, 2500, EVENT_GROUP_CANCELLABLE);
                        break;
                    default:
                        break;
                }
>>>>>>> b28881f6485f4bc7052b552d46acdfa3bf3d713a
            }

            void UpdateAI(const uint32 uiDiff)
            {
                if (!UpdateVictim())
                    return;

                if (!me->HasAura(SPELL_SHROUD_OF_SORROW))
                    DoCast(me, SPELL_SHROUD_OF_SORROW);

                if (m_uiBerserkTimer < uiDiff)
                {
                    DoScriptText(SAY_BERSERK, me);
                    DoCast(me, SPELL_BERSERK);
                    m_uiBerserkTimer = 330000;
                } else m_uiBerserkTimer -= uiDiff;

                if (m_uiPhase == 1)
                {
                    if (m_uiPactofDarkfallenTimer <= uiDiff)
                    {
<<<<<<< HEAD
                        DoScriptText(SAY_PACT_DARKFALLEN, me);
                        m_uiPactofDarkfallenExplosionCount = 0;
                        m_uiPactofDarkfallenExplodeTimer = 2000;
                        m_uiPactofDarkfallenTimer = 25000;
                    } else m_uiPactofDarkfallenTimer -= uiDiff;
=======
                        case EVENT_BERSERK:
                            DoScriptText(EMOTE_GENERIC_BERSERK_RAID, me);
                            Talk(SAY_BERSERK);
                            DoCast(me, SPELL_BERSERK);
                            break;
                        case EVENT_VAMPIRIC_BITE:
                            if (Player* target = SelectRandomTarget(false))
                            {
                                DoCast(target, SPELL_VAMPIRIC_BITE);
                                Talk(SAY_VAMPIRIC_BITE);
                                vampires.insert(target->GetGUID());
                            }
                            break;
                        case EVENT_BLOOD_MIRROR:
                        {
                            // victim can be NULL when this is processed in the same update tick as EVENT_AIR_PHASE
                            if (me->getVictim())
                            {
                                Player* newOfftank = SelectRandomTarget(true);
                                if (offtank != newOfftank)
                                {
                                    offtank = newOfftank;
                                    if (offtank)
                                    {
                                        offtank->CastSpell(me->getVictim(), SPELL_BLOOD_MIRROR_DAMAGE, true);
                                        me->getVictim()->CastSpell(offtank, SPELL_BLOOD_MIRROR_DUMMY, true);
                                        DoCastVictim(SPELL_BLOOD_MIRROR_VISUAL);
                                        if (Item* shadowsEdge = offtank->GetWeaponForAttack(BASE_ATTACK, true))
                                            if (!offtank->HasAura(SPELL_THIRST_QUENCHED) && shadowsEdge->GetEntry() == ITEM_SHADOW_S_EDGE && !offtank->HasAura(SPELL_GUSHING_WOUND))
                                                offtank->CastSpell(offtank, SPELL_GUSHING_WOUND, true);

                                    }
                                }
                            }
                            events.ScheduleEvent(EVENT_BLOOD_MIRROR, 2500, EVENT_GROUP_CANCELLABLE);
                            break;
                        }
                        case EVENT_DELIRIOUS_SLASH:
                            if (offtank && !me->HasByteFlag(UNIT_FIELD_BYTES_1, 3, 0x03))
                                DoCast(offtank, SPELL_DELIRIOUS_SLASH);
                            events.ScheduleEvent(EVENT_DELIRIOUS_SLASH, urand(20000, 24000), EVENT_GROUP_NORMAL);
                            break;
                        case EVENT_PACT_OF_THE_DARKFALLEN:
                        {
                            std::list<Player*> targets;
                            SelectRandomTarget(false, &targets);
                            uint32 targetCount = 2;
                            // do not combine these checks! we want it incremented TWICE when both conditions are met
                            if (IsHeroic())
                                ++targetCount;
                            if (Is25ManRaid())
                                ++targetCount;
                            Trinity::RandomResizeList<Player*>(targets, targetCount);
                            if (targets.size() > 1)
                            {
                                Talk(SAY_PACT_OF_THE_DARKFALLEN);
                                for (std::list<Player*>::iterator itr = targets.begin(); itr != targets.end(); ++itr)
                                    DoCast(*itr, SPELL_PACT_OF_THE_DARKFALLEN);
                            }
                            events.ScheduleEvent(EVENT_PACT_OF_THE_DARKFALLEN, 30500, EVENT_GROUP_NORMAL);
                            break;
                        }
                        case EVENT_SWARMING_SHADOWS:
                            if (Player* target = SelectRandomTarget(false))
                            {
                                Talk(EMOTE_SWARMING_SHADOWS, target->GetGUID());
                                Talk(SAY_SWARMING_SHADOWS);
                                DoCast(target, SPELL_SWARMING_SHADOWS);
                            }
                            events.ScheduleEvent(EVENT_SWARMING_SHADOWS, 30500, EVENT_GROUP_NORMAL);
                            break;
                        case EVENT_TWILIGHT_BLOODBOLT:
                        {
                            std::list<Player*> targets;
                            SelectRandomTarget(false, &targets);
                            Trinity::RandomResizeList<Player*>(targets, uint32(Is25ManRaid() ? 4 : 2));
                            for (std::list<Player*>::iterator itr = targets.begin(); itr != targets.end(); ++itr)
                                DoCast(*itr, SPELL_TWILIGHT_BLOODBOLT);
                            DoCast(me, SPELL_TWILIGHT_BLOODBOLT_TARGET);
                            events.ScheduleEvent(EVENT_TWILIGHT_BLOODBOLT, urand(10000, 15000), EVENT_GROUP_NORMAL);
                            break;
                        }
                        case EVENT_AIR_PHASE:
                            DoStopAttack();
                            me->SetReactState(REACT_PASSIVE);
                            events.DelayEvents(7000, EVENT_GROUP_NORMAL);
                            events.CancelEventsByGCD(EVENT_GROUP_CANCELLABLE);
                            me->GetMotionMaster()->MovePoint(POINT_CENTER, centerPos);
                            break;
                        case EVENT_AIR_START_FLYING:
                            me->AddUnitMovementFlag(MOVEMENTFLAG_LEVITATING);
                            me->SetByteFlag(UNIT_FIELD_BYTES_1, 3, 0x01);
                            me->SetFlying(true);
                            me->GetMotionMaster()->MovePoint(POINT_AIR, airPos);
                            break;
                        case EVENT_AIR_FLY_DOWN:
                            me->GetMotionMaster()->MovePoint(POINT_GROUND, centerPos);
                            break;
                        default:
                            break;
                    }
                }

                DoMeleeAttackIfReady();
            }

            bool WasVampire(uint64 guid)
            {
                return vampires.count(guid) != 0;
            }

        private:
            // offtank for this encounter is the player standing closest to main tank
            Player* SelectRandomTarget(bool includeOfftank, std::list<Player*>* targetList = NULL)
            {
                const std::list<HostileReference*> &threatlist = me->getThreatManager().getThreatList();
                std::list<Player*> tempTargets;
>>>>>>> b28881f6485f4bc7052b552d46acdfa3bf3d713a

                    if (m_uiSwarmingShadowsTimer < uiDiff)
                    {
                        if(Unit* pTarget = SelectUnit(SELECT_TARGET_RANDOM, 1))
                        DoCast(pTarget, SPELL_SWARMING_SHADOWS);
                        m_uiSwarmingShadowsTimer = 30000;
                    } else m_uiSwarmingShadowsTimer -= uiDiff;

                    if (m_uiTwilightBloodboltTimer < uiDiff)
                    {
                        if(Unit* pTarget = SelectUnit(SELECT_TARGET_RANDOM, 1))
                        DoCast(pTarget, SPELL_TWILIGHT_BLOODBOLT);
                        m_uiTwilightBloodboltTimer = 9000;
                    } else m_uiTwilightBloodboltTimer -= uiDiff;

                    if (m_uiVampBiteTimer < uiDiff)
                    {
                        DoScriptText(RAND(SAY_VAMP_BITE_1,SAY_VAMP_BITE_2), me);
                        DoCast(me->getVictim(), SPELL_VAMPIRIC_BITE);
                        m_uiVampBiteTimer = 40000;
                    } else m_uiVampBiteTimer -= uiDiff;

                    if (m_uiPhaseTimer < uiDiff)
                    {
                        DoScriptText(SAY_AIR_PHASE, me);
                        DoCast(me, SPELL_INCITE_TERROR);
                        me->GetMotionMaster()->MovePoint(0, SpawnLoc[0]);
                        me->SetReactState(REACT_PASSIVE);
                        me->AttackStop();
                        m_uiPhase = 2;
                        m_uiPhaseTimer = 90000;
                        m_uiSetHoverTimer = 5000;
                        m_uiBloodboldSplashTimer = 10000;
                        m_uiLandingTimer = 26000;
                        m_uiFlyingFalseTimer = 30000;
                    } else m_uiPhaseTimer -= uiDiff;
                }

                if (m_uiPhase == 2)
                {
                    if (m_uiSetHoverTimer < uiDiff)
                    {
                        me->GetMotionMaster()->MovePoint(0, SpawnLoc[1]);
                        me->SetUnitMovementFlags(MOVEMENTFLAG_JUMPING);
                        me->SetFlying(true);
                        m_uiSetHoverTimer = 90000;
                    } else m_uiSetHoverTimer -= uiDiff;

                    if (m_uiBloodboldSplashTimer < uiDiff)
                    {
                        std::list<Unit*> targets;
                        SelectTargetList(targets, 5, SELECT_TARGET_RANDOM, 80, true);
                        for (std::list<Unit*>::const_iterator i = targets.begin(); i != targets.end(); ++i)
                            DoCast(*i, SPELL_TWILIGHT_BLOODBOLT);
                        m_uiBloodboldSplashTimer = 2000;
                    } else m_uiBloodboldSplashTimer -= uiDiff;

                    if (m_uiLandingTimer < uiDiff)
                    {
                        me->GetMotionMaster()->MovePoint(0, SpawnLoc[0]);
                        me->SetUnitMovementFlags(MOVEMENTFLAG_JUMPING);
                        m_uiLandingTimer = 900000;
                        m_uiBloodboldSplashTimer = 900000;
                    } else m_uiLandingTimer -= uiDiff;

                    if (m_uiFlyingFalseTimer < uiDiff)
                    {
                        me->SetFlying(false);
                        me->RemoveAllAuras();
                        me->SetReactState(REACT_AGGRESSIVE);
                        me->GetMotionMaster()->MoveChase(me->getVictim());
                        m_uiPhase = 1;
                        m_uiFlyingFalseTimer = 900000;
                    } else m_uiFlyingFalseTimer -= uiDiff;
                }

                DoMeleeAttackIfReady();
            }
        private:
            InstanceScript* pInstance;

            uint32 m_uiTwilightBloodboltTimer;
            uint32 m_uiPhaseTimer;
            uint32 m_uiVampBiteTimer;
            uint32 m_uiSwarmingShadowsTimer;
            uint32 m_uiPactofDarkfallenTimer;
            uint32 m_uiPactofDarkfallenExplodeTimer;
            uint32 m_uiPactofDarkfallenExplosionCount;
            uint32 m_uiPhase;
            uint32 m_uiBerserkTimer;
            uint32 m_uiSetHoverTimer;
            uint32 m_uiLandingTimer;
            uint32 m_uiFlyingFalseTimer;
            uint32 m_uiBloodboldSplashTimer;
            uint32 m_uiResetTimer;
            Unit* Darkfallen[5];
        };

        CreatureAI* GetAI(Creature* pCreature) const
        {
            return new boss_blood_queen_lanathelAI(pCreature);
        }
};

class npc_swarming_shadows : public CreatureScript
{
    public:
        npc_swarming_shadows() : CreatureScript("npc_swarming_shadows") { }

        struct npc_swarming_shadowsAI : public Scripted_NoMovementAI
        {
            npc_swarming_shadowsAI(Creature *pCreature) : Scripted_NoMovementAI(pCreature)
            {
                pInstance = pCreature->GetInstanceScript();
            }

            void Reset()
            {
                m_uiSwarmingShadowTimer = 1200;
            }

            void UpdateAI(const uint32 uiDiff)
            {
                if (!me->HasAura(SPELL_SWARMING_SHADOWS_VISUAL))
                    DoCast(me, SPELL_SWARMING_SHADOWS_VISUAL);

                if (m_uiSwarmingShadowTimer < uiDiff)
                {
                    DoCast(me, SPELL_SWARMING_SHADOW);
                    m_uiSwarmingShadowTimer = 2000;
                } else m_uiSwarmingShadowTimer -= uiDiff;
            }
        private:
            InstanceScript* pInstance;

            uint32 m_uiSwarmingShadowTimer;
        };

        CreatureAI* GetAI(Creature* pCreature) const
        {
            return new npc_swarming_shadowsAI(pCreature);
        }
};

void AddSC_boss_blood_queen_lana_thel()
{
    new boss_blood_queen_lanathel();
    new npc_swarming_shadows();
}
