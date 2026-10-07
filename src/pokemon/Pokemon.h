#pragma once

#include "Animator.h"
#include "PokemonTemplate.h"
#include "raylib.h"
#include "../core/Constants.h"
#include "../core/Direction.h"
#include "dev_mode/DevMode.h"

namespace Pokemon {

class Pokemon{
    public:
        Pokemon(const PokemonTemplate& pkmn_template, Vector2 initPosition={WIDTH/2, HEIGHT/2});
        void Move(Vector2 direction, float dt);
        void Update(float dt);
        void Draw();
        void DisplayStats();
        const PokemonTemplate& GetTemplate() const;

    private:
        const PokemonTemplate& pkmn_template_;
        Animator animator_;
        Vector2 position_ = { (float)WIDTH / 2, (float)HEIGHT / 2 };
        Direction direction_ = Direction::DOWN;
        Color color_ = SKYBLUE;
        // --- POKEMON STATS --- //
        // Pokemon IVs
        float hp_iv_;
        float attack_iv_;
        float sp_attack_iv_;
        float defense_iv_;
        float sp_defense_iv_;
        float speed_iv_;
        // Pokemon EVs
        float hp_ev_ = 0;
        float attack_ev_ = 0;
        float sp_attack_ev_ = 0;
        float defense_ev_ = 0;
        float sp_defense_ev_ = 0;
        float speed_ev_ = 0;

        int radius_ = 1;
};

}
