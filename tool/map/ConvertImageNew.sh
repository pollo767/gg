#!/bin/bash

for arg in $*
do
  echo "$arg -> Begin"
  echo "$arg --> Decreasing Color"
  output=`$DOTNET exec DecreaseColor/bin/Debug/netcoreapp3.1/DecreaseColor.dll ../../res/map/new_map/$arg tmp/$arg 240 320 0 10`
  echo "$arg --> Decreasing Tile"
  output=`python3 DecreaseTile.py tmp/$arg ../../res/map/new_map/$arg 1023`
  echo "$arg -> Done"
done
