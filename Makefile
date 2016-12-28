#    ==========================================================
#     PAhAom makefile by Artem G (2016)
#    =========================================================
#     It's a universal makefile for Windows and Unix systems.
#    =========================================================

#Global definitions
INC = 
CFLAGS = -Wall -Wextra -std=c++14 -DSFML_STATIC
RESINC = 
LIBDIR = 
LDFLAGS = -static-libgcc -static-libstdc++

INC_DEBUG = $(INC)
CFLAGS_DEBUG = $(CFLAGS) -g
RESINC_DEBUG = $(RESINC)
RCFLAGS_DEBUG = $(RCFLAGS)
LIBDIR_DEBUG = $(LIBDIR)
LIB_DEBUG = $(LIB)

LDFLAGS_DEBUG = $(LDFLAGS)

INC_RELEASE = $(INC)
CFLAGS_RELEASE = $(CFLAGS) -O2
RESINC_RELEASE = $(RESINC)
RCFLAGS_RELEASE = $(RCFLAGS)
LIBDIR_RELEASE = $(LIBDIR)
LIB_RELEASE = $(LIB)
LDFLAGS_RELEASE = $(LDFLAGS) -s

#OS-like definitions
ifeq ($(OS),Windows_NT)
	WORKDIR = $(shell cd)
	CC = gcc
	CXX = g++
	AR = ar
	LD = g++
	WINDRES = windres
	INC +=
	CFLAGS +=
	RESINC +=
	LIBDIR +=
	LIB =\
-lsfml-audio-s -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lsfml-main \
-lopengl32 -lfreetype -ljpeg -lwinmm -lgdi32 -lopenal32 -lflac -lvorbisenc -lvorbisfile -lvorbis -logg
	LDFLAGS +=
	INC_DEBUG +=
	CFLAGS_DEBUG +=
	RESINC_DEBUG +=
	RCFLAGS_DEBUG +=
	LIBDIR_DEBUG +=
	LIB_DEBUG +=
	LDFLAGS_DEBUG +=
	DEP_DEBUG +=
	OUT_DEBUG = bin/Debug/pahaom.exe
	INC_RELEASE +=
	CFLAGS_RELEASE +=
	RESINC_RELEASE +=
	RCFLAGS_RELEASE +=
	LIBDIR_RELEASE +=
	LIB_RELEASE +=
	LDFLAGS_RELEASE +=
	OUT_RELEASE = bin/Release/pahaom.exe
else
	WORKDIR = $(shell pwd)
	CC = gcc
	CXX = clang++
	AR = ar
	LD = clang++
	WINDRES = windres
	INC += 
	CFLAGS += 
	RESINC += 
	LIBDIR += 
	LIB +=\
-lsfml-audio -lsfml-graphics -lsfml-window -lsfml-system
	LDFLAGS += 
	INC_DEBUG +=  
	CFLAGS_DEBUG +=  
	RESINC_DEBUG +=  
	RCFLAGS_DEBUG +=  
	LIBDIR_DEBUG += 
	LIB_DEBUG +=  
	LDFLAGS_DEBUG +=  
	DEP_DEBUG +=  
	OUT_DEBUG = bin/Debug/pahaom
	INC_RELEASE +=  
	CFLAGS_RELEASE +=  
	RESINC_RELEASE +=  
	RCFLAGS_RELEASE +=  
	LIBDIR_RELEASE += 
	LIB_RELEASE +=  
	LDFLAGS_RELEASE +=  
	OUT_RELEASE = bin/Release/pahaom
endif

#Objects list
OBJ_DEBUG =\
lib/AnimatedSprite.debug.o \
lib/Animation.debug.o \
src/main.debug.o \
src/program/AudioManager.debug.o \
src/program/Settings.debug.o \
src/program/Resources.debug.o \
src/program/Program.debug.o \
src/program/Observer.debug.o \
src/program/gui/Window.debug.o \
src/program/gui/Text.debug.o \
src/program/gui/Switch.debug.o \
src/program/gui/Slot.debug.o \
src/program/gui/Separator.debug.o \
src/program/gui/ScrollBar.debug.o \
src/program/gui/Menu.debug.o \
src/program/gui/Image.debug.o \
src/program/gui/Checkbox.debug.o \
src/program/gui/Button.debug.o \
src/program/gui/Bar.debug.o \
src/program/game/Game.debug.o \
src/program/game/Level.debug.o \
src/program/game/FOV.debug.o \
src/program/game/ShadowMap.debug.o \
src/program/game/Dialogue.debug.o \
src/program/game/path_finder/PathFinder.debug.o \
src/program/game/path_finder/PathFinder_Node.debug.o \
src/program/game/messages/MessageManager.debug.o \
src/program/game/messages/Message.debug.o \
src/program/game/hitmarkers/HitMarker.debug.o \
src/program/game/hitmarkers/HitMarkerManager.debug.o \
src/program/game/ui/PauseMenu.debug.o \
src/program/game/ui/MainMenu.debug.o \
src/program/game/ui/Journal.debug.o \
src/program/game/ui/Inventory.debug.o \
src/program/game/ui/BookOfSpells.debug.o \
src/program/game/ui/DeathScreen.debug.o \
src/program/game/ui/Conversation.debug.o \
src/program/game/ui/Attributes.debug.o \
src/program/game/ui/HUD.debug.o \
src/program/game/entity/Door.debug.o \
src/program/game/entity/Chest.debug.o \
src/program/game/entity/Stairs.debug.o \
src/program/game/entity/player/Player.debug.o \
src/program/game/entity/player/state/PlayerStanding.debug.o \
src/program/game/entity/player/state/PlayerMoving.debug.o \
src/program/game/entity/player/state/PlayerAttacking.debug.o \
src/program/game/entity/npc/NPC.debug.o \
src/program/game/entity/npc/Bandit.debug.o \
src/program/game/entity/npc/Teacher.debug.o \
src/program/game/entity/npc/state/NPCAttacking.debug.o \
src/program/game/entity/npc/state/NPCHunting.debug.o \
src/program/game/entity/npc/state/NPCMoving.debug.o \
src/program/game/entity/npc/state/NPCSleeping.debug.o \
src/program/game/entity/item/Rune.debug.o \
src/program/game/entity/item/Ring.debug.o \
src/program/game/entity/item/Potion.debug.o \
src/program/game/entity/item/Food.debug.o \
src/program/game/entity/item/MeleeWeapon.debug.o \
src/program/game/entity/item/RangedWeapon.debug.o \
src/program/game/entity/item/Coin.debug.o \
src/program/game/entity/item/Book.debug.o \
src/program/game/entity/item/Ammunition.debug.o

