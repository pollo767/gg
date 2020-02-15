//
// Created by laqieer on 2019/12/22.
//

#include "portrait.h"
#include "gba_debug_print.h"
#include <gba_base.h>
#include <gba_sprites.h>

#include "portrait_alfonse_tileset.h"
#include "portrait_alfonse_mini.h"
#include "portrait_Anna_commander_tileset.h"
#include "portrait_Anna_commander_mini.h"
#include "portrait_Sharena_princess_tileset.h"
#include "portrait_Sharena_princess_mini.h"
#include "portrait_Bruno_mini.h"
#include "portrait_Bruno_tileset.h"

const Portrait portraitAlfonse = {
        portrait_alfonse_tilesetTiles,
        portrait_alfonse_miniTiles,
        portrait_alfonse_tilesetPal,
        0, 0, 0, 0
};

const u16 portrait_Bruno_obj[] = {
        7,
        OBJ_Y(-8) | ATTR0_WIDE, OBJ_X(0 - 48) | OBJ_SIZE(3), OBJ_CHAR(0),
        OBJ_Y(-8) | ATTR0_TALL, OBJ_X(64 - 48) | OBJ_SIZE(2), OBJ_CHAR(8),
        OBJ_Y(-8) | ATTR0_TALL, OBJ_X(80 - 48) | OBJ_SIZE(1), OBJ_CHAR(10),
        OBJ_Y(-8 + 32) | ATTR0_WIDE, OBJ_X(8 - 48) | OBJ_SIZE(3), OBJ_CHAR(11),
        OBJ_Y(-8 + 32) | ATTR0_TALL, OBJ_X(72 - 48) | OBJ_SIZE(1), OBJ_CHAR(19),
        OBJ_Y(-8 + 32 * 2 - 8) | ATTR0_WIDE, OBJ_X(0 - 48) | OBJ_SIZE(3), OBJ_CHAR(20),
        OBJ_Y(-8 + 32 * 2 - 8) | ATTR0_SQUARE, OBJ_X(64 - 48) | OBJ_SIZE(2), OBJ_CHAR(28),
        7,
        OBJ_Y(-8) | ATTR0_WIDE, OBJ_X(- (0 - 48) - 64) | OBJ_SIZE(3) | OBJ_HFLIP, OBJ_CHAR(0),
        OBJ_Y(-8) | ATTR0_TALL, OBJ_X(- (64 - 48) - 16) | OBJ_SIZE(2) | OBJ_HFLIP, OBJ_CHAR(8),
        OBJ_Y(-8) | ATTR0_TALL, OBJ_X(- (80 - 48) - 16) | OBJ_SIZE(1) | OBJ_HFLIP, OBJ_CHAR(10),
        OBJ_Y(-8 + 32) | ATTR0_WIDE, OBJ_X(- (8 - 48) - 64) | OBJ_SIZE(3) | OBJ_HFLIP, OBJ_CHAR(11),
        OBJ_Y(-8 + 32) | ATTR0_TALL, OBJ_X(- (72 - 48) - 32) | OBJ_SIZE(1) | OBJ_HFLIP, OBJ_CHAR(19),
        OBJ_Y(-8 + 32 * 2 - 8) | ATTR0_WIDE, OBJ_X(- (0 - 48) - 64) | OBJ_SIZE(3) | OBJ_HFLIP, OBJ_CHAR(20),
        OBJ_Y(-8 + 32 * 2 - 8) | ATTR0_SQUARE, OBJ_X(- (64 - 48) - 16) | OBJ_SIZE(2) | OBJ_HFLIP, OBJ_CHAR(28),
};

const u16 portrait_Bruno_bg[] = {
        0x809,
        20 + 32, 21 + 32, 22 + 32, 23 + 32, 24 + 32, 25 + 32, 26 + 32, 27 + 32, 28 + 32, 29 + 32,
        0, 11 + 32 * 3, 12 + 32 * 3, 13 + 32 * 3, 14 + 32 * 3, 15 + 32 * 3, 16 + 32 * 3, 17 + 32 * 3, 18 + 32 * 3, 19 + 32 * 3,
        0, 11 + 32 * 2, 12 + 32 * 2, 13 + 32 * 2, 14 + 32 * 2, 15 + 32 * 2, 16 + 32 * 2, 17 + 32 * 2, 18 + 32 * 2, 19 + 32 * 2,
        0, 11 + 32, 12 + 32, 13 + 32, 14 + 32, 15 + 32, 16 + 32, 17 + 32, 18 + 32, 19 + 32,
        0, 11, 12, 13, 14, 15, 16, 17, 18, 19,
        0 + 32 * 3, 1 + 32 * 3, 2 + 32 * 3, 3 + 32 * 3, 4 + 32 * 3, 5 + 32 * 3, 6 + 32 * 3, 7 + 32 * 3, 8 + 32 * 3, 9 + 32 * 3,
        0 + 32 * 2, 1 + 32 * 2, 2 + 32 * 2, 3 + 32 * 2, 4 + 32 * 2, 5 + 32 * 2, 6 + 32 * 2, 7 + 32 * 2, 8 + 32 * 2, 9 + 32 * 2,
        0 + 32, 1 + 32, 2 + 32, 3 + 32, 4 + 32, 5 + 32, 6 + 32, 7 + 32, 8 + 32, 9 + 32,
        0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
};

