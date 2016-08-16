#!/bin/bash

clear
rm -rf src/*.o 
rm -rf src/program/*.o
rm -rf src/program/gui/*.o
rm -rf src/program/observer/*.o
rm -rf src/program/messages/*.o
rm -rf src/program/path_finder/*.o
rm -rf src/program/game/*.o
rm -rf src/program/game/ui/*.o
rm -rf src/program/game/level/*.o
rm -rf src/program/game/fov/*.o
rm -rf src/program/game/entity/*.o
rm -rf src/program/game/entity/item/*.o
rm -rf src/program/game/entity/npc/*.o
make -j 4

exit 0
