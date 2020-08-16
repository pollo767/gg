	.section .rodata
	#include "event.h"
	.align 2
	.global event_chap_6
event_chap_6:
PointerList:
	.word TurnBasedEvents
	.word CharacterBasedEvents
	.word LocationBasedEvents
	.word MiscBasedEvents
	.word TrapsEliwoodMode
	.word TrapsHectorMode
	.word EnemyUnitsENM
	.word EnemyUnitsENM
	.word EnemyUnitsENM
	.word EnemyUnitsENM
	.word AllyUnitsENM
	.word AllyUnitsENM
	.word AllyUnitsENM
	.word AllyUnitsENM
	.word BeginningScene
	.word EndingScene
TurnBasedEvents:
	.byte 0x02, 0x00, 0x00, 0x00
	.word BeginningScene
	.byte 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00
CharacterBasedEvents:
	.byte 0x00, 0x00, 0x00, 0x00
LocationBasedEvents:
	.byte 0x00, 0x00, 0x00, 0x00
MiscBasedEvents:
	.byte 0x01, 0x00, 0x00, 0x00, 0x1C, 0xF7, 0xD6, 0x08, 0x65, 0x00, 0x00, 0x00
	.byte 0x0E, 0x00, 0x00, 0x00
	.word EndingScene
	.byte 0x5D, 0xAA, 0x07, 0x08
	.byte 0x00, 0x00, 0x00, 0x00
BeginningScene:
    .word 0x3C, initSkillCDForAllUnits
	.byte 0x30, 0x00, 0x00, 0x00
	.word AllyUnitsENM
	.byte 0x39, 0x00, 0x00, 0x00
	.byte 0x30, 0x00, 0x00, 0x00
	.word EnemyUnitsENM
	.byte 0x39, 0x00, 0x00, 0x00
    .word 0x3C, updateSkillCDForAllUnits
	.byte 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
EndingScene:
	.byte 0x7F, 0x00, 0x07, 0x00 // go to next chapter
	.byte 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
AllyUnitsENM:
	.byte 0x01, 0x01, 0x02, 0x08, 13, 19, 13, 19, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x03, 0x02, 0x02, 0x08, 12, 19, 12, 19, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x02, 0x03, 0x00, 0x08, 14, 19, 14, 19, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
EnemyUnitsENM:
	.byte 0x73, 0x28, 0x00, 0x2D, 0, 5, 0, 5, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 // カイン
	.byte 0x73, 0x28, 0x00, 0x2D, 10, 0, 10, 0, 0x14, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 // アベル
	.byte 0x73, 0x18, 0x00, 0x2D, 0, 8, 0, 8, 0x2C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 // ゴードン
	.byte 0x68, 0x32, 0x00, 0x2D, 14, 6, 14, 6, 0x14, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 // 天馬
	.byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
TrapsEliwoodMode:
	.byte 0x00
TrapsHectorMode:
	.byte 0x00
