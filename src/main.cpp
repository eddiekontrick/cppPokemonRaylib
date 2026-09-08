#include <iostream>
#include <algorithm>
#include <vector>
#include <cstdlib>
#include <string>
#include "raylib.h"
#include "tinyxml2.h"

const int WIDTH = 800;
const int HEIGHT = 450;

enum Direction{
    DOWN,
    DOWN_RIGHT,
    RIGHT,
    UP_RIGHT,
    UP,
    UP_LEFT,
    LEFT,
    DOWN_LEFT,
    NONE
};

Direction GetDirection(Vector2 direction){
    if (direction.y == 1 && direction.x == 1) return DOWN_RIGHT; 
    else if (direction.y == 1 && direction.x == 0) return DOWN;
    else if (direction.y == 1 && direction.x == -1) return DOWN_LEFT;
    else if (direction.y == 0 && direction.x == 1) return RIGHT;
    else if (direction.y == 0 && direction.x == -1) return LEFT;
    else if (direction.y == -1 && direction.x == 1) return UP_RIGHT;
    else if (direction.y == -1 && direction.x == 0) return UP;
    else if (direction.y == -1 && direction.x == -1) return UP_LEFT;
    else return NONE;
}

struct TileDimensions{
    int length_;
    int width_;
};

class Terrain{
    public:
        Terrain(int moveCost, bool isWater, int length, int width, Color color) 
        : moveCost_(moveCost), isWater_(isWater), dimensions_{length, width}, color_(color) {}
        Terrain(){}

        void Draw(Vector2 position);
        void DrawCoordinates(Vector2 position);
        bool CheckWaterTile();
        Vector2 GetDimensions();

    private:
        int moveCost_;
        bool isWater_;
        Color color_;
        TileDimensions dimensions_;
        // Texture texture_;
};

void Terrain::Draw(Vector2 position){
    DrawRectangleV(
        position, 
        {static_cast<float>(dimensions_.width_), static_cast<float>(dimensions_.length_)},
        color_
    ); 
}

void Terrain::DrawCoordinates(Vector2 position){
    DrawRectangleLines(position.x, position.y, dimensions_.width_, dimensions_.length_, LIGHTGRAY);
    std::string coords = "{" + std::to_string(position.x) +  " , "  + std::to_string(position.y) + "}";
    DrawText(coords.c_str(), static_cast<int>(position.x), static_cast<int>(position.y), 5, BLACK);   
}

bool Terrain::CheckWaterTile() { return isWater_; }

Vector2 Terrain::GetDimensions(){
    return {static_cast<float>(dimensions_.width_), static_cast<float>(dimensions_.length_)};
}

// Turn this into world object template
class WorldObject{
    public:
        WorldObject(Vector2 position);
        WorldObject(){}
        void Draw();
        void Draw(Vector2 position);
        void setPosition(int x, int y);
        int getPositionX();
        int getPositionY();
    private:
        // -----------------
        // THIS is the issue, every instance has the same position because its a pointer
        // _________________
        Vector2 position_;
};

int WorldObject::getPositionX(){ return position_.x; }
int WorldObject::getPositionY(){ return position_.y; }

WorldObject::WorldObject(Vector2 position)
: position_(position){}

// Draw should know its position
void WorldObject::Draw(){
    Vector2 trunkSize = { 6, 12 };
    Vector2 top = {position_.x + 3, position_.y - 12};
    Vector2 bottomRight = { position_.x + 12, position_.y};
    Vector2 bottomLeft = { position_.x - 6, position_.y};
    DrawRectangleV(position_, trunkSize, BROWN);
    DrawTriangle(top, bottomLeft, bottomRight, DARKGREEN);
    DrawTriangle({top.x, top.y - 6}, {bottomLeft.x, bottomLeft.y - 6}, {bottomRight.x, bottomRight.y - 6}, DARKGREEN);
}
/*
    THIS IS A TEMPORARY FIX
    the real solution will be implementing a separate WorldObjectTemplate virtual class with all the static variables
    and a WorldObject, or maybe just derived classes, with instance specific variables
*/
void WorldObject::Draw(Vector2 position){
    Vector2 trunkSize = { 6, 12 };
    Vector2 top = {position.x + 3, position.y - 12};
    Vector2 bottomRight = { position.x + 12, position.y};
    Vector2 bottomLeft = { position.x - 6, position.y};
    DrawRectangleV(position, trunkSize, BROWN);
    DrawTriangle(top, bottomLeft, bottomRight, DARKGREEN);
    DrawTriangle({top.x, top.y - 6}, {bottomLeft.x, bottomLeft.y - 6}, {bottomRight.x, bottomRight.y - 6}, DARKGREEN);
}

