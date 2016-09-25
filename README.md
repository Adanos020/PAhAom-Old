# README #

To compile this code you need to use SFML:
http://www.sfml-dev.org/index.php

# Storyline #
Some nameless lumberjack gets captured by bandits during his another day of work. He's being led by them to their boss who happens to be a rich owner of an underground palace. He tells his rogues to lead our hero to the dungeon in the bottom of the complex. As it seems, the bandits are not very smart and they forget to lock the door to the jail. After they leave the room, our hero gets out of the jail and finds a dagger. a piece of baguette and a healing potion on the floor, with which he goes to the next floor. He decides to have a revenge on the bandits' boss living on the top of his underground palace. In order to prepare for the combat he explores the next floors of the residence.

# Used technologies #
- Programming language: C++ (C++14 standard)
- Multimedia library: SFML
- Compiler: GNU GCC
- Code editor: Visual Studio Code for Linux
- Graphics: Gimp 2.8

# What is already done #
- Procedural dungeon generation
- Auto-sorting inventory
- Identifying the items by using them
- For the potions there are randomized colors which change every time you start a new game; for the runes it is the same except for that there are randomized symbols for them
- Auto-save and loading the game
- Settings for graphics, controls and changing the language (three languages are available - polish, english and my own constructed language :D)
- Food sets the player's hunger level to zero if the hero is only slightly hunger but if he is starving, then it just decreases it
- Obtaining special skills by reading books which eventually will be available only in shops for ridiculous prices
- Drinking potions influences the attributes of the player (health, mana, strength, dexterity) or elongates the duration of the buffs (speed, accelerated health regeneration, poison, slowness, weakness)
- Map view
- HUD, attributes window, inventory window, main menu, pause menu
- Player's field of vision which is limited by walls, doors and darkness
- Game logs in a form similar to the chat in Minecraft
- Written by me fully functional GUI API.

# What is left to do #
- Combat system
- Obtaining special skills and augmenting the player's attributes by spending skill points (and gold) at the teachers'
- Changing look of the levels and enemies appearing on them after each boss fight
- Boss fights appearing every 5 levels
- Audio
- Actual buff effects
- Turn system
- Conversation system
- Trading system
- Casting spells from disposable runic stones and the possibility of writing them down in the Book of Spells (which must be bought in the store of course)
- Optimal path finding for the NPCs and the Player (the A* algorithm is implemented already, yet is not used anywhere at the moment)
- Book of Spells window
- Background in the main menu xD
- A small system of side-quests.