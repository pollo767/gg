/*
 * Buff & Debuff
 */

#include <gba_base.h>

#include "buff.h"

#include "character.h"
#include "fontgrp.h"
#include "skill.h"
#include "proc.h"
#include "new_unit_state.h"

// Buff
struct Buff gPlayerBuff[PLAYER_TOTAL_AMOUNT];
struct Buff gEnemyBuff[ENEMY_TOTAL_AMOUNT];
struct Buff gNPCBuff[NPC_TOTAL_AMOUNT];
struct Buff gP4Buff[P4_TOTAL_AMOUNT];

// Debuff
struct Buff gPlayerDebuff[PLAYER_TOTAL_AMOUNT];
struct Buff gEnemyDebuff[ENEMY_TOTAL_AMOUNT];
struct Buff gNPCDebuff[NPC_TOTAL_AMOUNT];
struct Buff gP4Debuff[P4_TOTAL_AMOUNT];

struct Buff *getUnitBuff(struct Unit *unit)
{
    struct Buff *pUnitBuff = 0;

    switch(unit->side)
    {
        case PlayerSide:
            pUnitBuff = &gPlayerBuff[unit->number - 1];
            break;
        case EnemySide:
            pUnitBuff = &gEnemyBuff[unit->number - 1];
            break;
        case NPCSide:
            pUnitBuff = &gNPCBuff[unit->number - 1];
            break;
        default:
            pUnitBuff = &gP4Buff[unit->number - 1];
            break;
    }

    return pUnitBuff;
}

struct Buff *getUnitDebuff(struct Unit *unit)
{
    struct Buff *pUnitDebuff = 0;

    switch(unit->side)
    {
        case PlayerSide:
            pUnitDebuff = &gPlayerDebuff[unit->number - 1];
            break;
        case EnemySide:
            pUnitDebuff = &gEnemyDebuff[unit->number - 1];
            break;
        case NPCSide:
            pUnitDebuff = &gNPCDebuff[unit->number - 1];
            break;
        default:
            pUnitDebuff = &gP4Debuff[unit->number - 1];
            break;
    }

    return pUnitDebuff;
}

void calcUnitTotalBuff(struct Unit *unit, struct Buff *pTotalBuff)
{
    struct Buff *pUnitBuff = getUnitBuff(unit);
    struct Buff *pUnitDebuff = getUnitDebuff(unit);
    pTotalBuff->hp = pUnitBuff->hp + pUnitDebuff->hp;
    pTotalBuff->pow = pUnitBuff->pow + pUnitDebuff->pow;
    pTotalBuff->skl = pUnitBuff->skl + pUnitDebuff->skl;
    pTotalBuff->spd = pUnitBuff->spd + pUnitDebuff->spd;
    pTotalBuff->def = pUnitBuff->def + pUnitDebuff->def;
    pTotalBuff->res = pUnitBuff->res + pUnitDebuff->res;
    pTotalBuff->luk = pUnitBuff->luk + pUnitDebuff->luk;
}

void clearUnitBuff(struct Unit *unit)
{
    struct Buff *pUnitBuff = getUnitBuff(unit);
    pUnitBuff->hp = 0;
    pUnitBuff->pow = 0;
    pUnitBuff->skl = 0;
    pUnitBuff->spd = 0;
    pUnitBuff->def = 0;
    pUnitBuff->res = 0;
    pUnitBuff->luk = 0;
}

void clearUnitDebuff(struct Unit *unit)
{
    struct Buff *pUnitDebuff = getUnitDebuff(unit);
    pUnitDebuff->hp = 0;
    pUnitDebuff->pow = 0;
    pUnitDebuff->skl = 0;
    pUnitDebuff->spd = 0;
    pUnitDebuff->def = 0;
    pUnitDebuff->res = 0;
    pUnitDebuff->luk = 0;
}

void clearUnitBuffAndDebuff(struct Unit *unit)
{
    clearUnitBuff(unit);
    clearUnitDebuff(unit);
}

void clearBuffForAllPlayerUnits()
{
    struct Buff *pUnitBuff = 0;

    for(int i = 0; i < PLAYER_TOTAL_AMOUNT; i++)
    {
        pUnitBuff = &gPlayerBuff[i];

        pUnitBuff->hp = 0;
        pUnitBuff->pow = 0;
        pUnitBuff->skl = 0;
        pUnitBuff->spd = 0;
        pUnitBuff->def = 0;
        pUnitBuff->res = 0;
        pUnitBuff->luk = 0;
    }
}

