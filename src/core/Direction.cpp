#include "Direction.h"

Direction GetDirection(Vector2 direction){
    if (direction.y == 1 && direction.x == 1) return Direction::DOWN_RIGHT;
    else if (direction.y == 1 && direction.x == 0) return Direction::DOWN;
    else if (direction.y == 1 && direction.x == -1) return Direction::DOWN_LEFT;
    else if (direction.y == 0 && direction.x == 1) return Direction::RIGHT;
    else if (direction.y == 0 && direction.x == -1) return Direction::LEFT;
    else if (direction.y == -1 && direction.x == 1) return Direction::UP_RIGHT;
    else if (direction.y == -1 && direction.x == 0) return Direction::UP;
    else if (direction.y == -1 && direction.x == -1) return Direction::UP_LEFT;
    else return Direction::NONE;
}