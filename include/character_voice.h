//
// Created by laqieer on 2020/3/24.
//

#ifndef FE7_JP_STUNNING_TRIBBLE_CHARACTER_VOICE_H
#define FE7_JP_STUNNING_TRIBBLE_CHARACTER_VOICE_H

#include <gba_types.h>

#include "character_id.h"
#include "voice.h"
#include "character.h"
#include "proc.h"
#include "text_id.h"
#include "text.h"
#include "gba_debug_print.h"

struct Wave {
    u16 type;
    u16 status;
    u32 frequency;
    u32 loopStart;
    u32 rawSize;
    s8 raw[0];
};

struct Tone {
    u8 type;
    u8 key;
    u8 length;
    u8 panOrSweep;
    const struct Wave *wave;
    u8 attack;
    u8 decay;
    u8 sustain;
    u8 release;
};

struct Song {
    u8 tracks;
    u8 blocks;
    u8 priority;
    u8 reverb;
    const struct Tone *tone;
    u8 *track[0];
};

struct CharacterVoice {
    const struct Song *map[3];
    const struct Song *damage[2];
    const struct Song *dead;
};

extern struct Unit *currentActiveUnit;
extern u32 currentGameClock;

extern u8 DAT_0203a50c;
extern u8 DAT_0203a50d;
extern u8 DAT_0203a50e;

// Random Number range: [0, n)
#define GetTrueRN(n) (currentGameClock % n)

void DisplayActiveUnitEffectRange();
void MPlayStart(void *player, const struct Song *song); // omit player info struct define, use void* instead
int getActiveUnitCurrentHp();
void HandleActiveUnitDeath(struct Proc *proc);

#define MUSIC_PLAYER_8 0x3005d10 // omit lookup table at 0x86ea8b8 & entry struct define
#define MUSIC_PLAYER_VOICE MUSIC_PLAYER_8

#define DEFINE_CHARACTER_MAP_VOICE(name) {&VOICE_##name##_MAP_1, &VOICE_##name##_MAP_2, &VOICE_##name##_MAP_3}
#define DEFINE_CHARACTER_DAMAGE_VOICE(name) {&VOICE_##name##_DAMAGE_1, &VOICE_##name##_DAMAGE_2}
#define DEFINE_CHARACTER_DEAD_VOICE(name) &VOICE_##name##_DEAD_1
#define DEFINE_CHARACTER_VOICE(name) [CHARACTER_##name##_ID] = {DEFINE_CHARACTER_MAP_VOICE(name), DEFINE_CHARACTER_DAMAGE_VOICE(name), DEFINE_CHARACTER_DEAD_VOICE(name)},

#endif //FE7_JP_STUNNING_TRIBBLE_CHARACTER_VOICE_H