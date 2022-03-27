//
// Created by Arthur Blaise on 07/03/2022.
//

#include "Player.h"
#include "World.h"

#include <iostream>


Player::Player() {
    inventory.setItem(0,*(new Block("dirt")));
    inventory.setItem(1,*(new Block("stone")));
    inventory.setItem(2,*(new Block("glass")));
    inventory.setItem(4,*(new Block("sponge")));
    inventory.setItem(5,*(new Block("soul_soil")));
}

bool Player::checkCollisions(World world) {
    BoundingBox playerBox = this->getBoundingBox();
    std::map<Vector3,Block> blocks = world.get_blocks({position.x-2,position.y-3,position.z-2},{position.x+2,position.y+2,position.z+2});
    for (auto &block : blocks) {
        if (CheckCollisionBoxes(playerBox, block.second.getBoundingBox(block.first))) {
            Vector3 faces[6] = {
                    Vector3 {1, 0, 0} , Vector3 {-1, 0, 0},
                    Vector3 {0, 1, 0} , Vector3 {0, -1, 0},
                    Vector3 {0, 0, 1} , Vector3 {0, 0, -1},
            };
            // A is player, B is block
            Vector3 maxA = playerBox.max;
            Vector3 minA = playerBox.min;
            Vector3 maxB = block.second.getBoundingBox(block.first).max;
            Vector3 minB = block.second.getBoundingBox(block.first).min;

            float distances[6] = {
                    maxB.x - minA.x,
                    maxA.x - minB.x,
                    maxB.y - minA.y,
                    maxA.y - minB.y,
                    maxB.z - minA.z,
                    maxA.z - minB.z
            };
            float penetration = 100000;
            Vector3 bestAxis;
            for (int i = 0; i < 6; i++) {
                if (distances[i] < penetration) {
                    penetration = distances[i];
                    bestAxis = faces[i];
                }
            }
            if (penetration == 0) {
                continue;
            }
//            std::cout << "penetration: " << penetration << " " << bestAxis.x << " " << bestAxis.y << " " << bestAxis.z << std::endl;
            move(bestAxis.x*penetration, bestAxis.y*penetration, bestAxis.z*penetration);

            return true;
        }
    }
}

void Player::drawInventory() {
    inventory.drawInventory();
}

void Player::handleInventoryGestures() {
    inventory.deviceManagement();
}

bool Player::hasInventoryOpen() {
    return inventory.isInventoryMenu();
}

BoundingBox Player::getBoundingBox() const {
    return (BoundingBox) {
            (Vector3) {
                    position.x - 0.5f,
                    position.y - 1.5f,
                    position.z - 0.5f
            },
            (Vector3) {
                    position.x + 0.5f,
                    position.y + 0.3f,
                    position.z + 0.5f
            }
    };
}

Vector3 Player::getPosition() const {
    return position;
}

void Player::setPosition(Vector3 pos) {
    this->position = pos;
}

void Player::move(float x, float y, float z) {
    position.x += x;
    position.y += y;
    position.z += z;
}