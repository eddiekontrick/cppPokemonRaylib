#pragma once
#include "raylib.h"
#include "../dev_mode/DevMode.h"
#include <string>

namespace Terrain {

enum class TerrainType{
    NONE = -1,
    Grass,
    Water
};

struct TileDimensions{
    int length_;
    int width_;
};

class TerrainTemplate{
    public:
        TerrainTemplate(int moveCost, bool isWater, int length, int width, Color color);
        TerrainTemplate();
        void setDevMode(DevMode& devMode);

        void Draw(Vector2 position) const;
        void DrawCoordinates(Vector2 position) const;
        bool CheckWaterTile() const;
        Vector2 GetDimensions() const;

    private:
        int moveCost_;
        bool isWater_;
        Color color_;
        TileDimensions dimensions_;
        DevMode* devMode_ = nullptr;
        // Texture texture_;
};

}