/*
 * Buff & Debuff
 */

#include <gba_base.h>

#include "buff.h"

#include "character.h"
#include "fontgrp.h"
#include "skill.h"
#include "skill_id.h"
#include "proc.h"
#include "new_unit_state.h"
#include "gba_debug_print.h"

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

void clearBuffAndDebuffForPlayerUnits()
{
    clearBuffAndDebuffForAllPlayerUnits();
}

void clearBuffAndDebuffForAllEnemyUnits()
{
    clearBuffForAllEnemyUnits();
    clearDebuffForAllEnemyUnits();
}

void clearBuffAndDebuffForEnemyUnits()
{
    clearBuffAndDebuffForAllEnemyUnits();
}

void clearBuffAndDebuffForAllNPCUnits()
{
    clearBuffForAllNPCUnits();
    clearDebuffForAllNPCUnits();
}

void clearBuffAndDebuffForNPCUnits()
{
    clearBuffAndDebuffForAllNPCUnits();
}

void clearBuffAndDebuffForAllP4Units()
{
    clearBuffForAllP4Units();
    clearDebuffForAllP4Units();
}

void clearBuffAndDebuffForP4Units()
{
    clearBuffAndDebuffForAllP4Units();
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

// updateUnitBuffXXX is for passive skill C Spur series

void updateUnitBuffHP(struct Unit *unit, s8 buffValue)
{
    struct Buff *pUnitBuff = getUnitBuff(unit);
    if(pUnitBuff->hp < buffValue)
        pUnitBuff->hp = buffValue;
}

void updateUnitBuffPower(struct Unit *unit, s8 buffValue)
{
    struct Buff *pUnitBuff = getUnitBuff(unit);
    if(pUnitBuff->pow < buffValue)
        pUnitBuff->pow = buffValue;
}

void updateUnitBuffSkill(struct Unit *unit, s8 buffValue)
{
    struct Buff *pUnitBuff = getUnitBuff(unit);
    if(pUnitBuff->skl < buffValue)
        pUnitBuff->skl = buffValue;
}

void updateUnitBuffSpeed(struct Unit *unit, s8 buffValue)
{
    struct Buff *pUnitBuff = getUnitBuff(unit);
    if(pUnitBuff->spd < buffValue)
        pUnitBuff->spd = buffValue;
}

void updateUnitBuffDefense(struct Unit *unit, s8 buffValue)
{
    struct Buff *pUnitBuff = getUnitBuff(unit);
    if(pUnitBuff->def < buffValue)
        pUnitBuff->def = buffValue;
}

void updateUnitBuffResistance(struct Unit *unit, s8 buffValue)
{
    struct Buff *pUnitBuff = getUnitBuff(unit);
    if(pUnitBuff->res < buffValue)
        pUnitBuff->res = buffValue;
}

void updateUnitBuffLuck(struct Unit *unit, s8 buffValue)
{
    struct Buff *pUnitBuff = getUnitBuff(unit);
    if(pUnitBuff->luk < buffValue)
        pUnitBuff->luk = buffValue;
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
    int maxHp = unit->maxHp + GetItemHpBonus(GetUnitEquippedItem(unit)) + getUnitTotalBuffHP(unit);

    switch(getUnitPassiveSkillA(unit))
    {
        case PASSIVE_SKILL_A_TEMPTATION_1:
            maxHp += 3;
            break;
        case PASSIVE_SKILL_A_TEMPTATION_2:
            maxHp += 4;
            break;
        case PASSIVE_SKILL_A_TEMPTATION_3:
            maxHp += 5;
            break;
        case PASSIVE_SKILL_A_TEMPTATION_4:
            maxHp += 7;
            break;
        default:
            break;
    }

    return maxHp;
}

int GetUnitHp(struct Unit* unit)
{
    if(unit->hp > GetUnitMaxHp(unit))
        unit->hp = GetUnitMaxHp(unit);
    return unit->hp;
}

int GetUnitPower(struct Unit* unit) 
{
    int power = unit->pow + GetItemPowBonus(GetUnitEquippedItem(unit)) + getUnitTotalBuffPower(unit);

    switch(getUnitPassiveSkillA(unit))
    {
        case PASSIVE_SKILL_A_FURY_1:
            power += 1;
            break;
        case PASSIVE_SKILL_A_FURY_2:
            power += 2;
            break;
        case PASSIVE_SKILL_A_FURY_3:
            power += 3;
            break;
        case PASSIVE_SKILL_A_FURY_4:
            power += 4;
            break;
        default:
            break;
    }

    return power;
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
    int speed = GetItemSpdBonus(item) + getUnitTotalBuffSpeed(unit);

    if (unit->state & UNIT_STATE_RESCUING)
        speed += unit->spd / 2;
    else
        speed += unit->spd;

    switch(getUnitPassiveSkillA(unit))
    {
        case PASSIVE_SKILL_A_SPEED_1:
            speed += 1;
            break;
        case PASSIVE_SKILL_A_SPEED_2:
            speed += 2;
            break;
        case PASSIVE_SKILL_A_SPEED_3:
            speed += 3;
            break;
        case PASSIVE_SKILL_A_SPEED_4:
            speed += 4;
            break;
        case PASSIVE_SKILL_A_FURY_1:
            speed += 1;
            break;
        case PASSIVE_SKILL_A_FURY_2:
            speed += 2;
            break;
        case PASSIVE_SKILL_A_FURY_3:
            speed += 3;
            break;
        case PASSIVE_SKILL_A_FURY_4:
            speed += 4;
            break;
        default:
            break;
    }

    return speed;
}

int GetUnitDefense(struct Unit* unit) 
{
    int defense = unit->def + GetItemDefBonus(GetUnitEquippedItem(unit)) + getUnitTotalBuffDefense(unit);

    switch(getUnitPassiveSkillA(unit))
    {
        case PASSIVE_SKILL_A_FURY_1:
            defense += 1;
            break;
        case PASSIVE_SKILL_A_FURY_2:
            defense += 2;
            break;
        case PASSIVE_SKILL_A_FURY_3:
            defense += 3;
            break;
        case PASSIVE_SKILL_A_FURY_4:
            defense += 4;
            break;
        default:
            break;
    }

    return defense;
}

int GetUnitResistance(struct Unit* unit) 
{
    int resistance = unit->res + GetItemResBonus(GetUnitEquippedItem(unit)) + unit->resBonus + getUnitTotalBuffResistance(unit);
    
    switch(getUnitPassiveSkillA(unit))
    {
        case PASSIVE_SKILL_A_FURY_1:
            resistance += 1;
            break;
        case PASSIVE_SKILL_A_FURY_2:
            resistance += 2;
            break;
        case PASSIVE_SKILL_A_FURY_3:
            resistance += 3;
            break;
        case PASSIVE_SKILL_A_FURY_4:
            resistance += 4;
            break;
        default:
            break;
    }

    return resistance;
}

int GetUnitLuck(struct Unit* unit) 
{
    return unit->luk + GetItemLukBonus(GetUnitEquippedItem(unit)) + getUnitTotalBuffLuck(unit);
}

#pragma GCC push_options
#pragma GCC optimize ("-O2")

int GetUnitHpInjector(struct Unit* unit)
{
    return GetUnitHp(unit);
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

#pragma GCC pop_options

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

void clearBuffDebuffAndNewStateForAllUnits()
{
    clearBuffAndDebuffForAllUnits();
    clearNewStateForAllUnits();
}

void clearBuffDebuffAndNewStateForPlayerUnits()
{
    clearBuffAndDebuffForPlayerUnits();
    clearNewStateForPlayerUnits();
}

void clearBuffDebuffAndNewStateForEnemyUnits()
{
    clearBuffAndDebuffForEnemyUnits();
    clearNewStateForEnemyUnits();
}

void clearBuffDebuffAndNewStateForNPCUnits()
{
    clearBuffAndDebuffForNPCUnits();
    clearNewStateForNPCUnits();
}

void clearBuffDebuffAndNewStateForP4Units()
{
    clearBuffAndDebuffForP4Units();
    clearNewStateForP4Units();
}

void updateNewStateWithPassiveSkillA(struct Unit *skillUnits, int skillUnitNumber, struct Unit *targetUnits, int targetUnitNumber)
{
    for(int i = 0; i < skillUnitNumber; i++)
    {
        if((skillUnits[i].state & UNIT_STATE_DEAD) == 0 && getUnitPassiveSkillA(&skillUnits[i]))
        {
            for(int j = 0; j < targetUnitNumber; j++)
            {
                if((targetUnits[j].state & UNIT_STATE_DEAD) == 0)
                {
                    switch(getUnitPassiveSkillA(&skillUnits[i]))
                    {
                        case PASSIVE_SKILL_A_TEMPTATION_1:
                            if((skillUnits[i].positionX == targetUnits[j].positionX || skillUnits[i].positionY == targetUnits[j].positionY) && GetUnitHp(&targetUnits[j]) <= GetUnitHp(&skillUnits[i]) - 5)
                                 setUnitStateGravity(&targetUnits[j]);
                            break;
                        case PASSIVE_SKILL_A_TEMPTATION_2:
                            if((skillUnits[i].positionX == targetUnits[j].positionX || skillUnits[i].positionY == targetUnits[j].positionY) && GetUnitHp(&targetUnits[j]) <= GetUnitHp(&skillUnits[i]) - 3)
                                 setUnitStateGravity(&targetUnits[j]);
                            break;
                        case PASSIVE_SKILL_A_TEMPTATION_3:
                            if((skillUnits[i].positionX == targetUnits[j].positionX || skillUnits[i].positionY == targetUnits[j].positionY) && GetUnitHp(&targetUnits[j]) <= GetUnitHp(&skillUnits[i]) - 1)
                                 setUnitStateGravity(&targetUnits[j]);
                            break;
                        case PASSIVE_SKILL_A_TEMPTATION_4:
                            if(skillUnits[i].positionX == targetUnits[j].positionX || skillUnits[i].positionY == targetUnits[j].positionY)
                                 setUnitStateGravity(&targetUnits[j]);
                            break;
                        default:
                            break;
                    }

                    switch(getUnitPassiveSkillC(&skillUnits[i]))
                    {
                        case PASSIVE_SKILL_C_SURTR_MENACE:
                            if(getDistanceBetweenTwoUnits(&skillUnits[i], &targetUnits[j]) <= 2)
                            {
                                targetUnits[j].hp -= 20;
                                if(targetUnits[j].hp < 1)
                                    targetUnits[j].hp = 1;
                                addUnitBuffPower(&skillUnits[i], 4);
                                addUnitBuffSpeed(&skillUnits[i], 4);
                                addUnitBuffDefense(&skillUnits[i], 4);
                                addUnitBuffResistance(&skillUnits[i], 4);
                                addUnitDebuffPower(&targetUnits[j], -4);
                                addUnitDebuffSpeed(&targetUnits[j], -4);
                                addUnitDebuffDefense(&targetUnits[j], -4);
                                addUnitDebuffResistance(&targetUnits[j], -4);
                            }
                            break;
                        default:
                            break;
                    }
                }
            }
        }
    }
}

void updateNewStateWithPassiveSkillAForPlayerUnits()
{
    updateNewStateWithPassiveSkillA(enemyUnits, ENEMY_TOTAL_AMOUNT, playerUnits, PLAYER_TOTAL_AMOUNT);
    updateNewStateWithPassiveSkillA(P4Units, P4_TOTAL_AMOUNT, playerUnits, PLAYER_TOTAL_AMOUNT);
}

void updateNewStateWithPassiveSkillAForEnemyUnits()
{
    updateNewStateWithPassiveSkillA(playerUnits, PLAYER_TOTAL_AMOUNT, enemyUnits, ENEMY_TOTAL_AMOUNT);
    updateNewStateWithPassiveSkillA(NPCUnits, NPC_TOTAL_AMOUNT, enemyUnits, ENEMY_TOTAL_AMOUNT);
}

void updateNewStateWithPassiveSkillAForNPCUnits()
{
    updateNewStateWithPassiveSkillA(enemyUnits, ENEMY_TOTAL_AMOUNT, NPCUnits, NPC_TOTAL_AMOUNT);
    updateNewStateWithPassiveSkillA(P4Units, P4_TOTAL_AMOUNT, NPCUnits, NPC_TOTAL_AMOUNT);
}

void updateNewStateWithPassiveSkillAForP4Units()
{
    updateNewStateWithPassiveSkillA(playerUnits, PLAYER_TOTAL_AMOUNT, P4Units, P4_TOTAL_AMOUNT);
    updateNewStateWithPassiveSkillA(NPCUnits, NPC_TOTAL_AMOUNT, P4Units, P4_TOTAL_AMOUNT);
}

void updateBuffAndDebuffWithPassiveSkillC(struct Unit *units, int number)
{
    for(int i = 0; i < number; i++)
    {
        if((units[i].state & UNIT_STATE_DEAD) == 0)
        {
            for(int j = 0; j < number; j++)
            {
                if((units[j].state & UNIT_STATE_DEAD) == 0)
                {
                    u32 distance = RECT_DISTANCE(units[i].positionX, units[i].positionY, units[j].positionX, units[j].positionY);
                        
                    switch(getUnitPassiveSkillC(&units[j]))
                    {
                        case PASSIVE_SKILL_C_FORTIFY_DEF_1:
                            if(distance == 1)
                                updateUnitBuffDefense(&units[i], 2);
                            break;
                        case PASSIVE_SKILL_C_FORTIFY_DEF_2:
                            if(distance == 1)
                                updateUnitBuffDefense(&units[i], 3);
                            break;
                        case PASSIVE_SKILL_C_FORTIFY_DEF_3:
                            if(distance == 1)
                                updateUnitBuffDefense(&units[i], 4);
                            break;
                        case PASSIVE_SKILL_C_FORTIFY_DEF_4:
                            if(distance == 1)
                                updateUnitBuffDefense(&units[i], 5);
                            break;
                        case PASSIVE_SKILL_C_ODD_ATK_WAVE_1:
                            if((gRAMChapterData.chapterTurnNumber % 2) && distance <= 1)
                                updateUnitBuffPower(&units[i], 2);
                            break;
                        case PASSIVE_SKILL_C_ODD_ATK_WAVE_2:
                            if((gRAMChapterData.chapterTurnNumber % 2) && distance <= 1)
                                updateUnitBuffPower(&units[i], 4);
                            break;
                        case PASSIVE_SKILL_C_ODD_ATK_WAVE_3:
                            if((gRAMChapterData.chapterTurnNumber % 2) && distance <= 1)
                                updateUnitBuffPower(&units[i], 6);
                            break;
                        case PASSIVE_SKILL_C_ODD_ATK_WAVE_4:
                            if((gRAMChapterData.chapterTurnNumber % 2) && distance <= 1)
                                updateUnitBuffPower(&units[i], 8);
                            break;
                        case PASSIVE_SKILL_C_ODD_SPD_WAVE_1:
                            if((gRAMChapterData.chapterTurnNumber % 2) && distance <= 1)
                                updateUnitBuffSpeed(&units[i], 2);
                            break;
                        case PASSIVE_SKILL_C_ODD_SPD_WAVE_2:
                            if((gRAMChapterData.chapterTurnNumber % 2) && distance <= 1)
                                updateUnitBuffSpeed(&units[i], 4);
                            break;
                        case PASSIVE_SKILL_C_ODD_SPD_WAVE_3:
                            if((gRAMChapterData.chapterTurnNumber % 2) && distance <= 1)
                                updateUnitBuffSpeed(&units[i], 6);
                            break;
                        case PASSIVE_SKILL_C_ODD_SPD_WAVE_4:
                            if((gRAMChapterData.chapterTurnNumber % 2) && distance <= 1)
                                updateUnitBuffSpeed(&units[i], 8);
                            break;
                        default:
                            break;
                    }
                }
            }
        }
    }
}

void updateBuffAndDebuffWithPassiveSkillCForPlayerUnits()
{
    updateBuffAndDebuffWithPassiveSkillC(playerUnits, PLAYER_TOTAL_AMOUNT);
}

void updateBuffAndDebuffWithPassiveSkillCForEnemyUnits()
{
    updateBuffAndDebuffWithPassiveSkillC(enemyUnits, ENEMY_TOTAL_AMOUNT);
}

void updateBuffAndDebuffWithPassiveSkillCForNPCUnits()
{
    updateBuffAndDebuffWithPassiveSkillC(NPCUnits, NPC_TOTAL_AMOUNT);
}

void updateBuffAndDebuffWithPassiveSkillCForP4Units()
{
    updateBuffAndDebuffWithPassiveSkillC(P4Units, P4_TOTAL_AMOUNT);
}

/*
 * Duration: 1 turn. Clear units' buff & debuff when switching phase.
 */

// Phase switch: player phase -> enemy phase -> NPC phase -> player phase -> ...
// 1st player phase doesn't have a NPC phase before it, so the units have buff & debuff from previous chapter at the 1st turn.
void clearUnitsBuffAndDebuffForPhaseSwitch()
{
    switch (gRAMChapterData.chapterPhaseIndex >> 6)
    {
        case NPCSide: //PlayerSide
            if(gRAMChapterData.chapterTurnNumber == 0)
                clearBuffDebuffAndNewStateForAllUnits();
            else
                clearBuffDebuffAndNewStateForPlayerUnits();
            updateBuffAndDebuffWithPassiveSkillCForPlayerUnits();
            break;
        case PlayerSide: //EnemySide
            clearBuffDebuffAndNewStateForEnemyUnits();
            updateBuffAndDebuffWithPassiveSkillCForEnemyUnits();
            break;
        case EnemySide: //NPCSide
            clearBuffDebuffAndNewStateForNPCUnits();
            updateBuffAndDebuffWithPassiveSkillCForNPCUnits();
            break;
        default: //TODO: for link arena
            clearBuffDebuffAndNewStateForP4Units();
            updateBuffAndDebuffWithPassiveSkillCForP4Units();
            break;
    }
}

void clearUnitsBuffAndDebuffEachTurn()
{
    switch (gRAMChapterData.chapterPhaseIndex >> 6)
    {
        case PlayerSide: //PlayerSide
            if(gRAMChapterData.chapterTurnNumber == 1)
                clearBuffDebuffAndNewStateForAllUnits();
            else
                clearBuffDebuffAndNewStateForPlayerUnits();
            updateBuffAndDebuffWithPassiveSkillCForPlayerUnits();
            updateNewStateWithPassiveSkillAForPlayerUnits();
            break;
        case EnemySide: //EnemySide
            clearBuffDebuffAndNewStateForEnemyUnits();
            updateBuffAndDebuffWithPassiveSkillCForEnemyUnits();
            updateNewStateWithPassiveSkillAForEnemyUnits();
            break;
        case NPCSide: //NPCSide
            clearBuffDebuffAndNewStateForNPCUnits();
            updateBuffAndDebuffWithPassiveSkillCForNPCUnits();
            updateNewStateWithPassiveSkillAForNPCUnits();
            break;
        default: //TODO: for link arena
            clearBuffDebuffAndNewStateForP4Units();
            updateBuffAndDebuffWithPassiveSkillCForP4Units();
            updateNewStateWithPassiveSkillAForP4Units();
            break;
    }
}

u32 phaseSwitchInjector()
{
    //clearUnitsBuffAndDebuffForPhaseSwitch();
    return func8015818();
}

const struct ProcCmd gProcPhaseSwitchInjector = PROC_CALL_ROUTINE_2(phaseSwitchInjector);

int GetSkillHealAmount(struct Unit *unit)
{
    int healAmount = 0;

    switch(getUnitPassiveSkillB(unit))
    {
        case PASSIVE_SKILL_B_RENEWAL_1:
            if(gRAMChapterData.chapterTurnNumber % 4 == 1)
                healAmount += 10;
            break;
        case PASSIVE_SKILL_B_RENEWAL_2:
            if(gRAMChapterData.chapterTurnNumber % 3 == 1)
                healAmount += 10;
            break;
        case PASSIVE_SKILL_B_RENEWAL_3:
            if(gRAMChapterData.chapterTurnNumber % 2 == 1)
                healAmount += 10;
            break;
        case PASSIVE_SKILL_B_RENEWAL_4:
                healAmount += 10;
            break;
        default:
            break;
    }

    return healAmount;
}

void HealUnitsHPByTerrain(int unitIDSideBase)
{
    struct Unit *unit;
    int terrain;
    int healAmount;

    InitTargets(0,0);

    for(int i = unitIDSideBase + 1; i < 0x40; i++)
    {
        unit = GetUnit(i);
        if(unit && unit->character && !(unit->state & (UNIT_STATE_UNAVAILABLE | UNIT_STATE_RESCUED)))
        {
            terrain = gBmMapTerrain[unit->positionY][unit->positionX];
            healAmount = GetTerrainHealAmount(terrain) + GetSkillHealAmount(unit);
            if(healAmount)
            {
                if(GetUnitHp(unit) < GetUnitMaxHp(unit))
                {
                    AddTarget(unit->positionX, unit->positionY, unit->number + unit->side * 0x40, GetUnitMaxHp(unit) * healAmount / 100);
                }
            }
            if((GetTerrainCureBadStatus(terrain) & 0xff) && unit->stateType)
            {
                AddTarget(unit->positionX, unit->positionY, unit->number + unit->side * 0x40, 0xff);
            }
        }
    }
}

void UpdateUnitSkillCDEachTurn(struct Unit *unit)
{

}

void UpdateUnitsSkillCDEachTurnForSide(struct Unit *units, int number)
{
    for(int i = 0; i < number; i++)
        UpdateUnitSkillCDEachTurn(&units[i]);
}

void UpdateSkillCDEachTurnForPlayerUnits()
{
    UpdateUnitsSkillCDEachTurnForSide(playerUnits, PLAYER_TOTAL_AMOUNT);
}

void UpdateSkillCDEachTurnForEnemyUnits()
{
    UpdateUnitsSkillCDEachTurnForSide(enemyUnits, ENEMY_TOTAL_AMOUNT);
}

void UpdateSkillCDEachTurnForNPCUnits()
{
    UpdateUnitsSkillCDEachTurnForSide(NPCUnits, NPC_TOTAL_AMOUNT);
}

void UpdateSkillCDEachTurnForP4Units()
{    
    UpdateUnitsSkillCDEachTurnForSide(P4Units, P4_TOTAL_AMOUNT);
}

void UpdateUnitsSkillCDEachTurn()
{
    UpdateSkillCDEachTurnForPlayerUnits();
    UpdateSkillCDEachTurnForEnemyUnits();
    UpdateSkillCDEachTurnForNPCUnits();
    UpdateSkillCDEachTurnForP4Units();
}

void HealUnitsHPEachTurn(struct Proc *proc)
{
    HealUnitsHPByTerrain(gRAMChapterData.chapterPhaseIndex);

    if(GetTargetListSize())
    {
        proc->data[0x23] = 0;
        proc->data[0x24] = 0;
    }
    else
    {
        EndProc(proc);
    }
}

void HealUnitsHPEachTurnInjector(struct Proc *proc)
{
    clearUnitsBuffAndDebuffEachTurn();
    HealUnitsHPEachTurn(proc);
    //if(gRAMChapterData.chapterTurnNumber == 1) // 1st turn only
        //UpdateUnitsSkillCDEachTurn();
}

const struct ProcCmd gProcHealUnitsHPEachTurnInjector = PROC_CALL_ROUTINE(HealUnitsHPEachTurnInjector);

