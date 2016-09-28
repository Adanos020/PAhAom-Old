#!/bin/bash

clear
rm -rf src/*.o 
rm -rf src/program/*.o
rm -rf src/program/gui/*.o
rm -rf src/program/game/*.o
rm -rf src/program/game/ui/*.o
rm -rf src/program/game/messages/*.o
rm -rf src/program/game/path_finder/*.o
rm -rf src/program/game/entity/*.o
rm -rf src/program/game/entity/item/*.o
rm -rf src/program/game/entity/npc/*.o
rm -rf src/program/game/entity/npc/ai/*.o
rm -rf src/program/game/entity/player/*.o
rm -rf src/program/game/entity/player/state/*.o
mingw32-make -j 4

exit 0