void WorldObject::setPosition(int x, int y){
    position_.x = x;
    position_.y = y;
}

class World{
    public:
        World();
        void Draw();
        void generateTerrain();
        void generateWorldObjects();
        void showOccupied();

    private:
        static const int numTilesWidth = WIDTH / 16;
        static const int numTilesHeight = HEIGHT / 16;
        Terrain* tiles_[numTilesWidth][numTilesHeight];
        WorldObject* worldObjects_[numTilesWidth][numTilesHeight];
        bool occupied_[numTilesWidth][numTilesHeight];
        Terrain grassTerrain_;
        Terrain rockTerrain_;
        Terrain waterTerrain_;
        WorldObject tree_;
        WorldObject rock_;
};

void World::showOccupied(){
    Vector2 position = { 0 , 0 };
    std::cout << "Occupied grid: \n" << std::endl;
    std::cout << "\n------------------------------" << std::endl;
    for (int i = 0; i < numTilesWidth; i++){
        for (int j = 0; j < numTilesHeight; j++){
            position.x = i * tiles_[i][j]->GetDimensions().x;
            position.y = j * tiles_[i][j]->GetDimensions().y;
            std::cout << "|" << occupied_[i][j] << "\{" << position.x  << "," << position.y << "}" << "|";
        }
        std::cout << "\n------------------------------" << std::endl;
    }
}

World::World()
:   grassTerrain_(1, false, 16, 16, GREEN),
    rockTerrain_(2, false, 16, 16, BROWN),
    waterTerrain_(3, true, 16, 16, BLUE),
    tree_(),
    rock_()
{
    for (int i = 0; i < numTilesWidth; i++) {
        for (int j = 0; j < numTilesHeight; j++) {
            tiles_[i][j] = nullptr;
            worldObjects_[i][j] = nullptr;
            occupied_[i][j] = false;
        }
    }
}

void World::generateTerrain(){
    for (int i = 0; i < numTilesWidth; i++){
        for (int j = 0; j < numTilesHeight; j++){
            if (tiles_[i][j] != nullptr) { continue; }

            if (rand() % 100 >= 99){
                tiles_[i][j] = &waterTerrain_;

                int waterDecision = rand() % 4;
                if (waterDecision >= 3) {
                    // fill entire row with water
                    for (Terrain*& tile : tiles_[i]) {
                        tile = &waterTerrain_; 
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
                                tiles_[k][l] = &waterTerrain_;
                            }
                        }
                    }
                }
            }
            else {
                tiles_[i][j] = &grassTerrain_;
            }
        }
    }
}

