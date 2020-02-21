//
// Created by laqieer on 2020/2/2.
//

#include <gba_types.h>

extern u8 chapter_title_pre[];
extern u8 chapter_title_1[];
extern u8 chapter_title_2[];
extern u8 chapter_title_3[];
extern u8 chapter_title_4_lz[];

const u8 * chapterTitles[] = {
        chapter_title_pre,
        chapter_title_1,
        chapter_title_2,
        chapter_title_3,
        chapter_title_4_lz,
        0x840a280,
        0x840a634,
        0x840a9b0,
        0x840ad04,
        0x840b084,
        0x840b3d8,
        0x840b748,
        0x840bb4c,
        0x840bebc,
        0x840c230,
        0x840c61c,
        0x840ca8c,
        0x840ce98,
        0x840d290,
        0x840d5f0,
        0x840da24,
        0x840dd5c,
        0x840e050,
        0x840e4e0,
        0x840e7b8,
        0x840ec00,
        0x840ef0c,
        0x840f2e4,
        0x840f768,
        0x840fb00,
        0x840fe98,
        0x8410384,
        0x841071c,
        0x8410ab4,
        0x8410f38,
        0x84113a8,
        0x8411770,
        0x8411ae8,
        0x8411ee8,
        0x841230c,
        0x84126b8,
        0x8412928,
        0x8412d04,
        0x841305c,
        0x8413448,
        0x84138b8,
        0x8413cc4,
        0x84140e4,
        0x84144f0,
        0x841485c,
        0x8414c74,
        0x8414fa8,
        0x84152a4,
        0x841571c,
        0x8415b20,
        0x8415df4,
        0x841621c,
        0x841653c,
        0x841691c,
        0x8416d8c,
        0x8417104,
        0x841747c,
        0x84177f4,
        0x8417ce0,
        0x841805C,
        0x84183d8,
        0x8418860,
        0x8418cdc,
        0x8419094,
        0x84194a4,
        0x8419890,
        0x8419c8c,
        0x841a038,
        0x841a454,
        0x841a6c4,
        0x841A964,
        0x841AB8C
};

const u8 ** const pChapterTitles = chapterTitles;