void clearBuffForAllEnemyUnits()
{
    struct Buff *pUnitBuff = 0;

    for(int i = 0; i < ENEMY_TOTAL_AMOUNT; i++)
    {
        pUnitBuff = &gEnemyBuff[i];

        pUnitBuff->hp = 0;
        pUnitBuff->pow = 0;
        pUnitBuff->skl = 0;
        pUnitBuff->spd = 0;
        pUnitBuff->def = 0;
        pUnitBuff->res = 0;
        pUnitBuff->luk = 0;
    }
}

void clearBuffForAllNPCUnits()
{
    struct Buff *pUnitBuff = 0;

    for(int i = 0; i < NPC_TOTAL_AMOUNT; i++)
    {
        pUnitBuff = &gNPCBuff[i];

        pUnitBuff->hp = 0;
        pUnitBuff->pow = 0;
        pUnitBuff->skl = 0;
        pUnitBuff->spd = 0;
        pUnitBuff->def = 0;
        pUnitBuff->res = 0;
        pUnitBuff->luk = 0;
    }
}

void clearBuffForAllP4Units()
{
    struct Buff *pUnitBuff = 0;

    for(int i = 0; i < P4_TOTAL_AMOUNT; i++)
    {
        pUnitBuff = &gP4Buff[i];

        pUnitBuff->hp = 0;
        pUnitBuff->pow = 0;
        pUnitBuff->skl = 0;
        pUnitBuff->spd = 0;
        pUnitBuff->def = 0;
        pUnitBuff->res = 0;
        pUnitBuff->luk = 0;
    }
}

void clearDebuffForAllPlayerUnits()
{
    struct Buff *pUnitDebuff = 0;

    for(int i = 0; i < PLAYER_TOTAL_AMOUNT; i++)
    {
        pUnitDebuff = &gPlayerDebuff[i];

        pUnitDebuff->hp = 0;
        pUnitDebuff->pow = 0;
        pUnitDebuff->skl = 0;
        pUnitDebuff->spd = 0;
        pUnitDebuff->def = 0;
        pUnitDebuff->res = 0;
        pUnitDebuff->luk = 0;
    }
}

void clearDebuffForAllEnemyUnits()
{
    struct Buff *pUnitDebuff = 0;

    for(int i = 0; i < ENEMY_TOTAL_AMOUNT; i++)
    {
        pUnitDebuff = &gEnemyDebuff[i];

        pUnitDebuff->hp = 0;
        pUnitDebuff->pow = 0;
        pUnitDebuff->skl = 0;
        pUnitDebuff->spd = 0;
        pUnitDebuff->def = 0;
        pUnitDebuff->res = 0;
        pUnitDebuff->luk = 0;
    }
}

void clearDebuffForAllNPCUnits()
{
    struct Buff *pUnitDebuff = 0;

    for(int i = 0; i < NPC_TOTAL_AMOUNT; i++)
    {
        pUnitDebuff = &gNPCDebuff[i];

        pUnitDebuff->hp = 0;
        pUnitDebuff->pow = 0;
        pUnitDebuff->skl = 0;
        pUnitDebuff->spd = 0;
        pUnitDebuff->def = 0;
        pUnitDebuff->res = 0;
        pUnitDebuff->luk = 0;
    }
}

void clearDebuffForAllP4Units()
{
    struct Buff *pUnitDebuff = 0;

    for(int i = 0; i < P4_TOTAL_AMOUNT; i++)
    {
        pUnitDebuff = &gP4Debuff[i];

        pUnitDebuff->hp = 0;
        pUnitDebuff->pow = 0;
        pUnitDebuff->skl = 0;
        pUnitDebuff->spd = 0;
        pUnitDebuff->def = 0;
        pUnitDebuff->res = 0;
        pUnitDebuff->luk = 0;
    }
}

void clearBuffAndDebuffForAllPlayerUnits()
{
    clearBuffForAllPlayerUnits();
    clearDebuffForAllPlayerUnits();
}

void clearBuffAndDebuffForAllEnemyUnits()
{
    clearBuffForAllEnemyUnits();
    clearDebuffForAllEnemyUnits();
}

void clearBuffAndDebuffForAllNPCUnits()
{
    clearBuffForAllNPCUnits();
    clearDebuffForAllNPCUnits();
}

void clearBuffAndDebuffForAllP4Units()
{
    clearBuffForAllP4Units();
    clearDebuffForAllP4Units();
}

void clearBuffForAllUnits()
{
    clearBuffForAllPlayerUnits();
    clearBuffForAllEnemyUnits();
    clearBuffForAllNPCUnits();
    clearBuffForAllP4Units();
}