DEFINE_PORTRAIT(Anna_commander)
DEFINE_PORTRAIT(Sharena_princess)
DEFINE_PORTRAIT_SPECIAL_WITHOUT_MASK(Bruno)

const Portrait* const portraits[] = {
    [0x101] = &portraitAlfonse,
    [0x102] = &portraitSharena_princess,
    [0x103] = &portraitAnna_commander,
    [0x104] = &portraitBruno,
};

extern const Portrait portraitsOrig[];

const Portrait *getPortraitByID(int id)
{
    if(id < sizeof(portraits) / sizeof(portraits[0]) && portraits[id])
        return portraits[id];
    return &portraitsOrig[id];
}

const Portrait *getPortraitByIDInjector(int id)
{
    //return getPortraitByID(id);
    asm("ldr r1,=getPortraitByID\nbx r1");
}

void setPortaritOBJPointerOrig(PortaritProc *proc)
{
    asm(".align 2\n.incbin \"../rom/fe7-jp.gba\",0x6c48,0x6d1c-0x6c48");
}

// default OBJ template for custom portraits
const u16 portraitOBJDefault[] = {
    6,
    OBJ_Y(-16) | ATTR0_WIDE, OBJ_X(32 - 56) | OBJ_SIZE(3), OBJ_CHAR(0),
    OBJ_Y(-16 + 32) | ATTR0_TALL, OBJ_X(16 - 56) | OBJ_SIZE(2), OBJ_CHAR(8),
    OBJ_Y(-16 + 32) | ATTR0_WIDE, OBJ_X(32 - 56) | OBJ_SIZE(3), OBJ_CHAR(10),
    OBJ_Y(-16 + 32 * 2) | ATTR0_SQUARE, OBJ_X(0 - 56) | OBJ_SIZE(2), OBJ_CHAR(18),
    OBJ_Y(-16 + 32 * 2) | ATTR0_WIDE, OBJ_X(32 - 56) | OBJ_SIZE(3), OBJ_CHAR(22),
    OBJ_Y(-16 + 32 * 2) | ATTR0_TALL, OBJ_X(96 - 56) | OBJ_SIZE(2), OBJ_CHAR(30),
    6,
    OBJ_Y(-16) | ATTR0_WIDE, OBJ_X(- (32 - 56) - 64) | OBJ_SIZE(3) | OBJ_HFLIP, OBJ_CHAR(0),
    OBJ_Y(-16 + 32) | ATTR0_TALL, OBJ_X(- (16 - 56) - 16) | OBJ_SIZE(2) | OBJ_HFLIP, OBJ_CHAR(8),
    OBJ_Y(-16 + 32) | ATTR0_WIDE, OBJ_X(- (32 - 56) - 64) | OBJ_SIZE(3) | OBJ_HFLIP, OBJ_CHAR(10),
    OBJ_Y(-16 + 32 * 2) | ATTR0_SQUARE, OBJ_X(- (0 - 56) - 32) | OBJ_SIZE(2) | OBJ_HFLIP, OBJ_CHAR(18),
    OBJ_Y(-16 + 32 * 2) | ATTR0_WIDE, OBJ_X(- (32 - 56) - 64) | OBJ_SIZE(3) | OBJ_HFLIP, OBJ_CHAR(22),
    OBJ_Y(-16 + 32 * 2) | ATTR0_TALL, OBJ_X(- (96 - 56) - 16) | OBJ_SIZE(2) | OBJ_HFLIP, OBJ_CHAR(30),
};

