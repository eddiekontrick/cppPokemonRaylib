#include "Animator.h"

#include <iostream>
#include <string>

#include "PokemonTemplate.h"
#include "tinyxml2.h"

namespace Pokemon {

void Animator::LoadSprite(const PokemonTemplate& pokemonTemplate) {
    const std::string path = "assets/" + pokemonTemplate.GetName() + "_sprites/Walk-Anim.png";
    sprite_ = LoadTexture(path.c_str());

    if (sprite_.id == 0) {
        std::cout << "Warning: Failed to load sprite for " << pokemonTemplate.GetName()
                  << " from " << path << std::endl;
        return;
    }

    LoadAnimationData(pokemonTemplate);
    sourceRec_ = {
        0.0f,
        0.0f,
        static_cast<float>(walkAnimation_.frameWidth),
        static_cast<float>(walkAnimation_.frameHeight)
    };
}

void Animator::LoadAnimationData(const PokemonTemplate& pokemonTemplate) {
    const std::string path = "assets/" + pokemonTemplate.GetName() + "_sprites/AnimData.xml";
    tinyxml2::XMLDocument document;

    if (document.LoadFile(path.c_str()) != tinyxml2::XML_SUCCESS) {
        std::cout << "Failed to load: " << path << std::endl;
        return;
    }

    tinyxml2::XMLElement* root = document.FirstChildElement("AnimData");
    tinyxml2::XMLElement* anims = root != nullptr ? root->FirstChildElement("Anims") : nullptr;
    if (anims == nullptr) {
        std::cout << "Failed to load animation data from: " << path << std::endl;
        return;
    }

    for (tinyxml2::XMLElement* anim = anims->FirstChildElement("Anim");
         anim != nullptr;
         anim = anim->NextSiblingElement("Anim")) {
        const tinyxml2::XMLElement* nameElement = anim->FirstChildElement("Name");
        const char* name = nameElement != nullptr ? nameElement->GetText() : nullptr;

        if (name != nullptr && std::string(name) == "Walk") {
            anim->FirstChildElement("FrameWidth")->QueryIntText(&walkAnimation_.frameWidth);
            anim->FirstChildElement("FrameHeight")->QueryIntText(&walkAnimation_.frameHeight);

            tinyxml2::XMLElement* durations = anim->FirstChildElement("Durations");
            if (durations == nullptr) {
                break;
            }

            for (tinyxml2::XMLElement* duration = durations->FirstChildElement("Duration");
                 duration != nullptr;
                 duration = duration->NextSiblingElement("Duration")) {
                int value = 0;
                duration->QueryIntText(&value);
                walkAnimation_.frameDurations.push_back(value);
            }
            break;
        }
    }
}

void Animator::SetAnimationState(Direction direction) {
    sourceRec_.y = static_cast<float>(static_cast<int>(direction) * walkAnimation_.frameHeight);
}

void Animator::Update(float dt) {
    animationTimer_ += dt;
    if (animationTimer_ >= frameDuration_) {
        animationTimer_ -= frameDuration_;
        currentFrame_++;
    }

    if (currentFrame_ >= static_cast<int>(walkAnimation_.frameDurations.size())) {
        currentFrame_ = 0;
    }
    sourceRec_.x = static_cast<float>(currentFrame_ * walkAnimation_.frameWidth);
}

void Animator::Draw(Vector2 position) {
    // ------ IMPORTANT -------
    // ** change this to currentAnimation later on **
    position.x -= walkAnimation_.frameWidth / 2;
    position.y -= walkAnimation_.frameHeight / 2;
    if (sprite_.id != 0) {
        DrawTextureRec(sprite_, sourceRec_, position, WHITE);
    }
    if (DevMode::getActiveFlag()){
        DrawRectangleLines(position.x, position.y, walkAnimation_.frameWidth, walkAnimation_.frameHeight, BLACK);
    }
}

}
