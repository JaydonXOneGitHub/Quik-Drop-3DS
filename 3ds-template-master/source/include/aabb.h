#pragma once

#include "vector2.h"

struct Rectangle {
    float x;                // Rectangle top-left corner position x
    float y;                // Rectangle top-left corner position y
    float width;            // Rectangle width
    float height;           // Rectangle height

    Rectangle(float x, float y, float width, float height)
        : x(x), y(y), width(width), height(height)
    {
        
    }

    Rectangle(const Vector2& position, const Vector2& borders)
        : x(position.x), y(position.y), width(borders.x), height(borders.y)
    {
        
    }

    bool Intersects(const Rectangle& rec2)
    {
        bool collision = false;

        if ((this->x < (rec2.x + rec2.width) && (this->x + this->width) > rec2.x) &&
            (this->y < (rec2.y + rec2.height) && (this->y + this->height) > rec2.y)) collision = true;

        return collision;
    }
};