void setPortaritOBJPointer(PortaritProc *proc)
{
    const Portrait *portrait;
    u32 flag;
    const u16 *obj;

    setPortaritOBJPointerOrig(proc);
    portrait = *(const Portrait **)(&proc->data[3]);
    if((u32)portrait >= 0x9000000) // for custom portraits
    {
        flag = *(u32 *)(&proc->data[7]) & 0x807;
        if(flag == 0x800 || flag == 0x801 || flag <= 5)
        {
            obj = portrait->obj;
            if (obj == NULL)
                obj = portraitOBJDefault;
            if(flag & 1)
                *(const u16 **)(&proc->data[15]) = obj + 1 + 3 * *obj; // orientation: left
            else
                *(const u16 **)(&proc->data[15]) = obj; // orientation: right
        }
    }
}

void setPortaritOBJPointerInjector(PortaritProc *proc)
{
    setPortaritOBJPointer(proc);
}

void playMouthAnimationOrig(u32 *p);

void playMouthAnimation(u32 *p)
{
    PortaritProc *proc;
    const Portrait *portrait;

    proc = (PortaritProc *)p[11];
    portrait = *(const Portrait **)(&proc->data[3]);
    if((u32)portrait < 0x9000000) // for original portraits
        playMouthAnimationOrig(p);
}

void (* const pPlayMouthAnimation)(u32 *p) = playMouthAnimation;

void playEyeAnimationOrig(u32 *p, int eyeStatus);

void playEyeAnimation(u32 *p, int eyeStatus)
{
    PortaritProc *proc;
    const Portrait *portrait;

    proc = (PortaritProc *)p[11];
    portrait = *(const Portrait **)(&proc->data[3]);
    if((u32)portrait < 0x9000000) // for original portraits
        playEyeAnimationOrig(p, eyeStatus);
}

void func80045FC(s16*, int);

void blink(s16 *p)
{
    int eyeStatus;

    eyeStatus = 2;
    if(p[26] <= 0xA)
    {
        switch(p[26])
        {
            case 3u:
            case 4u:
            case 5u:
                eyeStatus = 0;
                break;
            case 0u:
            case 1u:
            case 2u:
            case 6u:
            case 7u:
            case 8u:
                eyeStatus = 1;
                break;
            case 0xAu:
                func80045FC(p,0);
                break;
            default:
                break;
        }
    }
    playEyeAnimation(p,eyeStatus);
    ++p[26];
}

void blinkInjector(s16 *p)
{
    blink(p);
}

void func80077E8(s16 *p)
{
    if(p[26] > 5)
    {
        playEyeAnimation(p,0);
        if(!p[25])
            func80045FC(p,1);
    }
    else
        blink(p);
}

void func80077E8Injector(s16 *p)
{
    func80077E8(p);
}

void func8007824(s16 *p)
{
    if(p[26] > 2)
    {
        playEyeAnimation(p,1);
        if(!p[25])
            func80045FC(p,1);
    }
    else
        blink(p);
}

void func8007824Injector(s16 *p)
{
    func8007824(p);
}

void wink(s16 *p)
{
    int eyeStatus;

    eyeStatus = 2;
    if(p[26] <= 0xA)
    {
        switch(p[26])
        {
            case 3u:
            case 4u:
            case 5u:
                eyeStatus = 0;
                break;
            case 0u:
            case 1u:
            case 2u:
            case 6u:
            case 7u:
            case 8u:
                eyeStatus = 1;
                break;
            case 0xAu:
                func80045FC(p,0);
                break;
            default:
                break;
        }
    }
    playEyeAnimation(p,eyeStatus + 0x80);
    ++p[26];
}

void winkInjector(s16 *p)
{
    wink(p);
}

void writeTiles(const u8 *src, u8 *dst);
void writeTSAPlain(u16 *TSABuffer, int BGTileAndPaletteIDBase, int height, int width);
void writeTSA(u16 *TSABuffer, const u16 *TSA, int BGTileAndPaletteIDBase);
void writeBGPalette(const u16 *palette, int start, int length);
int fixHighPortrait(int portraitID);

#define getBGTileAndPaletteIDBaseForTSA(currentBGTileID, currentBGPaletteID) (((currentBGTileID) & 0x3FF) + (((currentBGPaletteID) & 0xF) << 12))
#define isHighPortrait(portraitIDD) (fixHighPortrait(portraitID)<<24)

