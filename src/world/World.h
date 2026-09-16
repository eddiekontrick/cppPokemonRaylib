#pragma once

#include "../terrain/Terrain.h"
#include "WorldObject.h"
#include "../core/Constants.h"

#include <memory>

#include <vector>

namespace World {

class World{
    public:
        World();
        void Draw();
        void generateTerrain();
        void generateWorldObjects();
        const Terrain::TerrainTemplate& getTerrainTemplate(Terrain::TerrainType type) const;

    private:
        static const int numTilesWidth = WIDTH / 16;
        static const int numTilesHeight = HEIGHT / 16;
        // TerrainTemplate* tiles_[numTilesWidth][numTilesHeight];
        Terrain::TerrainType tiles_[numTilesWidth][numTilesHeight];
        // WorldObject* worldObjects_[numTilesWidth][numTilesHeight];
        bool occupied_[numTilesWidth][numTilesHeight];

        // Terrain templates
        Terrain::TerrainTemplate noneTerrainTemplate_;
        Terrain::TerrainTemplate grassTerrainTemplate_;
        Terrain::TerrainTemplate rockTerrainTemplate_;
        Terrain::TerrainTemplate waterTerrainTemplate_;

        // World Objects
        std::vector<std::unique_ptr<WorldObject>> worldObjects_;
        RockObject rock_;
        TreeObject tree_;
};

}