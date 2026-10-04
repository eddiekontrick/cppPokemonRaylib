#pragma once

#include "../terrain/Terrain.h"
#include "WorldObject.h"
#include "../core/Constants.h"
#include "../dev_mode/DevMode.h"

#include <memory>
#include <vector>

namespace World {

struct Tile {
    Terrain::TerrainType terrainType;
    bool isOccupied;
    std::unique_ptr<WorldObject> owner;
};

class World{
    public:
        World();
        void setDevMode(DevMode& devMode);
        void Draw();
        void generateTerrain();
        void generateWorldObjects();
        const Terrain::TerrainTemplate& getTerrainTemplate(Terrain::TerrainType type) const;
        bool searchTileRadius(int radius, int x, int y);

    private:
        static const int numTilesWidth = WIDTH / TILE_SIZE;
        static const int numTilesHeight = HEIGHT / TILE_SIZE;
        // TerrainTemplate* tiles_[numTilesWidth][numTilesHeight];
        // Terrain::TerrainType tiles_[numTilesWidth][numTilesHeight];
        // WorldObject* worldObjects_[numTilesWidth][numTilesHeight];
        // bool occupied_[numTilesWidth][numTilesHeight];

        Tile tiles_[numTilesWidth][numTilesHeight];

        // Terrain templates
        Terrain::TerrainTemplate noneTerrainTemplate_;
        Terrain::TerrainTemplate grassTerrainTemplate_;
        Terrain::TerrainTemplate rockTerrainTemplate_;
        Terrain::TerrainTemplate waterTerrainTemplate_;

        // World Objects
        std::vector<std::unique_ptr<WorldObject>> worldObjects_;
        RockObject rock_;
        TreeObject tree_;

        DevMode* devMode_ = nullptr;
};

}