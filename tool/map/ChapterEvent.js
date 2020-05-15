var ChapterEvent = {
    name: "Fire Emblem (GBA) chapter event",
    extension: "S",

    write: function(map, fileName) {
        var file = new TextFile(fileName, TextFile.WriteOnly);

        file.writeLine("//Exported by Tiled extension: ChapterEvent.js");

        file.writeLine("\t#include \"event.h\"")
        file.writeLine("\t.section .rodata");
        file.writeLine("\t.align 2");

        var label = fileName.substring(fileName.lastIndexOf("\\")+1).substring(fileName.lastIndexOf("/")+1).split(".")[0];

        file.writeLine("\t.global " + label);
        file.writeLine(label + ":");

        var chapterId = parseInt(fileName.split("_").pop().split(".")[0]);

        // chapter event pointer array
        file.writeLine("\t.word TurnBasedEvents");
        file.writeLine("\t.word CharacterBasedEvents");
        file.writeLine("\t.word LocationBasedEvents");
        file.writeLine("\t.word MiscBasedEvents");
        file.writeLine("\t.word TrapsEliwoodMode");
        file.writeLine("\t.word TrapsHectorMode");
        file.writeLine("\t.word EnemyUnitsENM");
        file.writeLine("\t.word EnemyUnitsENM");
        file.writeLine("\t.word EnemyUnitsENM");
        file.writeLine("\t.word EnemyUnitsENM");
        file.writeLine("\t.word AllyUnitsENM");
        file.writeLine("\t.word AllyUnitsENM");
        file.writeLine("\t.word AllyUnitsENM");
        file.writeLine("\t.word AllyUnitsENM");
        file.writeLine("\t.word BeginningScene");
        file.writeLine("\t.word EndingScene");

        // Turn Events
        file.writeLine("TurnBasedEvents:");
        file.writeLine("\tLoadBeginningScene");
        file.writeLine("\tEND_MAIN");

        // Character Events
        file.writeLine("CharacterBasedEvents:");
        file.writeLine("\tEND_MAIN");

        // Location Events
        file.writeLine("LocationBasedEvents:");
        file.writeLine("\tEND_MAIN");

        // Misc Events
        file.writeLine("MiscBasedEvents:");
        file.writeLine("\tCauseGameOverIfLordDies"); // Game Over
        file.writeLine("\tDefeatAll(EndingScene)"); // Chapter Clear
        file.writeLine("\tEND_MAIN");

        // Beginning Scene
        file.writeLine("BeginningScene:");
        file.writeLine("\tClearSpecialSkillCD");
        file.writeLine("\tLOU1 EnemyUnitsENM");
        file.writeLine("\tENUN");
        file.writeLine("\tLOU1 AllyUnitsENM");
        file.writeLine("\tENUN");
        file.writeLine("\tUpdateSpecialSkillCD");
        if(map.property("hasScene") === true) {
            file.writeLine("\tMUSC MUSIC_FE_H_SERIOUS_6"); // dialogue bgm
            file.writeLine("\tTEX1 TEXT_CHAP_" + chapterId + "_OP"); // dialogue text
        }
        file.writeLine("\tENDA");

        // Ending Scene
        file.writeLine("EndingScene:");
        file.writeLine("\tClearSpecialSkillCD");
        if(map.property("hasScene") === true) {
            file.writeLine("\tMUSC MUSIC_FE_H_EVENT_1"); // dialogue bgm
            file.writeLine("\tTEX1 TEXT_CHAP_" + chapterId + "_ED"); // dialogue text
        }
        var nextChapterId = chapterId + 1;
        file.writeLine("\tMNCH " + nextChapterId);
        file.writeLine("\tENDA");

        // Player Units
        file.writeLine("AllyUnitsENM:");
        for (var i = 0; i < map.layerCount; ++i) {
            var layer = map.layerAt(i);
            if(layer.name == "Player") {
                if (layer.isObjectLayer) {
                    for (const object of layer.objects) {
                        var x = parseInt(object.x / 16);
                        var y = parseInt(object.y / 16) - 1;
                        var character = object.name;
                        var leader = "Anna";
                        if(character == leader) {
                            leader = "0";
                        }
                        var job = object.tile.imageFileName;
                        job = job.substring(job.lastIndexOf("\\")+1).substring(job.lastIndexOf("/")+1).split(".")[0];
                        var playerUnit = new Array("\tUNIT_ALLY_JOINED(" + character, job, leader, x, y, x, y + ")");
                        file.writeLine(playerUnit.join(","));
                    }
                } else {
                    tiled.error("\tPlayer is not object layer.");
                }
            }
        }
        file.writeLine("\tEND_UNIT");

        // Enemy Units
        file.writeLine("EnemyUnitsENM:");
        for (var i = 0; i < map.layerCount; ++i) {
            var layer = map.layerAt(i);
            if(layer.name == "Enemy") {
                if (layer.isObjectLayer) {
                    for (const object of layer.objects) {
                        var x = parseInt(object.x / 16);
                        var y = parseInt(object.y / 16) - 1;
                        var comment = object.name;
                        var character = object.property("Character");
                        var leader = 0;
                        var job = object.tile.imageFileName;
                        job = job.substring(job.lastIndexOf("\\")+1).substring(job.lastIndexOf("/")+1).split(".")[0];
                        var level = object.property("Level");
                        var autoLevel = object.property("AutoLevel");
                        var equip = object.property("Equip");
                        var item = object.property("Item");
                        var AI1 = object.property("AI1");
                        var AI2 = object.property("AI2");
                        var AI3 = object.property("AI3");
                        var AI4 = object.property("AI4");
                        var enemyUnit = new Array("\tUNIT(" + character, job, leader, level, "SIDE_ENEMY", autoLevel, x, y, x, y, equip, item, 0, 0, AI1, AI2, AI3, AI4 + ") // " + comment);
                        file.writeLine(enemyUnit.join(","));
                    }
                } else {
                    tiled.error("Enemy is not object layer.");
                }
            }
        }
        file.writeLine("\tEND_UNIT");

        // traps
        file.writeLine("TrapsEliwoodMode:");
        file.writeLine("TrapsHectorMode:");
        file.writeLine("END_TRAP");

        // Map Changes
        for (var i = 0; i < map.layerCount; ++i) {
            var layer = map.layerAt(i);
            if(layer.name == "MapChanges" && layer.isGroupLayer) {
                file.writeLine("\t.section .rodata");
                file.writeLine("\t.align 2");
                var symbol = "map_change_chap_" + chapterId;
                file.writeLine("\t.global " + symbol);
                file.writeLine(symbol + ":");
                for (var j = 0; j < layer.layerCount; ++j) {
                    var subLayer = layer.layerAt(j);
                    var bound = subLayer.region().boundingRect;
                    var mapChange = new Array(j, bound.x, bound.y, bound.width, bound.height, 0, 0, 0);
                    file.writeLine("\t.byte " + mapChange.join(","));
                    file.writeLine("\t.word mapChange" + j);
                }
                file.writeLine("\t.word -1, 0, 0");
                for (var j = 0; j < layer.layerCount; ++j) {
                    var subLayer = layer.layerAt(j);
                    var bound = subLayer.region().boundingRect;
                    file.writeLine("\t.align 2");
                    file.writeLine("mapChange" + j + ":");
                    file.write("\t.hword ");
                    for (y = bound.y; y < bound.y + bound.height; ++y) {
                        for (x = bound.x; x < bound.x + bound.width; ++x) {
                            file.write(String(4 * ((subLayer.cellAt(x, y).tileId + 1) & 1023)));
                            file.write(",");
                        }
                    }
                    file.writeLine("");
                }
            }
        }

        file.commit();
    },
}

tiled.registerMapFormat("Fire Emblem (GBA) Event", ChapterEvent)