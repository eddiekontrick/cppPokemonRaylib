#include "PokemonTemplate.h"

namespace Pokemon {

PokemonTemplate::PokemonTemplate(std::string name, float hp, float attack, float sp_attack, float defense, float sp_defense, float speed, Vector2 hitbox)
    : name_(name), hp_(hp), attack_(attack), sp_attack_(sp_attack), defense_(defense), sp_defense_(sp_defense), speed_(speed), hitbox_(hitbox) {}


float PokemonTemplate::GetSpeed() const{
    return speed_;
}

std::string PokemonTemplate::GetName() const{
    return name_;
}

void PokemonTemplate::DisplayStats() const{
    std::cout << name_ << "'s Base Stats: "
            << "HP: " << hp_ 
            << "\nAttack: " << attack_ 
            << "\nSpecial Attack: " << sp_attack_
            << "\nDefense: " << defense_
            << "\nSpecial Defense: " << sp_defense_
            << "\nSpeed: " << speed_ << std::endl;
}

}