void clearDebuffForAllUnits()
{
    clearDebuffForAllPlayerUnits();
    clearDebuffForAllEnemyUnits();
    clearDebuffForAllNPCUnits();
    clearDebuffForAllP4Units();
}

void clearBuffAndDebuffForAllUnits()
{
    clearBuffForAllUnits();
    clearDebuffForAllUnits();
}

s8 getUnitBuffHP(struct Unit *unit)
{
    return checkUnitStatePanic(unit)? -getUnitBuff(unit)->hp: getUnitBuff(unit)->hp;
}

s8 getUnitBuffPower(struct Unit *unit)
{
    return checkUnitStatePanic(unit)? -getUnitBuff(unit)->pow: getUnitBuff(unit)->pow;
}

s8 getUnitBuffSkill(struct Unit *unit)
{
    return checkUnitStatePanic(unit)? -getUnitBuff(unit)->skl: getUnitBuff(unit)->skl;
}

s8 getUnitBuffSpeed(struct Unit *unit)
{
    return checkUnitStatePanic(unit)? -getUnitBuff(unit)->spd: getUnitBuff(unit)->spd;
}

s8 getUnitBuffDefense(struct Unit *unit)
{
    return checkUnitStatePanic(unit)? -getUnitBuff(unit)->def: getUnitBuff(unit)->def;
}

s8 getUnitBuffResistance(struct Unit *unit)
{
    return checkUnitStatePanic(unit)? -getUnitBuff(unit)->res: getUnitBuff(unit)->res;
}

s8 getUnitBuffLuck(struct Unit *unit)
{
    return checkUnitStatePanic(unit)? -getUnitBuff(unit)->luk: getUnitBuff(unit)->luk;
}

s8 getUnitDebuffHP(struct Unit *unit)
{
    return checkUnitStateHarshed(unit)? -getUnitDebuff(unit)->hp: getUnitDebuff(unit)->hp;
}

s8 getUnitDebuffPower(struct Unit *unit)
{
    return checkUnitStateHarshed(unit)? -getUnitDebuff(unit)->pow: getUnitDebuff(unit)->pow;
}

s8 getUnitDebuffSkill(struct Unit *unit)
{
    return checkUnitStateHarshed(unit)? -getUnitDebuff(unit)->skl: getUnitDebuff(unit)->skl;
}

s8 getUnitDebuffSpeed(struct Unit *unit)
{
    return checkUnitStateHarshed(unit)? -getUnitDebuff(unit)->spd: getUnitDebuff(unit)->spd;
}

s8 getUnitDebuffDefense(struct Unit *unit)
{
    return checkUnitStateHarshed(unit)? -getUnitDebuff(unit)->def: getUnitDebuff(unit)->def;
}

s8 getUnitDebuffResistance(struct Unit *unit)
{
    return checkUnitStateHarshed(unit)? -getUnitDebuff(unit)->res: getUnitDebuff(unit)->res;
}

s8 getUnitDebuffLuck(struct Unit *unit)
{
    return checkUnitStateHarshed(unit)? -getUnitDebuff(unit)->luk: getUnitDebuff(unit)->luk;
}

s8 getUnitTotalBuffHP(struct Unit *unit)
{
    s8 total = getUnitBuffHP(unit) + getUnitDebuffHP(unit);
    if(total > 0 && checkUnitStateBonusDoubler(unit))
        total *= 2;
    return total;
}

s8 getUnitTotalBuffPower(struct Unit *unit)
{
    s8 total = getUnitBuffPower(unit) + getUnitDebuffPower(unit);
    if(total > 0 && checkUnitStateBonusDoubler(unit))
        total *= 2;
    return total;
}

s8 getUnitTotalBuffSkill(struct Unit *unit)
{
    s8 total = getUnitBuffSkill(unit) + getUnitDebuffSkill(unit);
    if(total > 0 && checkUnitStateBonusDoubler(unit))
        total *= 2;
    return total;
}

s8 getUnitTotalBuffSpeed(struct Unit *unit)
{
    s8 total = getUnitBuffSpeed(unit) + getUnitDebuffSpeed(unit);
    if(total > 0 && checkUnitStateBonusDoubler(unit))
        total *= 2;
    return total;
}

s8 getUnitTotalBuffDefense(struct Unit *unit)
{
    s8 total = getUnitBuffDefense(unit) + getUnitDebuffDefense(unit);
    if(total > 0 && checkUnitStateBonusDoubler(unit))
        total *= 2;
    return total;
}

