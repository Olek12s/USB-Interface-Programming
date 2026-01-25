//
// Created by Oleki on 24.01.2026.
//

#include "../include/Updater.h"
#include <iostream>
#include "../include/Game.h"

void Updater::globalTick() {

    // if game is stopped / not started - no ticks are performed
    if (!Game::isPending()) return;

    // Tick all existing blocks

    for (auto& row : Game::getBlocks()) {
        for (auto& block : row) {
            block.tick();
        }
    }

    // Generate new row of blocks whenever it would start reaching view

    float rowHeight = Block::getHeight() + Game::getPadding();
    std::vector<std::vector<Block>>& blocks = Game::getBlocks();
    if (!blocks.empty()) {
        float topRowY = blocks[0][0].getPosition().y + Block::getHeight(); // y of virutal -1 row
        if (topRowY >= rowHeight)
        {
            Game::generateNewRow();
            std::cout << "new row\n";
        }
    }
}