void World::generateWorldObjects(){
    for (int i = 0; i < numTilesWidth; i++){
        for (int j = 0; j < numTilesHeight; j++){
            // skip if water tile
            // SOMETHING ABOUT THIS is not working
            if (tiles_[i][j]->CheckWaterTile()) { continue; }

            int random = rand() % 101;
            if (random >= 95){
                int radius = rand() % 5;
                for (int k = ((i - radius) > 0) ? (i - radius) : 0; k < i + radius && k < numTilesWidth; k++){
                    for (int l = ((j - radius) > 0) ? (j - radius) : 0; l < j + radius && l < numTilesHeight; l++){
                        int treeRandom = rand() % 100;
                        // skip if already set to something, and randomly decide to place
                        if (tiles_[k][l]->CheckWaterTile()) { continue; } 
                        if (worldObjects_[k][l] != nullptr && treeRandom <= 1) { continue; }
                        worldObjects_[k][l] = &tree_;
                        worldObjects_[k][l]->setPosition(k * tiles_[k][l]->GetDimensions().x, l * tiles_[k][l]->GetDimensions().x);
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
            if (tiles_[i][j] != nullptr) {
                position.x = i * tiles_[i][j]->GetDimensions().x;
                position.y = j * tiles_[i][j]->GetDimensions().y;
                tiles_[i][j]->Draw(position);
                if (worldObjects_[i][j] != nullptr) { 
                    // Change this back once compartmentalization of classes for world objects
                    worldObjects_[i][j]->Draw(position);    
                }
            }
        }
    }
}

class InputHandler{
    public:
        InputHandler();
        Vector2 GetMovementDirection();
};

InputHandler::InputHandler(){};

Vector2 InputHandler::GetMovementDirection(){
    Vector2 direction = { 0.0f, 0.0f };

    if (IsKeyDown(KEY_W)){ direction.y -= 1; }
    if (IsKeyDown(KEY_S)){ direction.y += 1; }
    if (IsKeyDown(KEY_A)){ direction.x -= 1; }
    if (IsKeyDown(KEY_D)){ direction.x += 1; }

    return direction;
}

class PokemonTemplate {
    public:
        PokemonTemplate(std::string name, float hp, float attack, float sp_attack, float defense, float sp_defense, float speed, Vector2 hitbox);
        void DisplayStats() const;
        float GetSpeed() const;
        std::string GetName() const;

    private:
        // Pokemon's name
        std::string name_;
        // Pokemon Base stats
        float hp_;
        float attack_;
        float sp_attack_;
        float defense_;
        float sp_defense_;
        float speed_;
        //
        Vector2 hitbox_;
};

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

// This is the frame window dimensions for each sprite sheet
struct AnimationData {
    int frameWidth_ = 0;
    int frameHeight_ = 0;
    std::vector<int> frameDurations_; // how many frames in a direction (row)
};

class Animator{
    public:
        Animator();
        void LoadSprite(const PokemonTemplate& pkmn_tmp);
        void LoadAnimationData(const PokemonTemplate& pkmn_tmp);
        void SetAnimationState(Direction direction);
        void Update(float dt);
        void Draw(Vector2 position);
    private:
        Texture2D sprite_{};
        AnimationData walkAnimation_;
        Rectangle sourceRec_{};

        int currentFrame_ = 0;
        float animationTimer_ = 0.0f;
        float frameDuration_ = 0.15f;
};

Animator::Animator(){}

void Animator::LoadSprite(const PokemonTemplate& pkmn_tmp) {
    std::string path = "assets/" + pkmn_tmp.GetName() + "_sprites/Walk-Anim.png";
    sprite_ = LoadTexture(path.c_str());
    
    if (sprite_.id == 0) {
        std::cout << "Warning: Failed to load sprite for " << pkmn_tmp.GetName() << " from " << path << std::endl;
        return;
    }

    LoadAnimationData(pkmn_tmp);

    sourceRec_ = {
        0.0f,
        0.0f,
        static_cast<float>(walkAnimation_.frameWidth_),
        static_cast<float>(walkAnimation_.frameHeight_)
    };
}

void Animator::LoadAnimationData(const PokemonTemplate& pkmn_tmp) {
    std::string path = "assets/" + pkmn_tmp.GetName() + "_sprites/AnimData.xml";

    tinyxml2::XMLDocument document;

    if (document.LoadFile(path.c_str()) != tinyxml2::XML_SUCCESS) {
        std::cout << "Failed to load: " << path << std::endl;
        return;
    }

    tinyxml2::XMLElement* anims = document.FirstChildElement("AnimData")->FirstChildElement("Anims");

    for (tinyxml2::XMLElement* anim = anims->FirstChildElement("Anim"); anim != nullptr; anim = anim->NextSiblingElement("Anim")) {
        const char* name = anim->FirstChildElement("Name")->GetText();

        if (name != nullptr && std::string(name) == "Walk") {
            anim->FirstChildElement("FrameWidth")->QueryIntText(&walkAnimation_.frameWidth_);
            anim->FirstChildElement("FrameHeight")->QueryIntText(&walkAnimation_.frameHeight_);

            tinyxml2::XMLElement* durations = anim->FirstChildElement("Durations");

            for (tinyxml2::XMLElement* duration = durations->FirstChildElement("Duration"); duration != nullptr; duration = duration->NextSiblingElement("Duration")) {
                int value;
                duration->QueryIntText(&value);
                walkAnimation_.frameDurations_.push_back(value);
            }
            // Will add later animations in the future, for now just handle walk
            break;
        }
    }
}

void Animator::SetAnimationState(Direction direction){
    // see how to implement animator
    sourceRec_.y = float(direction * walkAnimation_.frameHeight_);
}

void Animator::Update(float dt){
    animationTimer_ += dt;
    if (animationTimer_ >= frameDuration_){
        animationTimer_ -= frameDuration_;
        currentFrame_++;
    }
    if (currentFrame_ >= walkAnimation_.frameDurations_.size()) currentFrame_ = 0;
    sourceRec_.x = float(currentFrame_ * walkAnimation_.frameWidth_);
}

void Animator::Draw(Vector2 position){
    if (sprite_.id != 0) {
        DrawTextureRec(sprite_, sourceRec_, position, WHITE);
    }
}

class Pokemon{
    public:
        Pokemon(const PokemonTemplate& pkmn_template, Vector2 initPosition={WIDTH/2, HEIGHT/2});
        void Move(Vector2 direction, float dt);
        void Update(float dt);
        void Draw();
        void DisplayStats();
        const PokemonTemplate& GetTemplate() const;

    private:
        const PokemonTemplate& pkmn_template_;
        Animator animator_;
        Vector2 position_ = { (float)WIDTH / 2, (float)HEIGHT / 2 };
        Direction direction_ = DOWN;
        Color color_ = SKYBLUE;
        // --- POKEMON STATS --- //
        // Pokemon IVs
        float hp_iv_;
        float attack_iv_;
        float sp_attack_iv_;
        float defense_iv_;
        float sp_defense_iv_;
        float speed_iv_;
        // Pokemon EVs
        float hp_ev_ = 0;
        float attack_ev_ = 0;
        float sp_attack_ev_ = 0;
        float defense_ev_ = 0;
        float sp_defense_ev_ = 0;
        float speed_ev_ = 0;
};

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
    if (new_direction != NONE) direction_ = new_direction;
    animator_.SetAnimationState(direction_);
}

void Pokemon::Draw(){
    animator_.Draw(position_);
}

int main()
{
    InitWindow(800, 450, "Raylib Test");
    World world;
    world.generateTerrain();
    world.generateWorldObjects();
    InputHandler input_handler = InputHandler();

    Vector2 standHitbox = { 20, 20 };

    const PokemonTemplate jirachi_template("jirachi", 100, 100, 100, 100, 100, 100, standHitbox);
    const PokemonTemplate celebi_template("celebi", 100, 100, 100, 100, 100, 100, standHitbox);
    const PokemonTemplate gible_template("gible", 58, 70, 45, 40, 45, 42, standHitbox);
    Pokemon jirachi(jirachi_template);
    Pokemon celebi(celebi_template, { (float)(rand() % 700 + 100), (float)(rand() % 400 + 50) });
    Pokemon gible(gible_template, { (float)(rand() % 700 + 100), (float)(rand() % 400 + 50) });
    
    while (!WindowShouldClose())
    {   
        float dt = GetFrameTime();
        // world.showOccupied();
        jirachi.Move(input_handler.GetMovementDirection(), dt);
        jirachi.Update(dt);
        gible.Update(dt);
        celebi.Update(dt);

        BeginDrawing();

        world.Draw();
        ClearBackground(RAYWHITE);
        
        jirachi.Draw();
        gible.Draw();
        celebi.Draw();

        EndDrawing();
    }

    CloseWindow();

    return 0;
}