s8 getUnitTotalBuffResistance(struct Unit *unit)
{
    s8 total = getUnitBuffResistance(unit) + getUnitDebuffResistance(unit);
    if(total > 0 && checkUnitStateBonusDoubler(unit))
        total *= 2;
    return total;
}

s8 getUnitTotalBuffLuck(struct Unit *unit)
{
    s8 total = getUnitBuffLuck(unit) + getUnitDebuffLuck(unit);
    if(total > 0 && checkUnitStateBonusDoubler(unit))
        total *= 2;
    return total;
}

void addUnitBuff(struct Unit *unit, struct Buff *pBuff)
{
    struct Buff *pUnitBuff = getUnitBuff(unit);
    pUnitBuff->hp += pBuff->hp;
    pUnitBuff->pow += pBuff->pow;
    pUnitBuff->skl += pBuff->skl;
    pUnitBuff->spd += pBuff->spd;
    pUnitBuff->def += pBuff->def;
    pUnitBuff->res += pBuff->res;
    pUnitBuff->luk += pBuff->luk;
}

void addUnitDebuff(struct Unit *unit, struct Buff *pDebuff)
{
    struct Buff *pUnitDebuff = getUnitDebuff(unit);
    pUnitDebuff->hp += pDebuff->hp;
    pUnitDebuff->pow += pDebuff->pow;
    pUnitDebuff->skl += pDebuff->skl;
    pUnitDebuff->spd += pDebuff->spd;
    pUnitDebuff->def += pDebuff->def;
    pUnitDebuff->res += pDebuff->res;
    pUnitDebuff->luk += pDebuff->luk;
}

void addUnitBuffHP(struct Unit *unit, s8 buffValue)
{
    struct Buff *pUnitBuff = getUnitBuff(unit);
    pUnitBuff->hp += buffValue;
}

void addUnitBuffPower(struct Unit *unit, s8 buffValue)
{
    struct Buff *pUnitBuff = getUnitBuff(unit);
    pUnitBuff->pow += buffValue;
}

void addUnitBuffSkill(struct Unit *unit, s8 buffValue)
{
    struct Buff *pUnitBuff = getUnitBuff(unit);
    pUnitBuff->skl += buffValue;
}

void addUnitBuffSpeed(struct Unit *unit, s8 buffValue)
{
    struct Buff *pUnitBuff = getUnitBuff(unit);
    pUnitBuff->spd += buffValue;
}

void addUnitBuffDefense(struct Unit *unit, s8 buffValue)
{
    struct Buff *pUnitBuff = getUnitBuff(unit);
    pUnitBuff->def += buffValue;
}

void addUnitBuffResistance(struct Unit *unit, s8 buffValue)
{
    struct Buff *pUnitBuff = getUnitBuff(unit);
    pUnitBuff->res += buffValue;
}

void addUnitBuffLuck(struct Unit *unit, s8 buffValue)
{
    struct Buff *pUnitBuff = getUnitBuff(unit);
    pUnitBuff->luk += buffValue;
}

void addUnitDebuffHP(struct Unit *unit, s8 debuffValue)
{
    struct Buff *pUnitDebuff = getUnitDebuff(unit);
    pUnitDebuff->hp += debuffValue;
}

void addUnitDebuffPower(struct Unit *unit, s8 debuffValue)
{
    struct Buff *pUnitDebuff = getUnitDebuff(unit);
    pUnitDebuff->pow += debuffValue;
}

void addUnitDebuffSkill(struct Unit *unit, s8 debuffValue)
{
    struct Buff *pUnitDebuff = getUnitDebuff(unit);
    pUnitDebuff->skl += debuffValue;
}

void addUnitDebuffSpeed(struct Unit *unit, s8 debuffValue)
{
    struct Buff *pUnitDebuff = getUnitDebuff(unit);
    pUnitDebuff->spd += debuffValue;
}

void addUnitDebuffDefense(struct Unit *unit, s8 debuffValue)
{
    struct Buff *pUnitDebuff = getUnitDebuff(unit);
    pUnitDebuff->def += debuffValue;
}

void addUnitDebuffResistance(struct Unit *unit, s8 debuffValue)
{
    struct Buff *pUnitDebuff = getUnitDebuff(unit);
    pUnitDebuff->res += debuffValue;
}

void addUnitDebuffLuck(struct Unit *unit, s8 debuffValue)
{
    struct Buff *pUnitDebuff = getUnitDebuff(unit);
    pUnitDebuff->luk += debuffValue;
}

/*
 * Effect & Display
 */

int GetUnitMaxHp(struct Unit* unit) 
{
    return unit->maxHp + GetItemHpBonus(GetUnitEquippedItem(unit)) + getUnitTotalBuffHP(unit);
}

