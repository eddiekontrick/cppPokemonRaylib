#pragma once

#include <string>
#include <iostream>

#include "raylib.h"

namespace Pokemon {

class PokemonTemplate {
    public:
        PokemonTemplate(std::string name, float hp, float attack, float sp_attack, float defense, float sp_defense, float speed, Vector2 hitbox);
        void DisplayStats() const;
        float GetSpeed() const;
        std::string GetName() const;

    private:
        // Pokemon's name
        std::string name_;
        // Pokemon Base stats
        float hp_;
        float attack_;
        float sp_attack_;
        float defense_;
        float sp_defense_;
        float speed_;
        //
        Vector2 hitbox_;
};

}