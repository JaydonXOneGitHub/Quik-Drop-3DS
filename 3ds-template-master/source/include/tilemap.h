#pragma once

#include <vector>
#include "citro2d.h"
#include "vector2.h"
#include "box2d/box2d.h"
#include <string>

enum TileGFXTypes
{
    MIDDLE_BOTTOM = 0,
    RIGHT_BOTTOM = 1,
    LEFT_BOTTOM = 2,
    MIDDLE_TOP = 3,
    RIGHT_TOP = 4,
    LEFT_TOP = 5,
    MIDDLE_MIDDLE = 6,
    RIGHT_MIDDLE = 7,
    LEFT_MIDDLE = 8,
    TOP_RIGHT_CORNER = 9,
    TOP_LEFT_CORNER = 10,
    BOTTOM_LEFT_CORNER = 11,
    BOTTOM_RIGHT_CORNER = 12
};

enum TileCollisionTypes
{
    SOLID = 0,
    NONE = 1,
};

struct Tile
{
    Vector2 position;
    int sheetIndex;

    C2D_Image image;

    b2Body* body = nullptr;
    b2Fixture* fixture = nullptr;
    b2World* world = nullptr;

    Tile(const C2D_SpriteSheet& sheet, 
    int sheetIndex, 
    Vector2 position, 
    TileCollisionTypes collisionType, b2World* world)
        : sheetIndex(sheetIndex), position(position)
    {
        this->image = C2D_SpriteSheetGetImage(sheet, this->sheetIndex % C2D_SpriteSheetCount(sheet));

        if (collisionType == TileCollisionTypes::SOLID)
        {
            this->world = world;
            b2BodyDef def;
            def.type = b2_staticBody;
            def.position.Set(position.x + 10, position.y + 10);

            b2PolygonShape shape;
            shape.SetAsBox(10, 10);

            b2FixtureDef fixtureDef;
            fixtureDef.shape = &shape;
            fixtureDef.density = 1.0f;
            fixtureDef.friction = 0.0f;

            if (this->world)
            {
                body = this->world->CreateBody(&def);
                fixture = body->CreateFixture(&fixtureDef);
            }
            
        }
    }

    void Render()
    {
        C2D_DrawImageAt(image, position.x, position.y, 0, nullptr, 1.0f, 1.0f);
    }

    void HandleCollision()
    {
        
    }
};

class TileMap
{
private:
    C2D_SpriteSheet tileSheet;

    std::vector<Tile*> tiles;

public:
    void Render()
    {
        for (Tile* t : tiles)
        {
            t->Render();
        }
    }

    Tile* GetTile(unsigned int index)
    {
        return tiles[index];
    }

    Tile* operator[](unsigned int index)
    {
        return tiles[index];
    }

    TileMap(const char* pathOfSheet)
    {
        this->tileSheet = C2D_SpriteSheetLoad(pathOfSheet);
    }

    void AddTile(int sheetIndex, Vector2 position, TileCollisionTypes collisionType = NONE, b2World* world = nullptr) {
        this->tiles.push_back(new Tile(tileSheet, sheetIndex, position, collisionType, world));
    }

    void AddTileOnGrid(int sheetIndex, int gridX, int gridY, TileCollisionTypes collisionType = NONE, b2World* world = nullptr) {
        for (Tile* t : tiles)
        {
            if (t->position == Vector2(gridX * 20, gridY * 20))
            {
                return;
            }
        }
        this->tiles.push_back(new Tile(tileSheet, sheetIndex, Vector2(gridX * 20, gridY * 20), collisionType, world));
    }

    ~TileMap() {
        for (Tile* t : tiles) {
            delete t;
        }

        tiles.clear();

        if (tileSheet) {
            C2D_SpriteSheetFree(tileSheet);
        }
    }
};