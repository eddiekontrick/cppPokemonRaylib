#include "Terrain.h"

namespace Terrain {

TerrainTemplate::TerrainTemplate(int moveCost, bool isWater, int length, int width, Color color) 
: moveCost_(moveCost), isWater_(isWater), dimensions_{length, width}, color_(color) {}

TerrainTemplate::TerrainTemplate(){}

void TerrainTemplate::Draw(Vector2 position) const {
    DrawRectangleV(
        position, 
        {static_cast<float>(dimensions_.width_), static_cast<float>(dimensions_.length_)},
        color_
    ); 
}

void TerrainTemplate::DrawCoordinates(Vector2 position) const {
    DrawRectangleLines(position.x, position.y, dimensions_.width_, dimensions_.length_, LIGHTGRAY);
    std::string coords = "{" + std::to_string(position.x) +  " , "  + std::to_string(position.y) + "}";
    DrawText(coords.c_str(), static_cast<int>(position.x), static_cast<int>(position.y), 5, BLACK);   
}

bool TerrainTemplate::CheckWaterTile() const { return isWater_; }

Vector2 TerrainTemplate::GetDimensions() const {
    return {static_cast<float>(dimensions_.width_), static_cast<float>(dimensions_.length_)};
}

}