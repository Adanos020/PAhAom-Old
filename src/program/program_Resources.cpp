#include "program.hpp"

namespace rr {

    bool Resources::load() {
        return (font   .Unifont .loadFromFile("data/font/unifont-8.0.01.ttf")
             && font   .Pixel   .loadFromFile("data/font/I-pixel-u-mod.ttf")
             && texture.gui     .loadFromFile("data/graphics/gui.png")
             && texture.player  .loadFromFile("data/graphics/player.png")
             && texture.items   .loadFromFile("data/graphics/items.png")
             && texture.tileset .loadFromFile("data/graphics/tileset.png")
             && texture.keyboard.loadFromFile("data/graphics/keyboard.png"));
    }

}
