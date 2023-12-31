//
// Created by laqieer on 2020/2/15.
//

#ifndef FE7_JP_STUNNING_TRIBBLE_MAP_SPRITE_H
#define FE7_JP_STUNNING_TRIBBLE_MAP_SPRITE_H

struct StandingSprite {
    short pattern; // unknown, seems to be useless
    short size; // icon size
    char *sheet; // animation sheet
};

struct MovingSprite {
    char *sheet; // animation sheet
    char *motion; // frames and scripts for different modes
};

enum {
    MAP_SPRITE_SIZE_SMALL = 0, // 16 x 16
    MAP_SPRITE_SIZE_TALL, // 16 x 32
    MAP_SPRITE_SIZE_BIG, // 32 x 32
};

#endif //FE7_JP_STUNNING_TRIBBLE_MAP_SPRITE_H
