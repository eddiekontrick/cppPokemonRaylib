#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <string>

#include "core/Direction.h"
#include "terrain/Terrain.h"
#include "world/World.h"
#include "core/Constants.h"
#include "pokemon/Pokemon.h"
#include "pokemon/PokemonTemplate.h"

#include "raylib.h"

class InputHandler{
    public:
        InputHandler();
        Vector2 GetMovementDirection();
};

InputHandler::InputHandler(){};

Vector2 InputHandler::GetMovementDirection(){
    Vector2 direction = { 0.0f, 0.0f };

    if (IsKeyDown(KEY_W)){ direction.y -= 1; }
    if (IsKeyDown(KEY_S)){ direction.y += 1; }
    if (IsKeyDown(KEY_A)){ direction.x -= 1; }
    if (IsKeyDown(KEY_D)){ direction.x += 1; }

    return direction;
}

int main()
{
    InitWindow(800, 450, "Raylib Test");
    World::World world;
    world.generateTerrain();
    world.generateWorldObjects();
    InputHandler input_handler = InputHandler();

    Vector2 standHitbox = { 20, 20 };

    const Pokemon::PokemonTemplate jirachi_template("jirachi", 100, 100, 100, 100, 100, 100, standHitbox);
    const Pokemon::PokemonTemplate celebi_template("celebi", 100, 100, 100, 100, 100, 100, standHitbox);
    const Pokemon::PokemonTemplate gible_template("gible", 58, 70, 45, 40, 45, 42, standHitbox);
    Pokemon::Pokemon jirachi(jirachi_template);
    Pokemon::Pokemon celebi(celebi_template, { (float)(rand() % 400 + 100), (float)(rand() % 200 + 50) });
    Pokemon::Pokemon gible(gible_template, { (float)(rand() % 700 + 100), (float)(rand() % 400 + 50) });
    
    while (!WindowShouldClose())
    {   
        float dt = GetFrameTime();
        // world.showOccupied();
        jirachi.Move(input_handler.GetMovementDirection(), dt);
        jirachi.Update(dt);
        gible.Update(dt);
        celebi.Update(dt);

        BeginDrawing();

        world.Draw();
        ClearBackground(RAYWHITE);
        
        jirachi.Draw();
        gible.Draw();
        celebi.Draw();

        EndDrawing();
    }

    CloseWindow();

    return 0;
}