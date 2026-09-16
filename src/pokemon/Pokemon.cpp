#include "Pokemon.h"

namespace Pokemon {

Pokemon::Pokemon(const PokemonTemplate& pkmn_template, Vector2 initPosition) : pkmn_template_(pkmn_template) {

    // Initialize animator and load sprite
    animator_ = Animator();
    animator_.LoadSprite(pkmn_template_);

    // Load all the stats
    hp_iv_ = rand() % 32;
    attack_iv_ = rand() % 32;
    sp_attack_iv_ = rand() % 32;
    defense_iv_ = rand() % 32;
    sp_defense_iv_ = rand() % 32;
    speed_iv_ = rand() % 32;

    position_ = initPosition;
}

void Pokemon::Update(float dt){
    animator_.Update(dt);
}

void Pokemon::DisplayStats(){
    std::cout << pkmn_template_.GetName() << "'s IVs: "
            << "\nHP: " << hp_iv_ 
            << "\nAttack: " << attack_iv_
            << "\nSpecial Attack: " << sp_attack_iv_
            << "\nDefense: " << defense_iv_
            << "\nSpecial Defense: " << sp_defense_iv_
            << "\nSpeed: " << speed_iv_ << std::endl;
}

const PokemonTemplate& Pokemon::GetTemplate() const { return pkmn_template_; }

void Pokemon::Move(Vector2 direction, float dt){ 
    if (direction.x != 0 || direction.y != 0){
        position_.x += direction.x * pkmn_template_.GetSpeed() * dt;
        position_.y += direction.y * pkmn_template_.GetSpeed() * dt;
    }
    Direction new_direction = GetDirection(direction);
    if (new_direction != Direction::NONE) direction_ = new_direction;
    animator_.SetAnimationState(direction_);
}

void Pokemon::Draw(){
    animator_.Draw(position_);
}

}