#pragma once

#include <vector>

#include "raylib.h"
#include "../core/Direction.h"
#include "dev_mode/DevMode.h"

namespace Pokemon {

class PokemonTemplate;

class Animator {
public:
    Animator() = default;

    void LoadSprite(const PokemonTemplate& pokemonTemplate);
    void LoadAnimationData(const PokemonTemplate& pokemonTemplate);
    void SetAnimationState(Direction direction);
    void Update(float dt);
    void Draw(Vector2 position);

private:
    struct AnimationData {
        int frameWidth = 0;
        int frameHeight = 0;
        std::vector<int> frameDurations;
    };

    Texture2D sprite_{};
    AnimationData walkAnimation_;
    Rectangle sourceRec_{};
    int currentFrame_ = 0;
    float animationTimer_ = 0.0f;
    float frameDuration_ = 0.15f;
};

}
