#pragma once

#include "raylib.h"

enum class Direction{
    DOWN,
    DOWN_RIGHT,
    RIGHT,
    UP_RIGHT,
    UP,
    UP_LEFT,
    LEFT,
    DOWN_LEFT,
    NONE
};

Direction GetDirection(Vector2 direction);
