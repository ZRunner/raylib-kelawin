//
// Created by Arthur Blaise on 23/02/2022.
//

#include "Block.h"
#include <utility>

Block::Block(std::string name) {
    this->_name = std::move(name);
}

void Block::draw(Texture2D texture, Vector3 position) const {
    DrawCubeTexture(texture, position, 1.0f, 1.0f, 1.0f, WHITE);
}

std::string Block::getName() const {
    return this->_name;
}
