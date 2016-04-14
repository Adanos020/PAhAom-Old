#include "program.hpp"

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdio>
#include <string>

extern rr::Settings settings;

namespace rr {

    bool Dictionary::load() {
        std::ifstream idict;
        idict.open("data/lang/"+settings.game.language+".lang");

        if (idict.good()) {
            puts(">Loading the dictionary...");
            std::cout << "=====WORD======" << std::setw(40) << "===TRANSLATION===\n";
            while (!idict.eof()) {
                std::string word;
                std::string translation;

                idict >> word;
                if (word[0] == ';' || word == "")
                    std::getline(idict, word);
                else {
                    idict.seekg(idict.tellg()+1l);
                    std::getline(idict, translation);

                    if      (word == "gui.button.newgame")   gui.button.newgame   = utf8ToUtf32(translation);
                    else if (word == "gui.button.resume")    gui.button.resume    = utf8ToUtf32(translation);
                    else if (word == "gui.button.save")      gui.button.save      = utf8ToUtf32(translation);
                    else if (word == "gui.button.load")      gui.button.load      = utf8ToUtf32(translation);
                    else if (word == "gui.button.options")   gui.button.options   = utf8ToUtf32(translation);
                    else if (word == "gui.button.help")      gui.button.help      = utf8ToUtf32(translation);
                    else if (word == "gui.button.credits")   gui.button.credits   = utf8ToUtf32(translation);
                    else if (word == "gui.button.quit")      gui.button.quit      = utf8ToUtf32(translation);
                    else if (word == "gui.button.game")      gui.button.game      = utf8ToUtf32(translation);
                    else if (word == "gui.button.graphical") gui.button.graphical = utf8ToUtf32(translation);
                    else if (word == "gui.button.sound")     gui.button.sound     = utf8ToUtf32(translation);
                    else if (word == "gui.button.controls")  gui.button.controls  = utf8ToUtf32(translation);

                    else if (word == "gui.checkbox.fullscreen") gui.checkbox.fullscreen = utf8ToUtf32(translation);
                    else if (word == "gui.checkbox.vsync")      gui.checkbox.vsync      = utf8ToUtf32(translation);

                    else if (word == "gui.text.resolution")   gui.text.resolution   = utf8ToUtf32(translation);
                    else if (word == "gui.text.language")     gui.text.language     = utf8ToUtf32(translation);
                    else if (word == "gui.text.killurslf")    gui.text.killurslf    = utf8ToUtf32(translation);
                    else if (word == "gui.text.wholegame")    gui.text.wholegame    = utf8ToUtf32(translation);
                    else if (word == "gui.text.usedlib")      gui.text.usedlib      = utf8ToUtf32(translation);
                    else if (word == "gui.text.music")        gui.text.music        = utf8ToUtf32(translation);
                    else if (word == "gui.text.effects")      gui.text.effects      = utf8ToUtf32(translation);
                    else if (word == "gui.text.mute")         gui.text.mute         = utf8ToUtf32(translation);

                    else if (word == "gui.window.attributes") gui.window.attributes = utf8ToUtf32(translation);
                    else if (word == "gui.window.inventory")  gui.window.inventory  = utf8ToUtf32(translation);


                    else if (word == "item.potion")  item.potion.potion = utf8ToUtf32(translation);

                    else if (word == "item.potion.size.small")  item.potion.size.small  = utf8ToUtf32(translation);
                    else if (word == "item.potion.size.medium") item.potion.size.medium = utf8ToUtf32(translation);
                    else if (word == "item.potion.size.big")    item.potion.size.big    = utf8ToUtf32(translation);

                    else if (word == "item.potion.effect.healing")      item.potion.effect.healing      = utf8ToUtf32(translation);
                    else if (word == "item.potion.effect.magic")        item.potion.effect.magic        = utf8ToUtf32(translation);
                    else if (word == "item.potion.effect.strength")     item.potion.effect.strength     = utf8ToUtf32(translation);
                    else if (word == "item.potion.effect.dexterity")    item.potion.effect.dexterity    = utf8ToUtf32(translation);
                    else if (word == "item.potion.effect.speed")        item.potion.effect.speed        = utf8ToUtf32(translation);
                    else if (word == "item.potion.effect.poison")       item.potion.effect.poison       = utf8ToUtf32(translation);
                    else if (word == "item.potion.effect.regeneration") item.potion.effect.regeneration = utf8ToUtf32(translation);
                    else if (word == "item.potion.effect.slowness")     item.potion.effect.slowness     = utf8ToUtf32(translation);
                    else if (word == "item.potion.effect.weakness")     item.potion.effect.weakness     = utf8ToUtf32(translation);

                    else if (word == "item.potion.color.red")    item.potion.color.red    = utf8ToUtf32(translation);
                    else if (word == "item.potion.color.blue")   item.potion.color.blue   = utf8ToUtf32(translation);
                    else if (word == "item.potion.color.brown")  item.potion.color.brown  = utf8ToUtf32(translation);
                    else if (word == "item.potion.color.green")  item.potion.color.green  = utf8ToUtf32(translation);
                    else if (word == "item.potion.color.gray")   item.potion.color.gray   = utf8ToUtf32(translation);
                    else if (word == "item.potion.color.pink")   item.potion.color.pink   = utf8ToUtf32(translation);
                    else if (word == "item.potion.color.purple") item.potion.color.purple = utf8ToUtf32(translation);
                    else if (word == "item.potion.color.black")  item.potion.color.black  = utf8ToUtf32(translation);
                    else if (word == "item.potion.color.white")  item.potion.color.white  = utf8ToUtf32(translation);

                    else if (word == "player.attributes.health")       player.attributes.health       = utf8ToUtf32(translation);
                    else if (word == "player.attributes.strength")     player.attributes.strength     = utf8ToUtf32(translation);
                    else if (word == "player.attributes.dexterity")    player.attributes.dexterity    = utf8ToUtf32(translation);
                    else if (word == "player.attributes.experience")   player.attributes.experience   = utf8ToUtf32(translation);
                    else if (word == "player.attributes.level")        player.attributes.level        = utf8ToUtf32(translation);
                    else if (word == "player.attributes.skill_points") player.attributes.skill_points = utf8ToUtf32(translation);

                    else if (word == "player.skills.crafting")              player.skills.crafting              = utf8ToUtf32(translation);
                    else if (word == "player.skills.alchemy")               player.skills.alchemy               = utf8ToUtf32(translation);
                    else if (word == "player.skills.cold_weapon_mastery")   player.skills.cold_weapon_mastery   = utf8ToUtf32(translation);
                    else if (word == "player.skills.ranged_weapon_mastery") player.skills.ranged_weapon_mastery = utf8ToUtf32(translation);
                    else if (word == "player.skills.better_sight")          player.skills.better_sight          = utf8ToUtf32(translation);

                    std::cout << word << std::setw(38-word.size()+translation.size()) << translation + "\n";
                }
            }
            idict.close();
            puts(">Done.");
            return true;
        }
        puts("!Error loading the dictionary!");
        return false;
    }

}