int GetUnitPower(struct Unit* unit) 
{
    return unit->pow + GetItemPowBonus(GetUnitEquippedItem(unit)) + getUnitTotalBuffPower(unit);
}

int GetUnitSkill(struct Unit* unit) 
{
    int item = GetUnitEquippedItem(unit);

    if (unit->state & UNIT_STATE_RESCUING)
        return unit->skl / 2 + GetItemSklBonus(item) + getUnitTotalBuffSkill(unit);

    return unit->skl + GetItemSklBonus(item) + getUnitTotalBuffSkill(unit);
}

int GetUnitSpeed(struct Unit* unit) 
{
    int item = GetUnitEquippedItem(unit);

    if (unit->state & UNIT_STATE_RESCUING)
        return unit->spd / 2 + GetItemSpdBonus(item) + getUnitTotalBuffSpeed(unit);

    return unit->spd + GetItemSpdBonus(item) + getUnitTotalBuffSpeed(unit);
}

int GetUnitDefense(struct Unit* unit) 
{
    return unit->def + GetItemDefBonus(GetUnitEquippedItem(unit)) + getUnitTotalBuffDefense(unit);
}

int GetUnitResistance(struct Unit* unit) 
{
    return unit->res + GetItemResBonus(GetUnitEquippedItem(unit)) + unit->resBonus + getUnitTotalBuffResistance(unit);
}

int GetUnitLuck(struct Unit* unit) 
{
    return unit->luk + GetItemLukBonus(GetUnitEquippedItem(unit)) + getUnitTotalBuffLuck(unit);
}

int GetUnitMaxHpInjector(struct Unit* unit)
{
    return GetUnitMaxHp(unit);
}

int GetUnitPowerInjector(struct Unit* unit)
{
    return GetUnitPower(unit);
}

int GetUnitSkillInjector(struct Unit* unit)
{
    return GetUnitSkill(unit);
}

int GetUnitSpeedInjector(struct Unit* unit)
{
    return GetUnitSpeed(unit);
}

int GetUnitDefenseInjector(struct Unit* unit)
{
    return GetUnitDefense(unit);
}

int GetUnitResistanceInjector(struct Unit* unit)
{
    return GetUnitResistance(unit);
}

int GetUnitLuckInjector(struct Unit* unit)
{
    return GetUnitLuck(unit);
}

/*
 * Display buff & debuff
 */

void DrawStatScreenBonusNumber(int bonusNumber, u16 *tileMap)
{
    if (bonusNumber > 0)
    {
        // Draw '+' before bonus number
        DrawUiSymbol(tileMap, TEXT_COLOR_GREEN, 21);
        // Draw positive bonus number
        DrawUiSmallNumber(tileMap + ((bonusNumber >= 10) ? 2 : 1), TEXT_COLOR_GREEN, bonusNumber);
    }
    else
    {
        if (bonusNumber < 0)
        {
            // Draw '-' before bonus number
            DrawUiSymbol(tileMap, TEXT_COLOR_GRAY, 20);
            // Draw negative bonus number
            DrawUiSmallNumber(tileMap + ((bonusNumber >= 10) ? 2 : 1), TEXT_COLOR_GRAY, -bonusNumber);            
        }
    }
}

void DrawStatScreenBonusNumberInjector(int bonusNumber, u16 *tileMap)
{
    DrawStatScreenBonusNumber(bonusNumber, tileMap);
}

/*
 * Duration: 1 turn. Clear units' buff & debuff when switching phase.
 */

// Phase switch: player phase -> enemy phase -> NPC phase -> player phase -> ...
void clearUnitsBuffAndDebuffForPhaseSwitch()
{
    switch (gRAMChapterData.chapterPhaseIndex >> 6)
    {
        case NPCSide: //PlayerSide
            if(gRAMChapterData.chapterTurnNumber == 0)
                clearBuffAndDebuffForAllUnits();
            else
                clearBuffAndDebuffForAllPlayerUnits();
            break;
        case PlayerSide: //EnemySide
            clearBuffAndDebuffForAllEnemyUnits();
            break;
        case EnemySide: //NPCSide
            clearBuffAndDebuffForAllNPCUnits();
            break;
        default: //TODO: for link arena
            clearBuffAndDebuffForAllP4Units();
            break;
    }
}

u32 phaseSwitchInjector()
{
    clearUnitsBuffAndDebuffForPhaseSwitch();
    return func8015818();
}

const struct ProcCmd gProcPhaseSwitchInjector = PROC_CALL_ROUTINE_2(phaseSwitchInjector);

