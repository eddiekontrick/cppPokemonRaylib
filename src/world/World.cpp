#include "World.h"

namespace World {

World::World()
:   noneTerrainTemplate_(0, false, 16, 16, GRAY),
    grassTerrainTemplate_(1, false, 16, 16, GREEN),
    rockTerrainTemplate_(2, false, 16, 16, BROWN),
    waterTerrainTemplate_(3, true, 16, 16, BLUE),
    tree_(),
    rock_()
{
    for (int i = 0; i < numTilesWidth; i++) {
        for (int j = 0; j < numTilesHeight; j++) {
            tiles_[i][j] = Terrain::TerrainType::NONE;
            occupied_[i][j] = false;
        }
    }
}

const Terrain::TerrainTemplate& World::getTerrainTemplate(Terrain::TerrainType type) const{
    switch(type){
        case(Terrain::TerrainType::NONE) : return noneTerrainTemplate_;
        case(Terrain::TerrainType::Grass) : return grassTerrainTemplate_;
        case(Terrain::TerrainType::Water): return waterTerrainTemplate_;
    }
}

void World::generateTerrain(){
    for (int i = 0; i < numTilesWidth; i++){
        for (int j = 0; j < numTilesHeight; j++){
            if (tiles_[i][j] != Terrain::TerrainType::NONE) { continue; }

            if (rand() % 100 >= 99){
                tiles_[i][j] = Terrain::TerrainType::Water;

                int waterDecision = rand() % 4;
                if (waterDecision >= 3) {
                    // fill entire row with water
                    for (Terrain::TerrainType& tile : tiles_[i]) {
                        tile = Terrain::TerrainType::Water; 
                    }
                }
                else {
                    int pondRadius = rand() % 3 + 3; // [3, 5]
                    int kMin = std::max(0, i - pondRadius);
                    int kMax = std::min(numTilesWidth - 1, i + pondRadius);
                    int lMin = std::max(0, j - pondRadius);
                    int lMax = std::min(numTilesHeight - 1, j + pondRadius);

                    for (int k = kMin; k <= kMax; k++){
                        for (int l = lMin; l <= lMax; l++){
                            int dx = k - i;
                            int dy = l - j;
                            if (dx*dx + dy*dy <= pondRadius*pondRadius){
                                tiles_[k][l] = Terrain::TerrainType::Water;
                            }
                        }
                    }
                }
            }
            else {
                tiles_[i][j] = Terrain::TerrainType::Grass;
            }
        }
    }
}

void World::generateWorldObjects(){
    for (int i = 0; i < numTilesWidth; i++){
        for (int j = 0; j < numTilesHeight; j++){
            // skip if water tile
            // SOMETHING ABOUT THIS is not working
            if (tiles_[i][j] == Terrain::TerrainType::Water) { continue; }

            int random = rand() % 101;
            if (random >= 98){
                int radius = rand() % 5;
                for (int k = ((i - radius) > 0) ? (i - radius) : 0; k < i + radius && k < numTilesWidth; k++){
                    for (int l = ((j - radius) > 0) ? (j - radius) : 0; l < j + radius && l < numTilesHeight; l++){
                        int treeRandom = rand() % 100;
                        // skip if already set to something, and randomly decide to place
                        if (tiles_[k][l] == Terrain::TerrainType::Water) { continue; } 
                        if (occupied_[k][l] == true) { continue; }
                        if (treeRandom >= 50) { continue; }
                        worldObjects_.push_back(std::make_unique<TreeObject>());
                        Vector2 position = {static_cast<float>(k * 16), static_cast<float>(l * 16)};
                        worldObjects_.back()->setPosition(position);
                        occupied_[k][l] = true;
                    }
                }
            }
            else if (random >= 97){
                int radius = rand() % 3;
                for (int k = ((i - radius) > 0) ? (i - radius) : 0; k < i + radius && k < numTilesWidth; k++){
                    for (int l = ((j - radius) > 0) ? (j - radius) : 0; l < j + radius && l < numTilesHeight; l++){
                        int rockRandom = rand() % 10;
                        if (tiles_[k][l] == Terrain::TerrainType::Water) { continue; } 
                        if (occupied_[k][l] == true) { continue; }
                        if (rockRandom >= 4) { continue; }
                        worldObjects_.push_back(std::make_unique<RockObject>());
                        Vector2 position = {static_cast<float>(k * 16), static_cast<float>(l * 16)};
                        worldObjects_.back()->setPosition(position);
                        occupied_[k][l] = true;
                    }
                }
            }
        }
    }
}

void World::Draw(){
    Vector2 position = { 0, 0 };
    for (int i = 0; i < numTilesWidth; i++){
        for (int j = 0; j < numTilesHeight; j++){
            if (tiles_[i][j] != Terrain::TerrainType::NONE) {
                position.x = i * getTerrainTemplate(tiles_[i][j]).GetDimensions().x; 
                position.y = j * getTerrainTemplate(tiles_[i][j]).GetDimensions().y; 
                getTerrainTemplate(tiles_[i][j]).Draw(position);
            }
        }
    }
    for (auto& object : worldObjects_){
        object->Draw();
    }
}

}