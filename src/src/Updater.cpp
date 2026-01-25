//
// Created by Oleki on 24.01.2026.
//

#include "../include/Updater.h"
#include "../include/Game.h"

void Updater::globalTick() {
    // Tick all existing blocks
    for (auto& row : Game::getBlocks())
        for (auto& block : row)
            block.tick();
}
