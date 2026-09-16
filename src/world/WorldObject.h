#pragma once

#include "raylib.h"

namespace World {

class WorldObject{
    public:
        virtual ~WorldObject(){}
        virtual void Draw() = 0;
        void setPosition(Vector2 position);
        Vector2 getTile() const;
        Vector2 getPosition() const;

    protected:
        Vector2 position_;
        // int radius; For how much space it occupies
        // Texture2D texture;
};

class TreeObject : public WorldObject{
    public:
        TreeObject(){}
        virtual void Draw();
};

class RockObject : public WorldObject{
    public:
        RockObject(){}
        virtual void Draw() override;
};


}