OBJ_RELEASE =\
lib/AnimatedSprite.o \
lib/Animation.o \
src/main.o \
src/program/AudioManager.o \
src/program/Settings.o \
src/program/Resources.o \
src/program/Program.o \
src/program/Observer.o \
src/program/gui/Window.o \
src/program/gui/Text.o \
src/program/gui/Switch.o \
src/program/gui/Slot.o \
src/program/gui/Separator.o \
src/program/gui/ScrollBar.o \
src/program/gui/Menu.o \
src/program/gui/Image.o \
src/program/gui/Checkbox.o \
src/program/gui/Button.o \
src/program/gui/Bar.o \
src/program/game/Game.o \
src/program/game/Level.o \
src/program/game/FOV.o \
src/program/game/ShadowMap.o \
src/program/game/Dialogue.o \
src/program/game/path_finder/PathFinder.o \
src/program/game/path_finder/PathFinder_Node.o \
src/program/game/messages/MessageManager.o \
src/program/game/messages/Message.o \
src/program/game/hitmarkers/HitMarker.o \
src/program/game/hitmarkers/HitMarkerManager.o \
src/program/game/ui/PauseMenu.o \
src/program/game/ui/MainMenu.o \
src/program/game/ui/Journal.o \
src/program/game/ui/Inventory.o \
src/program/game/ui/BookOfSpells.o \
src/program/game/ui/DeathScreen.o \
src/program/game/ui/Conversation.o \
src/program/game/ui/Attributes.o \
src/program/game/ui/HUD.o \
src/program/game/entity/Door.o \
src/program/game/entity/Chest.o \
src/program/game/entity/Stairs.o \
src/program/game/entity/player/Player.o \
src/program/game/entity/player/state/PlayerStanding.o \
src/program/game/entity/player/state/PlayerMoving.o \
src/program/game/entity/player/state/PlayerAttacking.o \
src/program/game/entity/npc/NPC.o \
src/program/game/entity/npc/Bandit.o \
src/program/game/entity/npc/Teacher.o \
src/program/game/entity/npc/state/NPCAttacking.o \
src/program/game/entity/npc/state/NPCHunting.o \
src/program/game/entity/npc/state/NPCMoving.o \
src/program/game/entity/npc/state/NPCSleeping.o \
src/program/game/entity/item/Rune.o \
src/program/game/entity/item/Ring.o \
src/program/game/entity/item/Potion.o \
src/program/game/entity/item/Food.o \
src/program/game/entity/item/MeleeWeapon.o \
src/program/game/entity/item/RangedWeapon.o \
src/program/game/entity/item/Coin.o \
src/program/game/entity/item/Book.o \
src/program/game/entity/item/Ammunition.o

all: debug release

clean:
ifeq ($(OS),Windows_NT)
	@del /s /q *.o
	@rd /s /q bin
else
	rm -rf *.o */*.o */*/*.o */*/*/*.o */*/*/*/*.o */*/*/*/*/*.o  */*/*/*/*/*/*.o */*/*/*/*/*/*/*.o
	rm -rf bin/Debug/*
	rm -rf bin/Release/*
endif

.PHONY: all clean debug release

# ======= Debug ================================

debug: debug_before debug_link debug_after

debug_before: 
ifeq ($(OS),Windows_NT)
	-mkdir bin\Debug
	-mkdir obj
else

endif

debug_link: $(OBJ_DEBUG)
	$(LD) $(LIBDIR_DEBUG) -o $(OUT_DEBUG) $(OBJ_DEBUG) $(LDFLAGS_DEBUG) $(LIB_DEBUG)

debug_after:

%.debug.o: %.cpp
	$(CXX) $(CFLAGS_DEBUG) $(INC_DEBUG) -c $< -o $@

# ======= Release ==============================

release: release_before release_link release_after

release_before: 
ifeq ($(OS),Windows_NT)
	-mkdir bin\Release
else
	
endif
	
release_link: $(OBJ_RELEASE)
	$(LD) $(LIBDIR_RELEASE) -o $(OUT_RELEASE) $(OBJ_RELEASE) $(LDFLAGS_RELEASE) $(LIB_RELEASE)

release_after:
	
%.o: %.cpp
	$(CXX) $(CFLAGS_RELEASE) $(INC_RELEASE) -c $< -o $@
	