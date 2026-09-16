#include "WorldObject.h"

namespace World {

void WorldObject::setPosition(Vector2 position){ position_ = position; }
Vector2 WorldObject::getPosition() const { return position_; }

Vector2 WorldObject::getTile() const{
    Vector2 tileLocation = position_;
    tileLocation.x = tileLocation.x / 16;
    tileLocation.y = tileLocation.y / 16;
    return tileLocation;
}

void TreeObject::Draw(){
    Vector2 trunkSize = { 6, 12 };
    Vector2 position = { position_.x + 5, position_.y };
    Vector2 top = { position.x + 3, position.y - 12};
    Vector2 bottomRight = { position.x + 12, position.y};
    Vector2 bottomLeft = { position.x - 6, position.y};
    DrawRectangleV(position, trunkSize, BROWN);
    DrawTriangle(top, bottomLeft, bottomRight, DARKGREEN);
    DrawTriangle({top.x, top.y - 6}, {bottomLeft.x, bottomLeft.y - 6}, {bottomRight.x, bottomRight.y - 6}, DARKGREEN);
}

void RockObject::Draw(){
    DrawRectangleV(position_, {16,16}, GRAY);
    DrawRectangleV({position_.x + 5, position_.y}, {10,10}, LIGHTGRAY);
}

}