// TSA for original portraits
extern const u16 portraitTSALowOrig[];
extern const u16 portraitTSAHighOrig[];
// default TSA for custom portraits
const u16 portraitTSADefault[] = {
        0x809,
        20, 21, 22, 23, 24, 25, 26, 27, 28, 29,
        8 + 32 * 3, 9 + 32 * 3, 10 + 32 * 3, 11 + 32 * 3, 12 + 32 * 3, 13 + 32 * 3, 14 + 32 * 3, 15 + 32 * 3, 16 + 32 * 3, 17 + 32 * 3,
        8 + 32 * 2, 9 + 32 * 2, 10 + 32 * 2, 11 + 32 * 2, 12 + 32 * 2, 13 + 32 * 2, 14 + 32 * 2, 15 + 32 * 2, 16 + 32 * 2, 17 + 32 * 2,
        8 + 32, 9 + 32, 10 + 32, 11 + 32, 12 + 32, 13 + 32, 14 + 32, 15 + 32, 16 + 32, 17 + 32,
        8, 9, 10, 11, 12, 13, 14, 15, 16, 17,
        0, 0, 0 + 32 * 3, 1 + 32 * 3, 2 + 32 * 3, 3 + 32 * 3, 4 + 32 * 3, 5 + 32 * 3, 6 + 32 * 3, 7 + 32 * 3,
        0, 0, 0 + 32 * 2, 1 + 32 * 2, 2 + 32 * 2, 3 + 32 * 2, 4 + 32 * 2, 5 + 32 * 2, 6 + 32 * 2, 7 + 32 * 2,
        0, 0, 0 + 32, 1 + 32, 2 + 32, 3 + 32, 4 + 32, 5 + 32, 6 + 32, 7 + 32,
        0, 0, 0, 1, 2, 3, 4, 5, 6, 7,
};
// mask for original portraits
const u16 portraitMaskOrig[] = {
        0,1,1,1,1,1,1,1,1,0,
        0,1,1,1,1,1,1,1,1,0,
        0,1,1,1,1,1,1,1,1,0,
        0,1,1,1,1,1,1,1,1,0,
        0,1,1,1,1,1,1,1,1,0,
        0,1,1,1,1,1,1,1,1,0,
        1,1,1,1,1,1,1,1,1,1,
        1,1,1,1,1,1,1,1,1,1,
        1,1,1,1,1,1,1,1,1,1
};
// default mask for custom portraits
const u16 portraitMaskDefault[] = {
        0,0,1,1,1,1,1,1,1,1,
        0,0,1,1,1,1,1,1,1,1,
        0,0,1,1,1,1,1,1,1,1,
        0,0,1,1,1,1,1,1,1,1,
        1,1,1,1,1,1,1,1,1,1,
        1,1,1,1,1,1,1,1,1,1,
        1,1,1,1,1,1,1,1,1,1,
        1,1,1,1,1,1,1,1,1,1,
        1,1,1,1,1,1,1,1,1,1
};

void drawPortraitInBG(u16 *TSABuffer, int portraitID, int currentBGTileID, int currentBGPaletteID)
{
    const Portrait *portrait;
    int i, j;

    if(portraitID)
    {
        portrait = getPortraitByID(portraitID);
        writeBGPalette(portrait->pal, 32 * currentBGPaletteID, 32);
        if(portrait->card)
        {
            writeTiles(portrait->card, 32 * currentBGTileID + VRAM);
            writeTSAPlain(TSABuffer, getBGTileAndPaletteIDBaseForTSA(currentBGTileID, currentBGPaletteID), 10, 9);
        }
        else
        {
            writeTiles(portrait->tiles, 32 * currentBGTileID + VRAM);
            const u16 *TSA = NULL;
            if((u32)portrait >= 0x9000000)
                TSA = portrait->bg;
            else if (isHighPortrait(portraitID))
                TSA = portraitTSAHighOrig;
            else
                TSA = portraitTSALowOrig;
            if(TSA == NULL)
                TSA = portraitTSADefault;
            writeTSA(TSABuffer, TSA, getBGTileAndPaletteIDBaseForTSA(currentBGTileID, currentBGPaletteID));
            // crop
            const u16 *mask = (u32)portrait >= 0x9000000? portrait->mask: portraitMaskOrig;
            if(mask == NULL)
                mask = portraitMaskDefault;
            if(mask != PORTRAIT_NO_MASK)
                for(i = 0; i < 9; i++)
                    for(j = 0; j < 10; j++)
                        TSABuffer[32 * i + j] &= - mask[10 * i + j];
        }
    }
}

void drawPortraitInBGInjector(u16 *TSABuffer, int portraitID, int currentBGTileID, int currentBGPaletteID)
{
    drawPortraitInBG(TSABuffer, portraitID, currentBGTileID, currentBGPaletteID);
}