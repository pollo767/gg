#!/bin/bash

mkdir tmp
cd tmp
for arg in $*
do
    echo "Exporting $arg ..."
    output=`../RearrangeTiles.py ../../../res/map/new_map/$arg.png $arg.png`
    grit $arg.png -gB4 -mR4 -pn160 -ftb
    cat $arg.map.bin $arg.terrain.bin > $arg.cfg.bin
    gbalzss e $arg.cfg.bin $arg.cfg
    grit $arg.png -gB4 -mR4 -pn160 -gzl
    sed '/Map/,/align/d' $arg.s > ../../../src/res/map/map/$arg.s
    bin2s $arg.cfg >> ../../../src/res/map/map/$arg.s
done
cd ..
